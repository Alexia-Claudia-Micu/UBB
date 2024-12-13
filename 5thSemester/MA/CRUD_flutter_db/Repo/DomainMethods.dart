import '../Plant.dart';

class InMemoryPlantRepo {
  List<Plant> plants = Plant.init();

  Plant? getPlantById(int id) {
    try {
      return plants.firstWhere((plant) => plant.id == id);
    } catch (e) {
      return null; // Handle the case where no plant is found
    }
  }

  void addPlant(Plant plant) {
    plants.add(plant);
  }

  void updatePlant(Plant updatedPlant) {
    plants = plants.map((plant) {
      return plant.id == updatedPlant.id ? updatedPlant : plant;
    }).toList();
  }

  void deletePlant(int id) {
    plants.removeWhere((plant) => plant.id == id);
  }
}
