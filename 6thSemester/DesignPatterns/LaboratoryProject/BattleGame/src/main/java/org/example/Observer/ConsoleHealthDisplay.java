package org.example.Observer;

import org.example.Factory.Character;

public class ConsoleHealthDisplay implements HealthObserver {
    @Override
    public void onHealthChanged(Character character) {
        System.out.println("[Observer] " + character.getName() + " now has " + character.getHealth() + " HP.");
    }
}
