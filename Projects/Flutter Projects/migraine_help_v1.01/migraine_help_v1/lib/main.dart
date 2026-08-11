import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:migraine_help_v1/Models/myuser.dart';
import 'package:migraine_help_v1/Screens/wrapper.dart';
import 'package:migraine_help_v1/Services/auth.dart';
import 'package:provider/provider.dart';

Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await SystemChrome.setPreferredOrientations(
    const <DeviceOrientation>[
      DeviceOrientation.portraitUp,
      DeviceOrientation.portraitDown,
    ],
  );
  await Firebase.initializeApp();
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return StreamProvider<MyUser?>.value(
      initialData: null,
      value: AuthService().user,
      child: const MaterialApp(
        debugShowCheckedModeBanner: false,
        title: 'Migraine Help',
        home: Wrapper(),
      ),
    );
  }
}
