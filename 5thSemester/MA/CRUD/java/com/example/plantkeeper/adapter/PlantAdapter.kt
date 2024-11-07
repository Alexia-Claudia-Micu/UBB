package com.example.plantkeeper

import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.plantkeeper.data.PlantModel

class PlantAdapter(
    private val onDeleteClick: (String) -> Unit,
    private val onItemClick: (String) -> Unit
) : RecyclerView.Adapter<PlantAdapter.PlantViewHolder>() {

    private var plants: List<PlantModel> = emptyList()

    inner class PlantViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        val plantName: TextView = view.findViewById(R.id.plant_name)
        val plantLocation: TextView = view.findViewById(R.id.plant_location)
        val deleteButton: Button = view.findViewById(R.id.delete_button)
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): PlantViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.plant_item, parent, false)
        return PlantViewHolder(view)
    }

    override fun onBindViewHolder(holder: PlantViewHolder, position: Int) {
        val plant = plants[position]
        holder.plantName.text = plant.type
        holder.plantLocation.text = plant.location

        // Set up delete button click
        holder.deleteButton.setOnClickListener { onDeleteClick(plant.id) }

        // Set up item click for navigating to UpdateActivity
        holder.itemView.setOnClickListener { onItemClick(plant.id) }
    }

    override fun getItemCount(): Int = plants.size

    fun setPlants(newPlants: List<PlantModel>) {
        this.plants = newPlants
        notifyDataSetChanged()
    }
}
