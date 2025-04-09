package org.example.Strategy;

import org.example.Factory.Character;

public class HealerStrategy implements BattleStrategy {
    @Override
    public void execute(Character self, Character opponent) {
        System.out.println(self.getName() + " adopts a Healer Strategy! Healing is more effective.");
        self.setHealMultiplier(1.4); // Heals 40% more
    }
}
