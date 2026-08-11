# Grendel — Software Engineering Portfolio & Learning Archive

Grendel is a cleaned and modernized collection of university projects, programming exercises, algorithms, and tutorial work. The repository preserves the original learning history while making the main projects easier to build, understand, and evaluate.

## Featured projects

| Project | Technology | What it demonstrates | Status |
|---|---|---|---|
| [Migraine Help](Projects/Flutter%20Projects/migraine_help_v1.01/migraine_help_v1) | Flutter, Dart, Firebase | Mobile UI, authentication, Firestore, health-event tracking | Preserved + documented |
| [Power Plant Regression](Projects/ML) | Python, pandas, scikit-learn | Data cleaning, cross-validation, model comparison, tuning, evaluation | Verified |
| [Medical Information System](Projects/C++%20Projects/Medical_Information_System) | C++17 | OOP, polymorphism, command/factory/observer-style patterns | Compiles cleanly |
| [Inventory Management](Projects/C++%20Projects/Inventory_Management) | C++17 | CRUD, persistence, CSV storage | Compiles cleanly |
| [Payroll Management](Projects/C++%20Projects/Payroll_Management_System) | C++17 | CRUD, persistence, payroll calculations | Modernized + verified |

## Repository layout

```text
Grendel/
├── Projects/
│   ├── C++ Projects/        # Standalone console applications
│   ├── Flutter Projects/    # Migraine Help mobile application
│   └── ML/                  # Power-plant regression project
├── Snippets/                # Small reusable examples
├── Tutorials/               # Coursework and guided practice
├── Data Structures and Algorithms.md
├── PROJECT_STATUS.md
└── README.md
```

## C++ projects

All standalone C++ projects are written/buildable as C++17. From the C++ projects directory, use CMake:

```bash
cmake -S . -B build
cmake --build build
```

Or compile an individual project directly:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic "Inventory_Management/main.cpp" -o inventory
```

## Machine-learning project

```bash
cd Projects/ML
python -m venv .venv
# Windows: .venv\Scripts\activate
# macOS/Linux: source .venv/bin/activate
pip install -r requirements.txt
python power_plant_regression.py
```

The script compares linear regression, ridge regression, random forest, and gradient boosting using cross-validation, then evaluates the selected model on a holdout set. Generated metrics and plots are written to `outputs/`.

## Flutter project

The Flutter project is under `Projects/Flutter Projects/migraine_help_v1.01/migraine_help_v1`. It was built against an older Flutter/Firebase generation and is preserved as university work. See its README for Firebase setup and compatibility notes before running it with a current Flutter SDK.

## Modernization work

This cleaned edition removes committed executables, IDE indexes, Python bytecode, temporary Office files, CodeLite/ctags databases, notebook checkpoints, and machine-specific configuration. It also adds repository-wide ignore/editor rules, project documentation, reproducible C++ builds, and a cleaner ML workflow.

Several legacy C++ applications were updated to remove non-standard variable-length arrays, recursive calls to `main`, DOS/Windows-only console dependencies, unsafe input patterns, hard-coded drive paths, compiler warnings, and undefined polymorphic deletion behavior.

## Purpose

This repository contains both portfolio work and learning history. Small tutorial exercises are intentionally retained because they show progression, but the projects in the Featured Projects section are the best starting points for reviewers.
