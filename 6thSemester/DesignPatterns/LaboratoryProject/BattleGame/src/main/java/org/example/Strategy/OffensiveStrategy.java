package org.example.Strategy;

import org.example.Factory.Character;

public class OffensiveStrategy implements BattleStrategy {
    @Override
    public void execute(Character self, Character opponent) {
        System.out.println(self.getName() + " adopts an Offensive Strategy! Damage increased.");
        self.setDamageMultiplier(1.3); // 30% more damage
    }
}
