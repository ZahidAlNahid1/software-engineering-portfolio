# Security Notes

Migraine Help stores health-adjacent user-entered information. A portfolio/demo deployment should therefore treat access control and data minimization as first-class requirements.

## Firebase configuration

Firebase client configuration identifies a Firebase project but is not a substitute for authorization. Authentication and Firestore Security Rules must enforce which records a user can read or write.

## Before any public deployment

- Create a dedicated Firebase project for the portfolio/demo environment.
- Re-run `flutterfire configure` for the intended platforms.
- Enable only the authentication providers actually used by the application.
- Add and test Firestore Security Rules before storing real user information.
- Do not use real medical information in screenshots, seed data, demos, or automated tests.
- Configure a private Android signing key before producing a release build.
- Review privacy/disclosure requirements before representing this as a medical or diagnostic product.

## Scope

This university project is a migraine tracking/demo application. It is not documented or validated as a medical device and should not claim to diagnose or treat medical conditions.
