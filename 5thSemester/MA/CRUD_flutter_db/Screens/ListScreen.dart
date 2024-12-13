import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import '../Plant.dart';
import '../Screens/AddPlantScreen.dart';
import '../Screens/UpdatePlantScreen.dart';
import '../Repo/DbRepository.dart'; // Updated to match your repository

class PlantListScreen extends StatefulWidget {
  const PlantListScreen({super.key});

  @override
  State<StatefulWidget> createState() => PlantListScreenState();
}

class PlantListScreenState extends State<PlantListScreen> {
  final PlantDatabaseRepo databaseRepo = PlantDatabaseRepo.dbInstance;

  late List<Plant> plants;

  void getPlantsFromFuture() async {
    plants = await databaseRepo.getPlants();
  }

  @override
  void initState() {
    super.initState();
    _loadPlants();
  }

  void _loadPlants() async {
    List<Plant> plants = await databaseRepo.getPlants();
    // Handle plants data (e.g., setState to update the UI)
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
              onPressed: () async {
                await databaseRepo.removePlant(id);
                setState(() {
                  Navigator.of(context).pop();
                });
              },
            ),
            CupertinoDialogAction(
              child: const Text("No"),
              onPressed: () {
                setState(() {
                  Navigator.of(context).pop();
                });
              },
            ),
          ],
        ));
  }

  @override
  Widget build(BuildContext context) {
    getPlantsFromFuture();
    return Scaffold(
      appBar: AppBar(
        title: const Text(
          "Plants",
          style: TextStyle(
            color: Colors.black,
          ),
        ),
        centerTitle: true,
        backgroundColor:  Color.fromARGB(255, 55, 77, 59),
      ),
      body: Center(
        child: Container(
            color: Color.fromARGB(255, 119, 153, 120), child: _buildListOfPlants()),
      ),
      floatingActionButton: FloatingActionButton(
          onPressed: () async {
            Plant plant = await Navigator.push(context,
                MaterialPageRoute(builder: (context) => const AddPlantScreen()));
            await databaseRepo.addPlant(plant);
            setState(() {
              ScaffoldMessenger.of(context).showSnackBar(const SnackBar(
                content: Text("Plant added!"),
              ));
            });
          },
          backgroundColor: Color.fromARGB(255, 55, 77, 59),
          child: const Icon(Icons.add)),
    );
  }

  Widget _buildListOfPlants() {
    return FutureBuilder(
      builder: (context, snapshot) {
        if (snapshot.connectionState == ConnectionState.waiting) {
          return const Center(child: CircularProgressIndicator());
        } else if (!snapshot.hasData || snapshot.data!.isEmpty) {
          return const Center(child: Text("No plants available"));
        }
        return ListView.builder(
          itemCount: snapshot.data!.length,
          itemBuilder: (context, index) {
            return _buildPlantCard(snapshot.data![index]);
          },
        );
      },
      future: databaseRepo.getPlants(),
    );
  }

  Widget _buildPlantCard(Plant plant) {
    return Card(
      elevation: 2,
      margin: const EdgeInsets.symmetric(horizontal: 16, vertical: 8),
      child: Container(
        decoration: BoxDecoration(
          color: Color.fromARGB(255, 195, 219, 199),
          border: Border.all(color: Colors.black),
          borderRadius: BorderRadius.circular(12),
        ),
        child: Column(
          children: [
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: Text(
                "${plant.type} - Acquired: ${plant.dateAcquired != null ? DateFormat('yyyy-MM-dd').format(plant.dateAcquired!) : 'Unknown'}",
                style: const TextStyle(fontSize: 16),
              ),
            ),
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 8.0),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  IconButton(
                    onPressed: () => _showDialog(context, plant.id!),
                    icon: const Icon(CupertinoIcons.delete, color: Colors.black),
                  ),
                  IconButton(
                    onPressed: () async {
                      Plant updatedPlant = await Navigator.push(
                          context,
                          MaterialPageRoute(
                              builder: (context) => UpdatePlantScreen(plant: plant)));
                      await databaseRepo.updatePlant(updatedPlant);
                      setState(() {
                        ScaffoldMessenger.of(context).showSnackBar(const SnackBar(
                          content: Text("Plant updated!"),
                        ));
                      });
                    },
                    icon: const Icon(CupertinoIcons.pen, color: Colors.black),
                  ),
                ],
              ),
            )
          ],
        ),
      ),
    );
  }
}
