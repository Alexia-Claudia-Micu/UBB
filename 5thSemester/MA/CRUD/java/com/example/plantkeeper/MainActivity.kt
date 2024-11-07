package com.example.plantkeeper

import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.widget.Button
import androidx.activity.viewModels
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.ViewModelProvider
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.plantkeeper.viewModel.PlantViewModel

class MainActivity : AppCompatActivity() {

    private lateinit var viewModel: PlantViewModel
    private lateinit var adapter: PlantAdapter

    companion object {
        private const val REQUEST_CODE_CREATE = 1
        private const val REQUEST_CODE_UPDATE = 2
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Initialize ViewModel (scoped to this activity)
        viewModel = ViewModelProvider(this).get(PlantViewModel::class.java)

        // Initialize Adapter with delete action
        adapter = PlantAdapter(
            onDeleteClick = { plantId -> viewModel.deletePlant(plantId) },
            onItemClick = { plantId ->
                // Start UpdateActivity and pass the plant ID for updating
                val intent = Intent(this, UpdateActivity::class.java)
                intent.putExtra("plantId", plantId)
                startActivityForResult(intent, REQUEST_CODE_UPDATE)
            }
        )

        // Set up RecyclerView with Adapter and LayoutManager
        val recyclerView: RecyclerView = findViewById(R.id.recycler_view)
        recyclerView.adapter = adapter
        recyclerView.layoutManager = LinearLayoutManager(this)

        // Observe LiveData from ViewModel and update RecyclerView
        viewModel.plants.observe(this) { plants ->
            adapter.setPlants(plants)
        }

        // Set up Add Plant button to start CreateActivity
        val btnAddPlant: Button = findViewById(R.id.btn_add_plant)
        btnAddPlant.setOnClickListener {
            val intent = Intent(this, CreateActivity::class.java)
            startActivityForResult(intent, REQUEST_CODE_CREATE)
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)

        if (resultCode == Activity.RESULT_OK) {
            when (requestCode) {
                REQUEST_CODE_CREATE -> {
                    // Force the ViewModel to refresh the plant list when returning from CreateActivity
                    viewModel.getPlants()  // Refresh plants after returning from CreateActivity
                }
                REQUEST_CODE_UPDATE -> {
                    // Refresh the plant list after updating a plant
                    viewModel.getPlants()
                }
            }
        }
    }
}


