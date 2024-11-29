import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:intl/intl.dart';

import '../Plant.dart'; // Import the Plant model
import '../Screens/AddPlantScreen.dart'; // Add plant screen
import '../Screens/UpdatePlantScreen.dart'; // Update plant screen

class ListScreen extends StatefulWidget {
  const ListScreen({super.key});

  @override
  State<StatefulWidget> createState() => ListScreenState();
}

class ListScreenState extends State<ListScreen> {
  final List<Plant> plants = Plant.init();

  Plant? getPlantById(int id) {
    for (Plant p in plants) {
      if (p.id == id) return p;
    }
    return null;
  }

  void updatePlant(Plant newPlant) {
    for (int i = 0; i < plants.length; i++) {
      if (plants[i].id == newPlant.id) {
        plants[i] = newPlant;
        return;
      }
    }
  }

  void removeFromList(int id) {
    plants.removeWhere((element) => element.id == id);
  }

  _showDialog(BuildContext context, int id) {
    showDialog(
      context: context,
      builder: (context) => CupertinoAlertDialog(
        title: const Text("Delete Plant"),
        content: const Text("Are you sure you want to delete this plant?"),
        actions: <Widget>[
          CupertinoDialogAction(
            child: const Text("Yes"),
            onPressed: () {
              setState(() {
                removeFromList(id);
                Navigator.of(context).pop();
              });
            },
          ),
          CupertinoDialogAction(
            child: const Text("No"),
            onPressed: () => Navigator.of(context).pop(),
          ),
        ],
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text(
          "Plant Keeper",
          style: TextStyle(
            color: Colors.white,
          ),
        ),
        centerTitle: true,
        backgroundColor: Color.fromARGB(255, 51, 66, 51), // Custom app bar green
      ),
      body: Center(
        child: Container(
          color: Color.fromARGB(255, 119, 153, 120), // Full background color
          child: ListView.builder(
            itemCount: plants.length,
            itemBuilder: (context, index) {
              return templatePlant(plants[index]);
            },
          ),
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () async {
          Plant newPlant = await Navigator.push(
            context,
            MaterialPageRoute(builder: (context) => AddPlantScreen()),
          );
          setState(() {
            plants.add(newPlant);
            ScaffoldMessenger.of(context).showSnackBar(const SnackBar(
              content: Text("Plant added!"),
            ));
          });
        },
        backgroundColor: Color.fromARGB(255, 119, 153, 120), // Floating button custom green
        child: const Icon(Icons.add),
      ),
    );
  }

  Widget templatePlant(Plant plant) {
    return Card(
      margin: const EdgeInsets.fromLTRB(20, 10, 20, 0),
      elevation: 3,
      child: Container(
        padding: const EdgeInsets.all(10),
        decoration: BoxDecoration(
          color: Color.fromARGB(255, 195, 232, 196), // Item background color
          border: Border.all(color: Color.fromARGB(255, 119, 153, 120)), // Border custom green
          borderRadius: BorderRadius.circular(10),
        ),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            Text(
              "${plant.type} (Acquired: ${DateFormat('yyyy-MM-dd').format(plant.dateAcquired!)})",
              style: const TextStyle(fontSize: 16, fontWeight: FontWeight.bold),
            ),
            const SizedBox(height: 5),
            Text("Location: ${plant.location ?? 'Unknown'}"),
            Text("Last Treated: ${plant.lastTreated != null ? DateFormat('yyyy-MM-dd').format(plant.lastTreated!) : 'N/A'}"),
            Row(
              mainAxisAlignment: MainAxisAlignment.end,
              children: <Widget>[
                IconButton(
                  onPressed: () => _showDialog(context, plant.id),
                  icon: const Icon(CupertinoIcons.delete),
                  color: Colors.red,
                ),
                IconButton(
                  onPressed: () async {
                    Plant updatedPlant = await Navigator.push(
                      context,
                      MaterialPageRoute(
                        builder: (context) => UpdatePlantScreen(plant: plant),
                      ),
                    );
                    setState(() {
                      updatePlant(updatedPlant);
                      ScaffoldMessenger.of(context).showSnackBar(const SnackBar(
                        content: Text("Plant updated!"),
                      ));
                    });
                  },
                  icon: const Icon(CupertinoIcons.pen),
                  color: Colors.blue,
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
