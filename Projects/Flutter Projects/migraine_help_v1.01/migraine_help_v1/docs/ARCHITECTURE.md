# Architecture

Migraine Help began as a university Flutter application generated partly from Adobe XD screens. Phase 2 keeps the visual flows intact while introducing clearer boundaries around authentication, persistence, and domain models.

## Current layers

```text
UI / Screens
    |
    v
Provider session state
    |
    +--> AuthService --------> Firebase Authentication
    |
    +--> DatabaseService ----> Cloud Firestore
              |
              v
         Domain models
        (MyUser, Migraine)
```

### Presentation

The `Screens`, `Migraine`, `Activity`, `Report`, `Weather`, `Side_Menu`, `Settings`, and `Notifications` directories contain the original presentation flows. Many screens are still Adobe XD-derived and therefore intentionally retain their existing layout code during the first modernization pass.

### Authentication

`AuthService` is the application boundary around Firebase Authentication. The UI consumes the application-level `MyUser` model rather than Firebase's `User` object.

### Persistence

`DatabaseService` owns Firestore reads and writes. Firestore documents are converted to and from `Migraine` with `fromMap` / `toMap` instead of indexing untyped snapshots throughout the UI.

### Domain models

`MyUser` and `Migraine` are immutable value-style models. This makes them easier to test and keeps Firebase-specific types out of most presentation code.

## Next architecture step

After the app is migrated and verified on the current Flutter stable toolchain, the generated UI should be divided into feature folders with view models/controllers or repositories where that separation actually reduces complexity. Avoid a large rewrite until the current behavior is covered by tests.
