package org.example.Factory;

public class BardFactory implements CharacterFactory {
    @Override
    public Character createCharacter() {
        return new Character("Bard", 90, 15, 25, 20);
    }
}
