package org.example;

import org.example.Actions.*;
import org.example.Factory.*;
import org.example.Factory.Character;
import org.example.Observer.ConsoleHealthDisplay;
import org.example.Strategy.*;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;

public class GameControllerFacade {
    private Character player;
    private Character enemy;
    private final Scanner scanner = new Scanner(System.in);
    private final String[] availableTypes = {"Warrior", "Mage", "Archer", "Bard", "Paladin", "Cleric"};
    private final Map<String, CharacterFactory> factoryMap = new HashMap<>();
    public GameControllerFacade() {
        // Initialize factory map
        factoryMap.put("Warrior", new WarriorFactory());
        factoryMap.put("Mage", new MageFactory());
        factoryMap.put("Archer", new ArcherFactory());
        factoryMap.put("Bard", new BardFactory());
        factoryMap.put("Paladin", new PaladinFactory());
        factoryMap.put("Cleric", new ClericFactory());
    }
    public void startGame() {
        setupCharacters();
        setupStrategies();
        showInitialStatus();
        runBattleLoop();
        displayWinner();
    }
    private void setupCharacters() {
        System.out.println("Choose your character:");
        for (int i = 0; i < availableTypes.length; i++) {
            System.out.println((i + 1) + ") " + availableTypes[i]);
        }

        int playerChoice = getValidatedInput(1, availableTypes.length);
        String playerType = availableTypes[playerChoice - 1];

        player = factoryMap.get(playerType).createCharacter();

        // Randomly select a different enemy type
        String enemyType;
        do {
            enemyType = availableTypes[new Random().nextInt(availableTypes.length)];
        } while (enemyType.equals(playerType));

        enemy = factoryMap.get(enemyType).createCharacter();

        System.out.println("\nYou chose: " + player.getName());
        System.out.println("Your enemy is: " + enemy.getName());

        player.addObserver(new ConsoleHealthDisplay());
        enemy.addObserver(new ConsoleHealthDisplay());
    }
    private void setupStrategies() {
        System.out.println("\nChoose your strategy:");
        System.out.println("1) Offensive (boosts damage)");
        System.out.println("2) Defensive (reduces damage taken)");
        System.out.println("3) Healer (boosts healing)");

        int strategyChoice = getValidatedInput(1, 3);

        player.setBattleStrategy(createStrategy(strategyChoice));

        int enemyStrategyChoice = new Random().nextInt(3) + 1;
        enemy.setBattleStrategy(createStrategy(enemyStrategyChoice));

        System.out.print("Enemy strategy: ");
        System.out.println(strategyName(enemyStrategyChoice));
    }
    private void showInitialStatus() {
        System.out.println("\n--- Initial Health ---");
        System.out.println(player.getName() + " HP: " + player.getHealth());
        System.out.println(enemy.getName() + " HP: " + enemy.getHealth());
        System.out.println("\n--- Battle Start! ---");
    }
    private void runBattleLoop() {
        while (player.getHealth() > 0 && enemy.getHealth() > 0) {
            System.out.println("\nYour Turn:");
            playerTurn();

            if (enemy.getHealth() <= 0) break;

            System.out.println("\nEnemy Turn:");
            enemyTurn();

            System.out.println("\n--- End of Turn ---");
        }
    }
    private void displayWinner() {
        if (player.getHealth() > 0) {
            System.out.println("\n🎉 You win!");
        } else {
            System.out.println("\n💀 You lost!");
        }
    }
    private void playerTurn() {
        player.getBattleStrategy().execute(player, enemy);

        System.out.println("Choose action: 1) Melee 2) Magic 3) Heal");
        int choice = getValidatedInput(1, 3);

        Action action = createAction(choice, player, enemy);
        action.execute();

        player.resetModifiers();
    }
    private void enemyTurn() {
        enemy.getBattleStrategy().execute(enemy, player);

        Action action;
        if (enemy.getHealth() < 40) {
            action = new HealAction(enemy);
        } else {
            action = (Math.random() > 0.5) ?
                    new MeleeAttackAction(enemy, player) :
                    new MagicAttackAction(enemy, player);
        }

        action.execute();
        enemy.resetModifiers();
    }
    private int getValidatedInput(int min, int max) {
        int input;
        while (true) {
            System.out.print("Enter number: ");
            if (scanner.hasNextInt()) {
                input = scanner.nextInt();
                if (input >= min && input <= max) {
                    return input;
                }
            }
            scanner.nextLine(); // Clear invalid input
            System.out.println("Invalid choice. Try again.");
        }
    }

    private BattleStrategy createStrategy(int choice) {
        switch (choice) {
            case 1: return new OffensiveStrategy();
            case 2: return new DefensiveStrategy();
            case 3: return new HealerStrategy();
            default: throw new IllegalArgumentException("Invalid strategy choice");
        }
    }

    private String strategyName(int choice) {
        switch (choice) {
            case 1: return "Offensive";
            case 2: return "Defensive";
            case 3: return "Healer";
            default: return "Unknown";
        }
    }

    private Action createAction(int choice, Character attacker, Character defender) {
        switch (choice) {
            case 1: return new MeleeAttackAction(attacker, defender);
            case 2: return new MagicAttackAction(attacker, defender);
            case 3: return new HealAction(attacker);
            default: return new MeleeAttackAction(attacker, defender); // fallback
        }
    }
}
