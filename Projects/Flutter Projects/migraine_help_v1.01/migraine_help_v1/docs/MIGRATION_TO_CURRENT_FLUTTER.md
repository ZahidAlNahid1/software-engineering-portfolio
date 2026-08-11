# Migration to Current Flutter

The application was originally built for Flutter 2 / Dart 2. Phase 2 begins by improving the application code without pretending that a current-SDK migration has been verified in an environment that does not contain Flutter.

## Recommended migration workflow

1. Install the current Flutter stable SDK and run `flutter doctor`.
2. Create a working branch before changing dependencies.
3. Run `flutter pub outdated` to identify dependency constraints.
4. Upgrade the Dart SDK constraint and packages incrementally rather than all at once.
5. Use the FlutterFire CLI and run `flutterfire configure` for the Firebase project and supported platforms.
6. Update `main.dart` to initialize Firebase with the generated `firebase_options.dart` when configuration is regenerated.
7. Run `dart fix --apply` only after reviewing the proposed changes.
8. Run `dart format .`, `flutter analyze`, and `flutter test`.
9. Regenerate outdated Android/iOS runner scaffolding carefully, preserving application identifiers and custom platform configuration.
10. Verify authentication, Firestore reads/writes, navigation, form validation, and reports on a real device or emulator.

## Migration completion criteria

A current-SDK migration is complete only when all of the following pass:

```bash
flutter pub get
dart format --output=none --set-exit-if-changed .
flutter analyze
flutter test
flutter build apk --debug
```

Firebase-dependent flows should then be exercised against a dedicated development Firebase project or emulator suite.
