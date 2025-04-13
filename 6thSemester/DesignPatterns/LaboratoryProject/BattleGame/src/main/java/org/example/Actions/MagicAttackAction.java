package org.example.Actions;

import org.example.Factory.Character;

public class MagicAttackAction implements Action {
    private Character attacker, defender;
    private int damage;
    public MagicAttackAction(Character attacker, Character defender) {
        this.attacker = attacker;
        this.defender = defender;
    }
    @Override
    public void execute() {
        damage = attacker.getMagicDamage();
        defender.takeDamage(damage);
        System.out.println(attacker.getName() + " hits " + defender.getName() + " with magic for " + damage + " damage.");
    }
    @Override
    public void unexecute() {
        defender.heal(damage);
        System.out.println(attacker.getName() + " undo magic attack on " + defender.getName() + " for " + damage + " HP.");
    }
}
