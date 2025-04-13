package org.example.Actions;

import org.example.Factory.Character;

public class MeleeAttackAction implements Action {
    private Character attacker, defender;
    private int damage;

    public MeleeAttackAction(Character attacker, Character defender) {
        this.attacker = attacker;
        this.defender = defender;
    }

    @Override
    public void execute() {
        damage = attacker.getMeleeDamage();
        defender.takeDamage(damage);
        System.out.println(attacker.getName() + " hits " + defender.getName() + " with melee for " + damage + " damage.");
    }

    @Override
    public void unexecute() {
        defender.heal(damage);
        System.out.println(attacker.getName() + " undo melee attack on " + defender.getName() + " for " + damage + " HP.");
    }
}
