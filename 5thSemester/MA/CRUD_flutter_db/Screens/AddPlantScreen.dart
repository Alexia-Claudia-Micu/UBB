
import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import '../Plant.dart';

class AddPlantScreen extends StatefulWidget {
  const AddPlantScreen({Key? key}) : super(key: key);

  @override
  State<AddPlantScreen> createState() => _AddPlantScreenState();
}

class _AddPlantScreenState extends State<AddPlantScreen> {
  final _formKey = GlobalKey<FormState>();

  String typeValue = "";
  String locationValue = "";
  String treatmentValue = "";
  String notesValue = "";
  String motherPlantValue = "";
  String dateAcquiredValue = "";
  String lastTreatedValue = "";
  List<String> propagationsValue = [];

  bool isValidDate(String stringToTest) {
    try {
      DateFormat('yyyy-MM-dd').parseStrict(stringToTest);
    } catch (e) {
      return false;
    }
    return true;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.green.shade200,
      body: SingleChildScrollView(
        child: Form(
          key: _formKey,
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Padding(
                padding: const EdgeInsets.all(20.0),
                child: Text(
                  'Add New Plant',
                  style: TextStyle(
                    fontSize: 32,
                    fontWeight: FontWeight.bold,
                    color: Colors.black87,
                  ),
                ),
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 20.0),
                child: TextFormField(
                  decoration: const InputDecoration(
                    labelText: 'Type',
                    filled: true,
                    fillColor: Colors.white70,
                  ),
                  validator: (value) =>
                  value == null || value.isEmpty ? "Enter the plant type" : null,
                  onChanged: (value) => typeValue = value,
                ),
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 20.0, vertical: 10.0),
                child: TextFormField(
                  decoration: const InputDecoration(
                    labelText: 'Location',
                    filled: true,
                    fillColor: Colors.white70,
                  ),
                  onChanged: (value) => locationValue = value,
                ),
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 20.0),
                child: TextFormField(
                  decoration: const InputDecoration(
                    labelText: 'Treatment',
                    filled: true,
                    fillColor: Colors.white70,
                  ),
                  onChanged: (value) => treatmentValue = value,
                ),
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 20.0, vertical: 10.0),
                child: TextFormField(
                  decoration: const InputDecoration(
                    labelText: 'Notes',
                    filled: true,
                    fillColor: Colors.white70,
                  ),
                  onChanged: (value) => notesValue = value,
                ),
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 20.0),
                child: TextFormField(
                  decoration: const InputDecoration(
                    labelText: 'Mother Plant',
                    filled: true,
                    fillColor: Colors.white70,
                  ),
                  onChanged: (value) => motherPlantValue = value,
                ),
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 20.0, vertical: 10.0),
                child: TextFormField(
                  decoration: const InputDecoration(
                    labelText: 'Date Acquired (yyyy-MM-dd)',
                    filled: true,
                    fillColor: Colors.white70,
                  ),
                  validator: (value) => value == null || value.isEmpty
                      ? "Enter the date acquired"
                      : (!isValidDate(value)
                      ? "Use format: yyyy-MM-dd"
                      : null),
                  onChanged: (value) => dateAcquiredValue = value,
                ),
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 20.0),
                child: TextFormField(
                  decoration: const InputDecoration(
                    labelText: 'Last Treated (yyyy-MM-dd)',
                    filled: true,
                    fillColor: Colors.white70,
                  ),
                  validator: (value) => value != null && value.isNotEmpty && !isValidDate(value)
                      ? "Use format: yyyy-MM-dd"
                      : null,
                  onChanged: (value) => lastTreatedValue = value,
                ),
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 20.0, vertical: 20.0),
                child: ElevatedButton(
                  onPressed: () {
                    if (_formKey.currentState!.validate()) {
                      Plant newPlant = Plant(
                        type: typeValue,
                        dateAcquired: dateAcquiredValue.isEmpty
                            ? null
                            : DateTime.parse(dateAcquiredValue),
                        location: locationValue,
                        treatment: treatmentValue,
                        lastTreated: lastTreatedValue.isEmpty
                            ? null
                            : DateTime.parse(lastTreatedValue),
                        notes: notesValue,
                        motherPlant: motherPlantValue.isEmpty ? null : motherPlantValue,
                        propagations: propagationsValue,
                      );
                      Navigator.pop(context, newPlant);
                    }
                  },
                  child: const Text('Save'),
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
