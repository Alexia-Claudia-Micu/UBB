
import 'package:flutter/material.dart';
import 'package:maa/Screens/AddPlantScreen.dart';

import 'Screens/ListScreen.dart';

void main() {
  WidgetsFlutterBinding.ensureInitialized();
  runApp(const MaterialApp(
      home: MyMainScreen()
  )
  );
}

class MyMainScreen extends StatefulWidget {
  const MyMainScreen({super.key});

  @override
  State<StatefulWidget> createState() => MyMainScreenState();
}

class MyMainScreenState extends State<MyMainScreen> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Color.fromARGB(255, 55, 77, 59),
      body: Column(
        children: <Widget>[
          const Padding(
            padding: EdgeInsets.fromLTRB(60, 100, 20, 0),
          ),
          Container(
              alignment: Alignment.center,
              margin: const EdgeInsets.fromLTRB(0, 250, 0, 0),
              child: ElevatedButton(
                onPressed: () => {
                  Navigator.push(context, MaterialPageRoute(builder: (context) => const PlantListScreen()))
                },
                style: ElevatedButton.styleFrom(
                    backgroundColor: Color.fromARGB(255, 119, 153, 120)
                ),
                child: const Text(
                    "See your plants",
                    style: TextStyle(
                        color: Colors.black,
                        fontSize: 30.0,
                        fontWeight: FontWeight.bold,
                        fontFamily: 'SomeFam'
                    )),
              )
          )
        ],
      ),
    );
  }
}
