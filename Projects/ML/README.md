# Combined Cycle Power Plant Regression

This project predicts net hourly electrical energy output (`PE`) from ambient conditions in a combined-cycle power plant dataset.

## Inputs

- `AT` — ambient temperature
- `V` — exhaust vacuum
- `AP` — ambient pressure
- `RH` — relative humidity
- `PE` — target electrical output

The loader also accepts common long-form versions of the feature names and normalizes them automatically.

## Models

The training pipeline compares:

- Linear Regression
- Ridge Regression
- Random Forest Regression with randomized hyperparameter search
- Gradient Boosting Regression with randomized hyperparameter search

Model selection uses shuffled K-fold cross-validation on the training split. The selected model is then evaluated once on a held-out test set using RMSE, MAE, and R².

## Setup

```bash
python -m venv .venv
# Windows: .venv\Scripts\activate
# macOS/Linux: source .venv/bin/activate
pip install -r requirements.txt
```

## Run

```bash
python power_plant_regression.py
```

Useful options:

```bash
python power_plant_regression.py --help
python power_plant_regression.py --folds 3 --search-iterations 5 --jobs 1
python power_plant_regression.py --data path/to/data.csv --output path/to/results
```

## Outputs

The default `outputs/` directory receives:

- `cv_results.csv`
- `model_metrics.csv`
- `pred_vs_actual.png`
- `residuals_hist.png`
- `feature_importance.png` when the selected model exposes importances or coefficients

## Verification

During the repository modernization, the complete pipeline was executed against the included dataset using a reduced (`2` folds, `1` search iteration) smoke-test configuration. It selected Random Forest and achieved approximately `R² = 0.962` on the held-out set. The normal defaults intentionally search more configurations and may produce slightly different tuned parameters while retaining the fixed train/test random seed.
