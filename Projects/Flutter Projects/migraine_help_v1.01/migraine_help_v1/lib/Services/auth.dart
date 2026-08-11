import 'package:firebase_auth/firebase_auth.dart';
import 'package:migraine_help_v1/Models/myuser.dart';
import 'package:migraine_help_v1/Services/database.dart';

/// Thin authentication boundary around Firebase Authentication.
///
/// UI code receives the app's [MyUser] model instead of depending directly on
/// Firebase user objects. Authentication failures are represented by `null` so
/// the existing university UI remains backwards compatible; a future
/// production iteration can replace this with a richer typed error result.
class AuthService {
  AuthService({FirebaseAuth? firebaseAuth})
      : _auth = firebaseAuth ?? FirebaseAuth.instance;

  final FirebaseAuth _auth;

  MyUser? _fromFirebaseUser(User? user) {
    return user == null ? null : MyUser(uid: user.uid);
  }

  Stream<MyUser?> get user => _auth.authStateChanges().map(_fromFirebaseUser);

  Future<MyUser?> signInAnon() async {
    try {
      final credential = await _auth.signInAnonymously();
      return _fromFirebaseUser(credential.user);
    } on FirebaseAuthException {
      return null;
    }
  }

  Future<MyUser?> signInWithEmailAndPassword(
    String email,
    String password,
  ) async {
    try {
      final credential = await _auth.signInWithEmailAndPassword(
        email: email.trim(),
        password: password,
      );
      return _fromFirebaseUser(credential.user);
    } on FirebaseAuthException {
      return null;
    }
  }

  Future<MyUser?> registerWithEmailAndPassword(
    String email,
    String password,
  ) async {
    try {
      final credential = await _auth.createUserWithEmailAndPassword(
        email: email.trim(),
        password: password,
      );
      final firebaseUser = credential.user;
      if (firebaseUser == null) {
        return null;
      }

      await DatabaseService(uid: firebaseUser.uid).updateUserData(
        sugars: '0',
        name: 'username',
        strength: 100,
      );

      return _fromFirebaseUser(firebaseUser);
    } on FirebaseAuthException {
      return null;
    }
  }

  Future<void> signOut() => _auth.signOut();
}
