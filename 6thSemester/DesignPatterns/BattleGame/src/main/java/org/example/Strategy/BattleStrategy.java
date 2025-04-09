package org.example.Strategy;
import org.example.Factory.Character;

// Strategy Interface
public interface BattleStrategy { //Encapsulates different algorithms or behaviors and lets you switch between them at runtime.

    void execute(Character attacker, Character defender);
}

