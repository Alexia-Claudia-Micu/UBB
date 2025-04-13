package org.example.Factory;

public class MageFactory implements CharacterFactory {
    @Override
    public Character createCharacter() {
        return new Character("Mage", 80, 5, 45, 5);
    }
}
