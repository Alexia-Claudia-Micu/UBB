package com.example.plantkeeper.repo

import com.example.plantkeeper.data.PlantModel
import com.example.plantkeeper.R  // Import the R class to access resources

object PlantRepository {  // Singleton declaration
    private var plantList: MutableList<PlantModel> = mutableListOf()

    init {
        // Initialize with some default plants (or you could load from a file or database)
        plantList = mutableListOf(
            PlantModel(id = "1", type = "Anthurium Luxurians", picture = R.drawable.anthurium, dateAquired = null, location = "Terrarium", lastTreated = null, treatment = "", notes = "", motherPlant = "", propagations = null),
            PlantModel(id = "2", type = "Hoya Carnosa Tricolor", picture = R.drawable.hoya, dateAquired = null, location = "Living-room Shelf", lastTreated = null, treatment = "", notes = "", motherPlant = "", propagations = null),
            PlantModel(id = "3", type = "Alocasia Frydek Variegata", picture = R.drawable.alocasia, dateAquired = null, location = "Bedroom Shelf", lastTreated = null, treatment = "", notes = "", motherPlant = "", propagations = null),
            PlantModel(id = "4", type = "Philodendron Squamicaule Blood", picture = R.drawable.philodendron, dateAquired = null, location = "Kitchen cabinet", lastTreated = null, treatment = "", notes = "", motherPlant = "", propagations = null),
            PlantModel(id = "5", type = "Monstera Deliciosa Variegata", picture = R.drawable.monstera, dateAquired = null, location = "Living-room Window", lastTreated = null, treatment = "", notes = "", motherPlant = "", propagations = null)
        )
    }

    fun add(plantModel: PlantModel) {
        plantList.add(plantModel)  // Add the plant to the list
    }

    fun get(): List<PlantModel> {
        return plantList  // Return the current list of plants
    }

    fun update(plantModel: PlantModel) {
        plantList.replaceAll { plant ->
            if (plant.id == plantModel.id) plantModel else plant
        }
    }

    fun delete(id: String) {
        plantList.removeAll { it.id == id }
    }

    fun getPlantById(id: String): PlantModel {
        return plantList.first { it.id == id }
    }
}
