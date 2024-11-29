package com.example.plantkeeper.viewModel

import android.util.Log
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import com.example.plantkeeper.data.PlantModel
import com.example.plantkeeper.repo.PlantRepository

class PlantViewModel : ViewModel() {

    // Use the singleton instance of PlantRepository
    private val plantRepository = PlantRepository

    private val _plants = MutableLiveData<List<PlantModel>>()
    val plants: LiveData<List<PlantModel>> = _plants

    init {
        // Initialize repository data (optional)
        // Load plants initially
        getPlants()
    }

    // Fetch plants from the repository and update LiveData
    fun getPlants() {
        _plants.value = plantRepository.get()  // Fetch plants from the singleton repository
    }

    // Add a plant to the repository and refresh the list
    fun addPlant(plant: PlantModel) {
        plantRepository.add(plant)  // Add plant to the singleton repository
        getPlants()  // Refresh the plant list
    }

    // Delete a plant from the repository and refresh the list
    fun deletePlant(id: String) {
        plantRepository.delete(id)  // Delete plant from the singleton repository
        getPlants()  // Refresh the plant list
    }

    // Update a plant in the repository and refresh the list
    fun updatePlant(plant: PlantModel) {
        plantRepository.update(plant)  // Update plant in the singleton repository
        getPlants()  // Refresh the plant list
    }

    // Get a specific plant by its ID from the repository
    fun getPlantById(id: String): PlantModel {
        return plantRepository.getPlantById(id)  // Get plant by ID from the singleton repository
    }
}
