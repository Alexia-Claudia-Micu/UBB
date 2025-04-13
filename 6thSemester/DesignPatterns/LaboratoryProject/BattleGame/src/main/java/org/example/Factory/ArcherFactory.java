package org.example.Factory;

public class ArcherFactory implements CharacterFactory {
    @Override
    public Character createCharacter() {
        return new Character("Archer", 90, 20, 20, 10);
    }
}
