package com.example.plantkeeper

import android.app.Activity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.ViewModelProvider
import com.example.plantkeeper.viewModel.PlantViewModel

class UpdateActivity : AppCompatActivity() {

    private lateinit var viewModel: PlantViewModel
    private lateinit var plantType: EditText
    private lateinit var plantLocation: EditText
    private lateinit var plantPicture: ImageView
    private lateinit var btnUpdatePlant: Button
    private lateinit var plantId: String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_update)

        // Initialize views
        plantType = findViewById(R.id.plant_type)
        plantLocation = findViewById(R.id.plant_location)
        plantPicture = findViewById(R.id.plant_picture)
        btnUpdatePlant = findViewById(R.id.btn_update_plant)

        // Get data from intent
        plantId = intent.getStringExtra("plantId") ?: return  // Get plant ID passed from MainActivity

        // Initialize ViewModel
        viewModel = ViewModelProvider(this).get(PlantViewModel::class.java)

        // Populate the fields with the current plant details
        val plant = viewModel.getPlantById(plantId) // Fetch the plant by its ID
        plant?.let {
            plantType.setText(it.type)
            plantLocation.setText(it.location)
            // Load the image (if necessary)
        }

        btnUpdatePlant.setOnClickListener {
            val type = plantType.text.toString()
            val location = plantLocation.text.toString()
            val picture = R.drawable.default_image  // Replace with actual image logic if needed

            // Validation
            if (type.isEmpty() || location.isEmpty()) {
                Toast.makeText(this, "Please fill all fields", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            // Create updated plant model
            val updatedPlant = plant?.copy(
                type = type,
                location = location,
                picture = picture
            )

            // Update the plant in the repository via ViewModel
            updatedPlant?.let { viewModel.updatePlant(it) }

            // Close the activity and go back to MainActivity
            setResult(Activity.RESULT_OK)
            finish()
        }
    }
}
