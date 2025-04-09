package org.example.Observer;

import org.example.Factory.Character;

public interface HealthObserver { //Allows objects (observers) to be notified automatically when another object (subject) changes.

    void onHealthChanged(Character character);
}
