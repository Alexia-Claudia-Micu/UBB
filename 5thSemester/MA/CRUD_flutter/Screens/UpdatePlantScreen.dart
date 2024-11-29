import 'package:flutter/material.dart';
import 'package:intl/intl.dart';

import '../Plant.dart';

class UpdatePlantScreen extends StatefulWidget {
  final Plant plant;

  const UpdatePlantScreen({super.key, required this.plant});

  @override
  State<UpdatePlantScreen> createState() => _UpdatePlantScreenState();
}

class _UpdatePlantScreenState extends State<UpdatePlantScreen> {
  final _formKey = GlobalKey<FormState>();

  // Utility function to validate date input
  bool isValidDate(String stringToTest) {
    try {
      DateFormat('yyyy-MM-dd').parseStrict(stringToTest);
    } catch (_) {
      return false;
    }
    return true;
  }

  @override
  Widget build(BuildContext context) {
    // Local variables to hold field values
    String typeValue = widget.plant.type;
    String locationValue = widget.plant.location ?? '';
    String treatmentValue = widget.plant.treatment ?? '';
    String dateAcquiredValue =
    widget.plant.dateAcquired != null ? DateFormat('yyyy-MM-dd').format(widget.plant.dateAcquired!) : '';
    String lastTreatedValue =
    widget.plant.lastTreated != null ? DateFormat('yyyy-MM-dd').format(widget.plant.lastTreated!) : '';
    String notesValue = widget.plant.notes ?? '';

    return Scaffold(
      backgroundColor: Colors.lightGreen.shade100,
      appBar: AppBar(
        backgroundColor: Colors.green.shade700,
        title: const Text("Update Plant Details"),
      ),
      body: Form(
        key: _formKey,
        child: SingleChildScrollView(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            children: [
              buildInputField(
                label: 'Type',
                initialValue: typeValue,
                onChanged: (value) => typeValue = value,
              ),
              buildInputField(
                label: 'Location',
                initialValue: locationValue,
                onChanged: (value) => locationValue = value,
              ),
              buildInputField(
                label: 'Treatment',
                initialValue: treatmentValue,
                onChanged: (value) => treatmentValue = value,
              ),
              buildInputField(
                label: 'Date Acquired',
                initialValue: dateAcquiredValue,
                onChanged: (value) => dateAcquiredValue = value,
                validator: (value) {
                  if (value != null && value.isNotEmpty && !isValidDate(value)) {
                    return 'Enter a valid date (yyyy-MM-dd)';
                  }
                  return null;
                },
              ),
              buildInputField(
                label: 'Last Treated',
                initialValue: lastTreatedValue,
                onChanged: (value) => lastTreatedValue = value,
                validator: (value) {
                  if (value != null && value.isNotEmpty && !isValidDate(value)) {
                    return 'Enter a valid date (yyyy-MM-dd)';
                  }
                  return null;
                },
              ),
              buildInputField(
                label: 'Notes',
                initialValue: notesValue,
                onChanged: (value) => notesValue = value,
                maxLines: 3,
              ),
              const SizedBox(height: 16.0),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: [
                  ElevatedButton(
                    onPressed: () {
                      if (_formKey.currentState!.validate()) {
                        Navigator.pop(
                          context,
                          Plant.fromPlant(
                            widget.plant.id,
                            typeValue,
                            dateAcquiredValue.isNotEmpty
                                ? DateFormat('yyyy-MM-dd').parse(dateAcquiredValue)
                                : null,
                            locationValue,
                            treatmentValue,
                            lastTreatedValue.isNotEmpty
                                ? DateFormat('yyyy-MM-dd').parse(lastTreatedValue)
                                : null,
                            notesValue,
                            widget.plant.motherPlant,
                            widget.plant.propagations,
                          ),
                        );
                      }
                    },
                    child: const Text("Save"),
                  ),
                  ElevatedButton(
                    onPressed: () => Navigator.pop(context),
                    style: ElevatedButton.styleFrom(
                      backgroundColor: Colors.red,
                    ),
                    child: const Text("Cancel"),
                  ),
                ],
              ),
            ],
          ),
        ),
      ),
    );
  }

  // Helper method to create a text input field
  Widget buildInputField({
    required String label,
    required String initialValue,
    required ValueChanged<String> onChanged,
    FormFieldValidator<String>? validator,
    int maxLines = 1,
  }) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 8.0),
      child: TextFormField(
        initialValue: initialValue,
        onChanged: onChanged,
        validator: validator ??
                (value) {
              if (value == null || value.isEmpty) {
                return 'Please enter $label';
              }
              return null;
            },
        maxLines: maxLines,
        decoration: InputDecoration(
          labelText: label,
          border: const OutlineInputBorder(),
          filled: true,
          fillColor: Colors.white,
        ),
      ),
    );
  }
}
