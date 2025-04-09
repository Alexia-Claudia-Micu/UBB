package org.example.Factory;

public class PaladinFactory implements CharacterFactory {
    @Override
    public Character createCharacter() {
        return new Character("Paladin", 95, 25, 25, 15);
    }
}
