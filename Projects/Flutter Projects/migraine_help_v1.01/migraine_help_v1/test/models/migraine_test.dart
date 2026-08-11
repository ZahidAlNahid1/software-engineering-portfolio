import 'package:flutter_test/flutter_test.dart';
import 'package:migraine_help_v1/Models/migraine.dart';

void main() {
  group('Migraine', () {
    test('creates a model from Firestore-style map data', () {
      final migraine = Migraine.fromMap(<String, dynamic>{
        'name': 'Morning migraine',
        'sugars': '18',
        'strength': 7,
      });

      expect(migraine.name, 'Morning migraine');
      expect(migraine.sugars, '18');
      expect(migraine.strength, 7);
    });

    test('uses safe defaults for missing data', () {
      final migraine = Migraine.fromMap(<String, dynamic>{});

      expect(migraine.name, '');
      expect(migraine.sugars, '0');
      expect(migraine.strength, 0);
    });

    test('serializes to a Firestore-compatible map', () {
      const migraine = Migraine(
        name: 'Evening migraine',
        sugars: '10',
        strength: 4,
      );

      expect(migraine.toMap(), <String, dynamic>{
        'name': 'Evening migraine',
        'sugars': '10',
        'strength': 4,
      });
    });
  });
}
