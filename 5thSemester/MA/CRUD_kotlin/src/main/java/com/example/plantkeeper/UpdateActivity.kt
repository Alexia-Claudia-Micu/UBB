package com.example.plantkeeper

import android.app.Activity
import android.app.DatePickerDialog
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.ViewModelProvider
import com.example.plantkeeper.viewModel.PlantViewModel
import java.text.SimpleDateFormat
import java.util.Calendar
import java.util.Locale
import java.util.Date

class UpdateActivity : AppCompatActivity() {

    private lateinit var viewModel: PlantViewModel
    private lateinit var plantType: EditText
    private lateinit var plantLocation: EditText
    private lateinit var plantPicture: ImageView
    private lateinit var plantDateAcquired: EditText
    private lateinit var plantTreatment: EditText
    private lateinit var plantLastTreated: EditText
    private lateinit var plantNotes: EditText
    private lateinit var plantMotherPlant: EditText
    private lateinit var plantPropagations: EditText
    private lateinit var btnUpdatePlant: Button
    private lateinit var btnBack: ImageView
    private lateinit var plantId: String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_update)

        // Initialize views
        plantType = findViewById(R.id.plant_type)
        plantLocation = findViewById(R.id.plant_location)
        plantPicture = findViewById(R.id.plant_picture)
        plantDateAcquired = findViewById(R.id.plant_date_acquired)
        plantTreatment = findViewById(R.id.plant_treatment)
        plantLastTreated = findViewById(R.id.plant_last_treated)
        plantNotes = findViewById(R.id.plant_notes)
        plantMotherPlant = findViewById(R.id.plant_mother_plant)
        plantPropagations = findViewById(R.id.plant_propagations)
        btnUpdatePlant = findViewById(R.id.btn_update_plant)
        btnBack = findViewById(R.id.btn_back)

        // Get data from intent
        plantId = intent.getStringExtra("plantId") ?: return

        // Initialize ViewModel
        viewModel = ViewModelProvider(this).get(PlantViewModel::class.java)

        // Populate fields with current plant details
        val plant = viewModel.getPlantById(plantId)
        plant?.let {
            plant.picture?.let {
                plantPicture.setImageResource(it)
            } ?: plantPicture.setImageResource(R.drawable.default_image)
            plantType.setText(it.type)
            plantLocation.setText(it.location)
            plantDateAcquired.setText(it.dateAquired?.let { date -> formatDate(date) })
            plantTreatment.setText(it.treatment)
            plantLastTreated.setText(it.lastTreated?.let { date -> formatDate(date) })
            plantNotes.setText(it.notes)
            plantMotherPlant.setText(it.motherPlant)
            plantPropagations.setText(it.propagations?.joinToString(", "))
        }

        // Set up date picker dialogs
        plantDateAcquired.setOnClickListener { showDatePickerDialog { date -> plantDateAcquired.setText(date) } }
        plantLastTreated.setOnClickListener { showDatePickerDialog { date -> plantLastTreated.setText(date) } }

        // Update plant logic
        btnUpdatePlant.setOnClickListener {
            val type = plantType.text.toString()
            val location = plantLocation.text.toString()

            val dateAcquired = plantDateAcquired.text.toString().let {
                parseDate(it) ?: plant?.dateAquired // Fallback to original date if parsing fails
            }

            val lastTreated = plantLastTreated.text.toString().let {
                parseDate(it) ?: plant?.lastTreated // Fallback to original date if parsing fails
            }

            val treatment = plantTreatment.text.toString()
            val notes = plantNotes.text.toString()
            val motherPlant = plantMotherPlant.text.toString()
            val propagations = plantPropagations.text.toString().split(",").map { it.trim() }.toMutableList()

            if (type.isEmpty() || location.isEmpty()) {
                Toast.makeText(this, "Please fill all required fields", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            val updatedPlant = plant?.copy(
                type = type,
                location = location,
                dateAquired = dateAcquired,
                treatment = treatment,
                lastTreated = lastTreated,
                notes = notes,
                motherPlant = motherPlant,
                propagations = propagations
            )

            updatedPlant?.let { viewModel.updatePlant(it) }

            setResult(Activity.RESULT_OK)
            finish()
        }

        // Back button logic
        btnBack.setOnClickListener {
            setResult(Activity.RESULT_CANCELED)
            finish()
        }
    }

    private fun showDatePickerDialog(onDateSet: (String) -> Unit) {
        val calendar = Calendar.getInstance()
        val year = calendar.get(Calendar.YEAR)
        val month = calendar.get(Calendar.MONTH)
        val day = calendar.get(Calendar.DAY_OF_MONTH)

        val datePickerDialog = DatePickerDialog(
            this,
            { _, selectedYear, selectedMonth, selectedDay ->
                val selectedDate = Calendar.getInstance().apply {
                    set(selectedYear, selectedMonth, selectedDay)
                }
                onDateSet(formatDate(selectedDate.time))
            },
            year,
            month,
            day
        )
        datePickerDialog.show()
    }

    private fun formatDate(date: Date): String {
        val dateFormat = SimpleDateFormat("yyyy-MM-dd", Locale.getDefault())
        return dateFormat.format(date)
    }

    private fun parseDate(dateString: String): Date? {
        return try {
            if (dateString.isNotEmpty()) SimpleDateFormat("yyyy-MM-dd", Locale.getDefault()).parse(dateString)
            else null
        } catch (e: Exception) {
            null
        }
    }
}
