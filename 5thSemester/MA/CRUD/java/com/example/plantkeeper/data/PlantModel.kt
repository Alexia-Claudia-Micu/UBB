package com.example.plantkeeper.data

import java.util.Date

data class PlantModel (
    val id: String,
    var picture: Int?,
    var type: String = "plant",
    var dateAquired: Date?,
    var location: String?,
    var treatment: String?,
    var lastTreated: Date?,
    var notes: String?,
    var motherPlant: String?,
    var propagations: MutableList<String>?
)

