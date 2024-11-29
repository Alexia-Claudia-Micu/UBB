import 'package:intl/intl.dart';

class Plant {
  static int currentId = 0; // Counter for generating unique IDs
  late int id;              // Unique ID for the plant
  String type;
  DateTime? dateAcquired;
  String? location;
  String? treatment;
  DateTime? lastTreated;
  String? notes;
  String? motherPlant;
  List<String>? propagations;

  // Constructor to initialize plant properties
  Plant({
    required this.type,
    this.dateAcquired,
    this.location,
    this.treatment,
    this.lastTreated,
    this.notes,
    this.motherPlant,
    this.propagations,
  }) {
    id = currentId++; // Assign a unique ID and increment the counter
  }

  // Factory constructor to create a plant from an existing plant's data
  Plant.fromPlant(
      this.id,
      this.type,
      this.dateAcquired,
      this.location,
      this.treatment,
      this.lastTreated,
      this.notes,
      this.motherPlant,
      this.propagations,
      );

  // Static method to initialize a list of sample plants
  static List<Plant> init() {
    List<Plant> plants = [
      Plant(
        type: "Fern",
        dateAcquired: DateTime.parse(
            DateFormat('yyyy-MM-dd').format(DateTime(2020, 01, 15))),
        location: "Living Room",
        treatment: "Water twice a week",
        lastTreated: DateTime.parse(
            DateFormat('yyyy-MM-dd').format(DateTime(2024, 11, 10))),
        notes: "Thrives in indirect sunlight",
        motherPlant: "Fern A",
        propagations: ["Fern B", "Fern C"],
      ),
      Plant(
        type: "Cactus",
        dateAcquired: DateTime.parse(
            DateFormat('yyyy-MM-dd').format(DateTime(2019, 05, 20))),
        location: "Office Desk",
        treatment: "Water monthly",
        lastTreated: DateTime.parse(
            DateFormat('yyyy-MM-dd').format(DateTime(2024, 10, 01))),
        notes: "Avoid overwatering",
        motherPlant: null,
        propagations: [],
      ),
      Plant(
        type: "Snake Plant",
        dateAcquired: DateTime.parse(
            DateFormat('yyyy-MM-dd').format(DateTime(2021, 07, 10))),
        location: "Bedroom",
        treatment: "Water once a week",
        lastTreated: DateTime.parse(
            DateFormat('yyyy-MM-dd').format(DateTime(2024, 11, 15))),
        notes: "Improves indoor air quality",
        motherPlant: null,
        propagations: ["Snake Plant A"],
      ),
    ];

    return plants;
  }
}
