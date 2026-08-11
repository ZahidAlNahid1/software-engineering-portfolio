# Migraine Help

Migraine Help is a Flutter/Firebase university application for recording migraine events and related context such as pain location, activity, weather, and reports. It is being modernized as a portfolio project while preserving the original application flows.

## What the project demonstrates

- Firebase Authentication session handling
- Cloud Firestore persistence
- Provider-based application state
- Multi-screen Flutter navigation and form flows
- Migraine pain/location tracking UI
- Activity, weather, profile, settings, and report screens
- Domain-model serialization and automated model tests

## Phase 2 modernization

The first Phase 2 pass improves the code without a risky visual rewrite:

- introduced a consistently named `AuthService` with typed method signatures;
- isolated Firebase Authentication from the application `MyUser` model;
- made `MyUser` and `Migraine` immutable;
- added `Migraine.fromMap` and `toMap` serialization;
- changed Firestore access to typed `CollectionReference<Map<String, dynamic>>` APIs;
- added dependency injection seams for Firebase Auth and Firestore;
- removed duplicate Flutter binding initialization and debug printing;
- made application startup and Provider usage clearer;
- added model tests and architecture/security/migration documentation.

The original Adobe XD-derived screens are intentionally preserved during this pass. Replacing those layouts before the app is covered by tests would create unnecessary regression risk.

## Structure

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

test/
└── models/

docs/
├── ARCHITECTURE.md
├── MIGRATION_TO_CURRENT_FLUTTER.md
└── SECURITY.md
```

## Firebase setup

For a fresh deployment, use a dedicated Firebase project with Authentication and Cloud Firestore enabled. Configure the application using the FlutterFire CLI and verify Firestore Security Rules before storing any real user data.

The Firebase configuration that accompanied the university project should be treated as historical development configuration, not as production credentials or production authorization.

## Historical runtime baseline

The checked-in dependency constraints still describe the Flutter 2 / Dart 2 generation in which the university project was written. They are intentionally not mass-upgraded in this pass because the modernization environment does not contain a Flutter SDK with which to prove that a dependency migration builds.

See [`docs/MIGRATION_TO_CURRENT_FLUTTER.md`](docs/MIGRATION_TO_CURRENT_FLUTTER.md) for the migration checklist.

## Verification

New pure model behavior is covered by tests in `test/models/migraine_test.dart`. On a compatible Flutter environment, run:

```bash
flutter pub get
flutter analyze
flutter test
```

A current-Flutter migration should additionally pass a debug build before it is marked verified.

## Portfolio status

**Modernization in progress.** The service/model layer has begun moving toward production-style boundaries. The next verified milestone is a current Flutter/Firebase migration followed by UI smoke tests and targeted widget tests.
