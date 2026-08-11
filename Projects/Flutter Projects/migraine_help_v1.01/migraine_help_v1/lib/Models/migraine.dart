class Migraine {
  const Migraine({
    required this.name,
    required this.sugars,
    required this.strength,
  });

  final String name;
  final String sugars;
  final int strength;

  factory Migraine.fromMap(Map<String, dynamic> data) {
    return Migraine(
      name: data['name'] as String? ?? '',
      sugars: data['sugars'] as String? ?? '0',
      strength: (data['strength'] as num?)?.toInt() ?? 0,
    );
  }

  Map<String, dynamic> toMap() {
    return <String, dynamic>{
      'name': name,
      'sugars': sugars,
      'strength': strength,
    };
  }
}
