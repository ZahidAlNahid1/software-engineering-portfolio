# Project Status

This file records what was verified during the repository cleanup.

## Verification summary

- **C++ standalone projects:** all `Projects/C++ Projects/*/main.cpp` files compile with GCC using C++17 and `-Wall -Wextra -Wpedantic` with no compiler diagnostics.
- **Power Plant Regression:** executed end-to-end against the included `power_plant.csv` using Python 3.13, pandas 2.2, NumPy 2.3, scikit-learn 1.8, and Matplotlib 3.10. A reduced search configuration was used for the verification run.
- **Flutter Migraine Help:** source and configuration were reviewed and cleaned, but a Flutter SDK was not available in the cleanup environment, so a current-SDK build was not claimed. The project README explains the required Firebase/Flutter setup and its legacy dependency baseline.

## Modernized C++ projects

- **CGPA Calculator:** replaced variable-length arrays with standard containers, removed recursion into `main`, added input validation, and corrected GPA calculation to weight grade points by credits.
- **Scientific Calculator:** removed `conio.h`, added domain validation for square roots/logarithms, standard C++ entry point, and repeatable menu flow.
- **Store Management System:** removed `D://` hard-coded paths, DOS console calls, `goto`, and fragile EOF loops; now uses local persistence and standard algorithms.
- **Payroll Management System:** replaced the DOS/Windows-specific legacy implementation with a portable C++17 CRUD/payroll application using CSV persistence.
- **Medical Information System:** fixed a missing return path and polymorphic deletion issue; compiler warnings were removed.
- **Inventory Management:** corrected persistence so saving no longer repeatedly appends duplicate inventory rows.
- **Login/Registration:** removed non-standard `bits/stdc++.h`, fixed signed/unsigned comparisons, and added safer empty-string checks.

## Repository hygiene

Removed or ignored:

- compiled executables and object/build output
- CodeLite and ctags databases/indexes
- IDE metadata (`.idea`, `*.iml`)
- Python bytecode and `__pycache__`
- notebook checkpoints
- Flutter machine-local configuration
- temporary Office lock files

The original source/course material was otherwise preserved.

## Phase 2 — Migraine Help

The first portfolio-focused modernization pass now includes typed Firebase service boundaries, immutable domain models, Firestore map serialization, model tests, and architecture/security/current-Flutter migration documentation. The dependency baseline remains historical until a Flutter SDK is available to verify the current-SDK migration end to end.
