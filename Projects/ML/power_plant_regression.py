"""Train and evaluate regression models for combined-cycle power output.

The script compares linear, ridge, random-forest, and gradient-boosting models,
selects the best model using cross-validation on the training split, evaluates
once on a held-out test split, and writes metrics/plots to an output directory.
"""

from __future__ import annotations

import argparse
import math
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.ensemble import GradientBoostingRegressor, RandomForestRegressor
from sklearn.linear_model import LinearRegression, Ridge
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score
from sklearn.model_selection import KFold, RandomizedSearchCV, cross_val_score, train_test_split
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler

FEATURES = ["AT", "V", "AP", "RH"]
TARGET = "PE"
RANDOM_STATE = 42


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--data", type=Path, default=Path(__file__).with_name("power_plant.csv"))
    parser.add_argument("--output", type=Path, default=Path(__file__).with_name("outputs"))
    parser.add_argument("--test-size", type=float, default=0.2)
    parser.add_argument("--folds", type=int, default=5)
    parser.add_argument("--search-iterations", type=int, default=12,
                        help="Randomized-search iterations for each tuned ensemble model.")
    parser.add_argument("--jobs", type=int, default=-1)
    return parser.parse_args()


def load_dataset(path: Path) -> pd.DataFrame:
    if not path.exists():
        raise FileNotFoundError(f"Dataset not found: {path}")

    df = pd.read_csv(path)
    aliases = {
        "Temperature": "AT",
        "Exhaust Vacuum": "V",
        "Exhaust vacuum": "V",
        "Ambient Pressure": "AP",
        "Ambient pressure": "AP",
        "Relative Humidity": "RH",
        "Relative humidity": "RH",
    }
    df = df.rename(columns=aliases)

    missing = set(FEATURES + [TARGET]) - set(df.columns)
    if missing:
        raise ValueError(f"Dataset is missing required columns: {sorted(missing)}")

    clean = df[FEATURES + [TARGET]].apply(pd.to_numeric, errors="coerce").dropna()
    if clean.empty:
        raise ValueError("Dataset contains no usable numeric rows after cleaning.")
    return clean


def candidates(cv: KFold, jobs: int, iterations: int):
    linear = Pipeline([("scaler", StandardScaler()), ("model", LinearRegression())])
    ridge = Pipeline([("scaler", StandardScaler()), ("model", Ridge())])

    rf = RandomizedSearchCV(
        RandomForestRegressor(random_state=RANDOM_STATE, n_jobs=jobs),
        {
            "n_estimators": np.arange(150, 601, 50),
            "max_depth": [None, 4, 6, 8, 10, 12, 16, 20],
            "min_samples_split": np.arange(2, 9),
            "min_samples_leaf": np.arange(1, 5),
            "max_features": ["sqrt", "log2", 0.6, 0.8, 1.0],
        },
        n_iter=iterations,
        scoring="neg_root_mean_squared_error",
        cv=cv,
        random_state=RANDOM_STATE,
        n_jobs=jobs,
    )

    gb = RandomizedSearchCV(
        GradientBoostingRegressor(random_state=RANDOM_STATE),
        {
            "n_estimators": np.arange(100, 501, 50),
            "learning_rate": np.linspace(0.02, 0.18, 9),
            "max_depth": np.arange(2, 7),
            "subsample": np.linspace(0.75, 1.0, 6),
        },
        n_iter=iterations,
        scoring="neg_root_mean_squared_error",
        cv=cv,
        random_state=RANDOM_STATE,
        n_jobs=jobs,
    )

    return {
        "LinearRegression": linear,
        "Ridge": ridge,
        "RandomForest": rf,
        "GradientBoosting": gb,
    }


def save_plots(model, features, y_test, y_pred, output: Path) -> None:
    plt.figure()
    plt.scatter(y_test, y_pred, alpha=0.6)
    limits = [min(y_test.min(), y_pred.min()), max(y_test.max(), y_pred.max())]
    plt.plot(limits, limits)
    plt.xlabel("Actual PE (MW)")
    plt.ylabel("Predicted PE (MW)")
    plt.title("Predicted vs Actual (Test Set)")
    plt.tight_layout()
    plt.savefig(output / "pred_vs_actual.png", dpi=160)
    plt.close()

    residuals = y_test - y_pred
    plt.figure()
    plt.hist(residuals, bins=40)
    plt.xlabel("Residual (Actual - Predicted) MW")
    plt.ylabel("Frequency")
    plt.title("Residuals (Test Set)")
    plt.tight_layout()
    plt.savefig(output / "residuals_hist.png", dpi=160)
    plt.close()

    values = None
    title = None
    if hasattr(model, "feature_importances_"):
        values = model.feature_importances_
        title = "Feature Importance"
    elif isinstance(model, Pipeline) and hasattr(model.steps[-1][1], "coef_"):
        values = np.abs(model.steps[-1][1].coef_)
        title = "Absolute Standardized Coefficients"

    if values is not None:
        order = np.argsort(values)[::-1]
        plt.figure()
        plt.bar(range(len(order)), np.asarray(values)[order])
        plt.xticks(range(len(order)), np.asarray(features)[order])
        plt.ylabel("Importance")
        plt.title(title)
        plt.tight_layout()
        plt.savefig(output / "feature_importance.png", dpi=160)
        plt.close()


def main() -> int:
    args = parse_args()
    if not 0 < args.test_size < 1:
        raise ValueError("--test-size must be between 0 and 1.")
    if args.folds < 2:
        raise ValueError("--folds must be at least 2.")
    if args.search_iterations < 1:
        raise ValueError("--search-iterations must be at least 1.")

    args.output.mkdir(parents=True, exist_ok=True)
    df = load_dataset(args.data)
    X, y = df[FEATURES], df[TARGET]
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=args.test_size, random_state=RANDOM_STATE
    )

    cv = KFold(n_splits=args.folds, shuffle=True, random_state=RANDOM_STATE)
    models = candidates(cv, args.jobs, args.search_iterations)

    cv_rows = []
    for name, model in models.items():
        scores = -cross_val_score(
            model, X_train, y_train,
            scoring="neg_root_mean_squared_error", cv=cv, n_jobs=args.jobs
        )
        cv_rows.append({"model": name, "cv_rmse_mean": scores.mean(), "cv_rmse_std": scores.std()})

    cv_table = pd.DataFrame(cv_rows).sort_values("cv_rmse_mean").reset_index(drop=True)
    cv_table.to_csv(args.output / "cv_results.csv", index=False)

    best_name = str(cv_table.iloc[0]["model"])
    best_search_or_model = models[best_name]
    best_search_or_model.fit(X_train, y_train)
    final_model = getattr(best_search_or_model, "best_estimator_", best_search_or_model)

    y_pred = final_model.predict(X_test)
    metrics = pd.DataFrame([{
        "best_model": best_name,
        "test_RMSE": math.sqrt(mean_squared_error(y_test, y_pred)),
        "test_MAE": mean_absolute_error(y_test, y_pred),
        "test_R2": r2_score(y_test, y_pred),
    }])
    metrics.to_csv(args.output / "model_metrics.csv", index=False)
    save_plots(final_model, FEATURES, y_test, y_pred, args.output)

    print("\nCross-validation results:\n", cv_table.to_string(index=False))
    print("\nTest metrics:\n", metrics.to_string(index=False))
    if hasattr(best_search_or_model, "best_params_"):
        print("\nBest hyperparameters:", best_search_or_model.best_params_)
    print(f"\nArtifacts written to: {args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
