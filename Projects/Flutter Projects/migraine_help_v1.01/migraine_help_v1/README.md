# Migraine Help

Migraine Help is a Flutter university project for recording migraine events and related context such as pain location, symptoms, activity, weather, and reports. The application demonstrates a multi-screen mobile UI backed by Firebase Authentication and Cloud Firestore.

## Features represented in the codebase

- Firebase authentication and user session handling
- Firestore-backed migraine/user data
- Migraine pain/location detail flows
- Activity and weather views
- Reporting/upload-download screens
- Profile, settings, help, and side-menu screens
- Provider-based application state
- Reusable image assets and custom visual layouts

## Project structure

```text
lib/
├── Activity/
├── Migraine/
├── Models/
├── Notifications/
├── Report/
├── Screens/
├── Services/
├── Settings/
├── Shared/
├── Side_Menu/
├── Weather/
└── main.dart
```

## Firebase setup

The application expects a Firebase project configured for Authentication and Cloud Firestore. The Android project currently contains the Firebase configuration that accompanied the university project. For your own deployment, create your own Firebase application and replace platform configuration files with values from your Firebase project.

Do not treat Firebase client configuration as server-side authorization. Firestore security rules and Firebase Authentication should enforce access to user data.

## Running the project

This project originated on the Flutter 2 / Dart 2 generation and its dependency versions have intentionally been preserved rather than blindly upgraded without a Flutter toolchain.

For the historical environment, install a compatible Flutter SDK and run:

```bash
flutter pub get
flutter run
```

For a current Flutter SDK, expect a dependency/API migration before production use. Recommended migration steps are:

1. run `flutter pub outdated`;
2. upgrade Firebase/Flutter dependencies incrementally;
3. run `dart fix --apply` where appropriate;
4. run `flutter analyze` and `flutter test`;
5. update Android/iOS build configuration using `flutter create .` only after committing/backing up custom platform files;
6. verify authentication, Firestore reads/writes, and each navigation flow on a device/emulator.

## Current verification status

The repository cleanup environment did not include the Flutter SDK, so this application was **not claimed as current-SDK build verified**. The source tree and repository artifacts were cleaned and documented while preserving the historical dependency baseline. See the root `PROJECT_STATUS.md` for the verified parts of the repository.

## Portfolio notes

This is one of the strongest projects in the repository because it demonstrates a complete application rather than an isolated exercise. A future portfolio-focused iteration should add automated widget/service tests, stronger error presentation around Firebase calls, typed service return values, and an incremental migration to current Flutter/Firebase packages.
