import 'package:path/path.dart';
import 'package:sqflite/sqflite.dart';
import 'package:path_provider/path_provider.dart';
import 'dart:io';

class DatabaseConnection {
  static const dbName = "plants.db";
  static const dbVersion = 1;
  static const table = "plant"; // Remove the underscore to make it public

  DatabaseConnection._();
  static final DatabaseConnection instance = DatabaseConnection._();
  static Database? _database;

  Future<Database> get database async => _database ??= await _initDatabase();

  Future<Database> _initDatabase() async {
    Directory directory = await getApplicationDocumentsDirectory();
    String path = join(directory.path, dbName);

    return await openDatabase(
      path,
      version: dbVersion,
      onCreate: _onCreate,
    );
  }

  void _onCreate(Database db, int version) async {
    await db.execute('''
      CREATE TABLE $table (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        type TEXT NOT NULL,
        dateAcquired TEXT,
        location TEXT,
        treatment TEXT,
        lastTreated TEXT,
        notes TEXT,
        motherPlant TEXT,
        propagations TEXT
      )
    ''');
  }
}
