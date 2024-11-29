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
import com.example.plantkeeper.data.PlantModel
import com.example.plantkeeper.viewModel.PlantViewModel
import java.text.SimpleDateFormat
import java.util.Calendar
import java.util.Locale
import java.util.Date

class CreateActivity : AppCompatActivity() {

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
    private lateinit var btnSavePlant: Button
    private lateinit var btnBack: ImageView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_create)

        // Initialize views
        plantType = findViewById(R.id.plant_type)
        plantLocation = findViewById(R.id.plant_location)
        plantPicture = findViewById(R.id.plant_picture)
        plantDateAcquired = findViewById(R.id.plant_date_acquired)
        plantTreatment = findViewById(R.id.plant_treatment)
        plantLastTreated = findViewById(R.id.plant_last_treated)
        plantNotes = findViewById(R.id.plant_notes)
        plantMotherPlant = findViewById(R.id.plant_mother)
        plantPropagations = findViewById(R.id.plant_propagations)
        btnSavePlant = findViewById(R.id.btn_save_plant)
        btnBack = findViewById(R.id.btn_back)

        // Initialize ViewModel
        viewModel = ViewModelProvider(this).get(PlantViewModel::class.java)

        // Set up date picker dialogs
        plantDateAcquired.setOnClickListener { showDatePickerDialog { date -> plantDateAcquired.setText(date) } }
        plantLastTreated.setOnClickListener { showDatePickerDialog { date -> plantLastTreated.setText(date) } }

        // Save plant logic
        btnSavePlant.setOnClickListener {
            val type = plantType.text.toString()
            val location = plantLocation.text.toString()

            val dateAcquired = parseDate(plantDateAcquired.text.toString())
            val lastTreated = parseDate(plantLastTreated.text.toString())
            val treatment = plantTreatment.text.toString()
            val notes = plantNotes.text.toString()
            val motherPlant = plantMotherPlant.text.toString()
            val propagations = plantPropagations.text.toString().split(",").map { it.trim() }.toMutableList()

            if (type.isEmpty() || location.isEmpty()) {
                Toast.makeText(this, "Please fill all required fields", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            val newPlant = PlantModel(
                id = generateUniqueId(),
                type = type,
                location = location,
                picture = null, // Assuming you have a way to set this, or set a default
                dateAquired = dateAcquired,
                treatment = treatment,
                lastTreated = lastTreated,
                notes = notes,
                motherPlant = motherPlant,
                propagations = propagations
            )

            viewModel.addPlant(newPlant)

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

    private fun generateUniqueId(): String {
        return java.util.UUID.randomUUID().toString()
    }
}
