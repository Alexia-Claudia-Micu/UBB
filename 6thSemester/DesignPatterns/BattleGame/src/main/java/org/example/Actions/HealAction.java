package org.example.Actions;

import org.example.Factory.Character;
import java.util.Random;

public class HealAction implements Action {
    private Character character;
    private int healAmount;

    public HealAction(Character character) {
        this.character = character;
    }

    @Override
    public void execute() {
        Random random = new Random();
        healAmount = random.nextInt(16) + 5;
        character.heal(healAmount);
        System.out.println(character.getName() + " heals for " + healAmount + " HP.");
    }

    @Override
    public void unexecute() {
        character.takeDamage(healAmount);
        System.out.println(character.getName() + " undo heal for " + healAmount + " HP.");
    }
}
