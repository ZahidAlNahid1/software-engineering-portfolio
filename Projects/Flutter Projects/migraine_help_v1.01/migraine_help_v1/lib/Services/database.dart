import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:migraine_help_v1/Models/migraine.dart';

class DatabaseService {
  DatabaseService({required this.uid, FirebaseFirestore? firestore})
      : _firestore = firestore ?? FirebaseFirestore.instance;

  DatabaseService.withoutUID({FirebaseFirestore? firestore})
      : uid = '',
        _firestore = firestore ?? FirebaseFirestore.instance;

  final String uid;
  final FirebaseFirestore _firestore;

  CollectionReference<Map<String, dynamic>> get _migraineCollection =>
      _firestore.collection('migraine');

  Future<void> updateUserData({
    required String sugars,
    required String name,
    required int strength,
  }) {
    if (uid.isEmpty) {
      throw StateError('A user id is required to update user data.');
    }

    return _migraineCollection.doc(uid).set(
          Migraine(name: name, sugars: sugars, strength: strength).toMap(),
          SetOptions(merge: true),
        );
  }

  List<Migraine> _migraineListFromSnapshot(
    QuerySnapshot<Map<String, dynamic>> snapshot,
  ) {
    return snapshot.docs
        .map((document) => Migraine.fromMap(document.data()))
        .toList(growable: false);
  }

  Stream<List<Migraine>> get migraine =>
      _migraineCollection.snapshots().map(_migraineListFromSnapshot);
}
