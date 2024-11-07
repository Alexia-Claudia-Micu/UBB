package com.example.plantkeeper

import android.app.Activity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.ViewModelProvider
import com.example.plantkeeper.data.PlantModel
import com.example.plantkeeper.viewModel.PlantViewModel
import java.util.UUID

class CreateActivity : AppCompatActivity() {

    private lateinit var viewModel: PlantViewModel
    private lateinit var plantType: EditText
    private lateinit var plantLocation: EditText
    private lateinit var plantPicture: ImageView
    private lateinit var btnSavePlant: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_create)

        // Initialize views
        plantType = findViewById(R.id.plant_type)
        plantLocation = findViewById(R.id.plant_location)
        plantPicture = findViewById(R.id.plant_picture)
        btnSavePlant = findViewById(R.id.btn_save_plant)

        // Initialize ViewModel (use ViewModelProvider with activity context to share the same ViewModel)
        viewModel = ViewModelProvider(this).get(PlantViewModel::class.java)

        btnSavePlant.setOnClickListener {
            val type = plantType.text.toString()
            val location = plantLocation.text.toString()
            val picture = R.drawable.default_image  // Replace with actual image logic if needed

            // Simple validation for empty fields
            if (type.isEmpty() || location.isEmpty()) {
                Toast.makeText(this, "Please fill all fields", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            // Create a new plant model
            val newPlant = PlantModel(
                id = UUID.randomUUID().toString(),  // Generate a unique ID for the new plant
                type = type,
                picture = picture,
                location = location,
                dateAquired = null,
                lastTreated = null,
                treatment = "",
                notes = "",
                motherPlant = "",
                propagations = null
            )

            // Add to the repository via ViewModel
            viewModel.addPlant(newPlant)

            // Send back the result to MainActivity (force refresh)
            setResult(Activity.RESULT_OK)
            finish()
        }
    }
}

