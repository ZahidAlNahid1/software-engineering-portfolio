import 'package:flutter/material.dart';
import 'package:migraine_help_v1/Models/myuser.dart';
import 'package:migraine_help_v1/Screens/Authentication/authenticate.dart';
import 'package:migraine_help_v1/Screens/Home/dashboard.dart';
import 'package:provider/provider.dart';

class Wrapper extends StatelessWidget {
  const Wrapper({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    final user = context.watch<MyUser?>();
    return user == null ? Authenticate() : Dashboard();
  }
}
