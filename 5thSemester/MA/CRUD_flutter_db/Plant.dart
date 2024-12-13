import 'package:intl/intl.dart';

class Plant {
  int? id;
  String type;
  DateTime? dateAcquired;
  String? location;
  String? treatment;
  DateTime? lastTreated;
  String? notes;
  String? motherPlant;
  List<String>? propagations;

  Plant({
    this.id,
    required this.type,
    this.dateAcquired,
    this.location,
    this.treatment,
    this.lastTreated,
    this.notes,
    this.motherPlant,
    this.propagations,
  });

  // Convert Plant object to Map for database operations
  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'type': type,
      'dateAcquired': dateAcquired?.toIso8601String(),
      'location': location,
      'treatment': treatment,
      'lastTreated': lastTreated?.toIso8601String(),
      'notes': notes,
      'motherPlant': motherPlant,
      'propagations': propagations?.join(","),
    };
  }

  // Create Plant object from Map
  factory Plant.fromMap(Map<String, dynamic> map) {
    return Plant(
      id: map['id'],
      type: map['type'],
      dateAcquired: map['dateAcquired'] != null
          ? DateTime.parse(map['dateAcquired'])
          : null,
      location: map['location'],
      treatment: map['treatment'],
      lastTreated: map['lastTreated'] != null
          ? DateTime.parse(map['lastTreated'])
          : null,
      notes: map['notes'],
      motherPlant: map['motherPlant'],
      propagations: map['propagations'] is String
          ? (map['propagations'] as String).split(",").where((e) => e.isNotEmpty).toList()
          : [],
    );
  }


  // Add the `fromPlant` constructor
  static Plant fromPlant(
      int? id,
      String type,
      DateTime? dateAcquired,
      String? location,
      String? treatment,
      DateTime? lastTreated,
      String? notes,
      String? motherPlant,
      List<String>? propagations,
      ) {
    return Plant(
      id: id,
      type: type,
      dateAcquired: dateAcquired,
      location: location,
      treatment: treatment,
      lastTreated: lastTreated,
      notes: notes,
      motherPlant: motherPlant,
      propagations: propagations,
    );
  }

  static List<Plant> init() {
    return [
      Plant(
        id: 1,
        type: "Fern",
        dateAcquired: DateTime.now().subtract(Duration(days: 30)),
        location: "Living Room",
        treatment: "Water Weekly",
        lastTreated: DateTime.now().subtract(Duration(days: 7)),
        notes: "Looks healthy.",
        motherPlant: null,
        propagations: [],
      ),
      Plant(
        id: 2,
        type: "Cactus",
        dateAcquired: DateTime.now().subtract(Duration(days: 90)),
        location: "Bedroom",
        treatment: "Water Monthly",
        lastTreated: DateTime.now().subtract(Duration(days: 14)),
        notes: "Thriving well.",
        motherPlant: null,
        propagations: ["Cutting 1"],
      ),
    ];
  }
}
