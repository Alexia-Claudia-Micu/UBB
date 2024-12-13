import 'dart:io';
import 'package:intl/intl.dart';
import 'package:path/path.dart';
import 'package:path_provider/path_provider.dart';
import 'package:sqflite/sqflite.dart';

import '../Plant.dart';

class PlantDatabaseRepo {
  static const _dbName = "plants.db";
  static const _dbVersion = 1;
  static const _table = "plant";

  // Singleton pattern
  PlantDatabaseRepo._();

  static final PlantDatabaseRepo dbInstance = PlantDatabaseRepo._();

  static Database? _database;

  Future<Database> get database async => _database ??= await _initDatabase();

  Future<Database> _initDatabase() async {
    Directory documentsDirectory = await getApplicationDocumentsDirectory();
    String path = join(documentsDirectory.path, _dbName);

    return await openDatabase(
      path,
      version: _dbVersion,
      onCreate: _onCreate,
    );
  }

  void _onCreate(Database db, int version) async {
    await db.execute('''CREATE TABLE $_table
        (
          id INTEGER PRIMARY KEY AUTOINCREMENT,
          type TEXT NOT NULL,
          dateAcquired TEXT,
          location TEXT,
          treatment TEXT,
          lastTreated TEXT,
          notes TEXT,
          motherPlant TEXT,
          propagations TEXT
        )''');
  }

  Future<List<Plant>> getPlants() async {
    Database db = await dbInstance.database;
    var plants = await db.query(_table);

    List<Plant> plantList = plants.isNotEmpty
        ? plants.map((p) => Plant.fromMap(p)).toList()
        : [];

    return plantList;
  }

  Future<int> addPlant(Plant plant) async {
    Database db = await dbInstance.database;
    return await db.insert(_table, plant.toMap());
  }

  Future<int> removePlant(int id) async {
    Database db = await dbInstance.database;
    return await db.delete(_table, where: 'id = ?', whereArgs: [id]);
  }

  Future<int> updatePlant(Plant plant) async {
    Database db = await dbInstance.database;
    return await db.update(_table, plant.toMap(), where: 'id = ?', whereArgs: [plant.id]);
  }

  Future<void> addInitialData() async {
    List<Plant> initialPlants = [
      Plant(
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

    for (var plant in initialPlants) {
      await addPlant(plant);
    }
  }
}
