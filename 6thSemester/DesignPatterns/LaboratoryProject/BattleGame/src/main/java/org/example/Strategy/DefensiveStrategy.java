package org.example.Strategy;

import org.example.Factory.Character;

public class DefensiveStrategy implements BattleStrategy {
    @Override
    public void execute(Character self, Character opponent) {
        System.out.println(self.getName() + " adopts a Defensive Strategy! Damage taken reduced.");
        self.setDamageResistance(0.7); // Takes 30% less damage
    }
}
