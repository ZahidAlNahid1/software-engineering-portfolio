class MyUser {
  const MyUser({required this.uid});

  final String uid;

  @override
  bool operator ==(Object other) =>
      identical(this, other) || other is MyUser && other.uid == uid;

  @override
  int get hashCode => uid.hashCode;
}
