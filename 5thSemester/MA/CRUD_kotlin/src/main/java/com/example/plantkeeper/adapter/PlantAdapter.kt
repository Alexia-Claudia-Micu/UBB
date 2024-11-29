package com.example.plantkeeper

import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.plantkeeper.data.PlantModel

class PlantAdapter(
    private val onDeleteClick: (String) -> Unit,
    private val onItemClick: (String) -> Unit
) : RecyclerView.Adapter<PlantAdapter.PlantViewHolder>() {

    private var plantList: List<PlantModel> = listOf()

    fun setPlants(plants: List<PlantModel>) {
        plantList = plants
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): PlantViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.plant_item, parent, false)
        return PlantViewHolder(view)
    }

    override fun onBindViewHolder(holder: PlantViewHolder, position: Int) {
        val plant = plantList[position]
        holder.bind(plant)
    }

    override fun getItemCount(): Int = plantList.size

    inner class PlantViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        private val plantImage: ImageView = itemView.findViewById(R.id.plant_image)
        private val plantName: TextView = itemView.findViewById(R.id.plant_name)
        private val plantLocation: TextView = itemView.findViewById(R.id.plant_location)
        private val deleteButton: ImageView = itemView.findViewById(R.id.delete_button)

        fun bind(plant: PlantModel) {
            // Set the name and location
            plantName.text = plant.type
            plantLocation.text = plant.location

            // Set the plant image dynamically from the model (using `plant.picture` resource ID)
            plant.picture?.let {
                plantImage.setImageResource(it)
            }

            // Set up the delete button action
            deleteButton.setOnClickListener {
                onDeleteClick(plant.id)
            }

            // Handle item click to navigate to update page or details
            itemView.setOnClickListener {
                onItemClick(plant.id)
            }
        }
    }
}
