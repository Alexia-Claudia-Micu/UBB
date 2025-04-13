package org.example.Factory;

public class WarriorFactory implements CharacterFactory {
    @Override
    public Character createCharacter() {
        return new Character("Warrior", 100, 30, 5, 15);
    }
}
