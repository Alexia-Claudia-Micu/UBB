package org.example.Factory;

import org.example.Observer.HealthObserver;
import org.example.Strategy.BattleStrategy;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;


public class Character { //Creates objects without exposing the instantiation logic to the client.
    private String name;
    private int health;
    private int meleeAttack;
    private int magicAttack;
    private int defense;
    private BattleStrategy battleStrategy;  // Strategy pattern reference

    private double damageMultiplier = 1.0;
    private double healMultiplier = 1.0;
    private double damageResistance = 1.0;

    private List<HealthObserver> observers = new ArrayList<>();


    // Constructor
    public Character(String name, int health, int meleePower, int magicPower, int defense) {
        this.name = name;
        this.health = health;
        this.meleeAttack = meleePower;
        this.magicAttack = magicPower;
        this.defense = defense;
    }

    // Setters and getters
    public String getName() {
        return name;
    }

    public int getHealth() {
        return health;
    }

    public int getMeleeDamage() {
        Random random = new Random();
        int randomInt = random.nextInt(11) - 5;
        return (int)((meleeAttack + randomInt) * damageMultiplier);
    }

    public int getMagicDamage() {
        Random random = new Random();
        int randomInt = random.nextInt(11) - 5;
        return (int)((magicAttack + randomInt) * damageMultiplier);
    }

    public void takeDamage(int damage) {
        int reduced = (int)(damage * damageResistance);
        this.health -= reduced;
        if (this.health < 0) this.health = 0;
        System.out.println(this.name + " takes " + reduced + " damage!");
        notifyObservers();
    }

    public void heal(int amount) {
        int effectiveHeal = (int)(amount * healMultiplier);
        this.health += effectiveHeal;
        System.out.println(this.name + " heals for " + effectiveHeal + " health!");
        notifyObservers();
    }


    public void addObserver(HealthObserver observer) {
        observers.add(observer);
    }

    private void notifyObservers() {
        for (HealthObserver observer : observers) {
            observer.onHealthChanged(this);
        }
    }


    public int getDefense() {
        return defense;
    }

    public void defend() {
        System.out.println(this.name + " is defending!");
        this.defense += 5;
    }

    public void setBattleStrategy(BattleStrategy strategy) {
        this.battleStrategy = strategy;
    }

    public BattleStrategy getBattleStrategy() {
        return this.battleStrategy;
    }

    public void setDamageMultiplier(double multiplier) {
        this.damageMultiplier = multiplier;
    }

    public void setHealMultiplier(double multiplier) {
        this.healMultiplier = multiplier;
    }

    public void setDamageResistance(double resistance) {
        this.damageResistance = resistance;
    }

    public void resetModifiers() {
        damageMultiplier = 1.0;
        healMultiplier = 1.0;
        damageResistance = 1.0;
    }


}
