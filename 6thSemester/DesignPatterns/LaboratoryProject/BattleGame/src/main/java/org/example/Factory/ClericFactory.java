package org.example.Factory;

public class ClericFactory implements CharacterFactory {
    @Override
    public Character createCharacter() {
        return new Character("Cleric", 80, 5, 20, 25);
    }
}
