# Modernization Notes

This cleaned copy was created from the university-era Grendel repository without modifying the original archive supplied by the owner.

## Repository hygiene changes

- Removed committed executables and build products.
- Removed CodeLite/ctags index databases that accounted for most repository size.
- Removed IntelliJ/Android Studio user metadata and machine-local Flutter configuration.
- Removed Python bytecode, `__pycache__`, notebook checkpoints, and temporary Office lock files.
- Added a repository-wide `.gitignore` and `.editorconfig`.
- Added GitHub Actions workflows for C++ compilation and the machine-learning smoke test.
- Added root, project, tutorial, and status documentation.

## C++ modernization

All standalone project entry points compile as C++17 with GCC warning flags enabled.

Notable updates include standard containers instead of variable-length arrays, safer input handling, local relative paths instead of hard-coded Windows drives, removal of DOS-only console APIs, standard `int main()` entry points, corrected persistence behavior, and fixes for polymorphic destruction/return-path warnings.

The legacy Payroll application was substantially rewritten because its original implementation depended throughout on DOS/Windows-only APIs and unsafe removed C functions. The new implementation keeps the project concept—employee CRUD, persistence, and salary slips—while using portable C++17.

## Machine-learning modernization

The original one-file regression experiment was reorganized into a reusable command-line workflow with explicit data/output paths, configurable cross-validation/search settings, requirements, input validation, and deterministic train/test splitting. A reduced search configuration was executed successfully against the included dataset as a smoke test.

## Flutter preservation strategy

The Migraine Help project uses an older Flutter/Firebase dependency generation. Because the modernization environment did not contain Flutter, dependencies were not blindly upgraded. The source, assets, and historical configuration were retained; generated/user-specific artifacts and placeholder documentation were cleaned; and a migration/run guide was added.

This distinction is deliberate: verified modernization is preferable to changing framework versions without being able to run `flutter analyze`, tests, and platform builds.
