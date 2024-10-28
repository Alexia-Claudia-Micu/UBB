import java.io.*;
import java.util.*;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class Operation {
    int sourceAccountId;
    int destinationAccountId;
    int amount;
    int serialNumber;
}

class Account {
    int id;
    int balance;
    int initialBalance;
    List<Operation> log = new ArrayList<>();
}

public class Main {
    private static final int CREATOR_THREAD_COUNT = 5;
    private static Map<Integer, Account> accounts = new HashMap<>();
    private static List<Operation> operations = new ArrayList<>();
    private static int nextSerialNumber = 0;

    private static Lock[] accountsLocks;
    private static final Lock operationLock = new ReentrantLock();
    private static final Lock serialNumberLock = new ReentrantLock();

    public static Map<Integer, Account> readAllAccounts(String filePath) throws IOException {
        Map<Integer, Account> accounts = new HashMap<>();
        BufferedReader reader = new BufferedReader(new FileReader(filePath));
        String line;

        while ((line = reader.readLine()) != null) {
            String[] parts = line.split(" ");
            Account account = new Account();
            account.id = Integer.parseInt(parts[0]);
            account.balance = Integer.parseInt(parts[1]);
            account.initialBalance = account.balance;
            accounts.put(account.id, account);
        }

        reader.close();
        return accounts;
    }

    public static void printAllOperations() {
        operationLock.lock();
        try {
            for (Operation operation : operations) {
                System.out.println("--> OPERATION serial number: " + operation.serialNumber + "-----");
                System.out.println("source account: " + operation.sourceAccountId);
                System.out.println("destination account: " + operation.destinationAccountId);
                System.out.println("amount: " + operation.amount + "\n");
            }
        } finally {
            operationLock.unlock();
        }
    }

    public static void printAllAccounts() {
        System.out.println("Printing all accounts:");
        for (Map.Entry<Integer, Account> entry : accounts.entrySet()) {
            int accountId = entry.getKey();
            Account account = entry.getValue();

            // Lock the specific account to ensure thread-safe access
            accountsLocks[accountId].lock();
            try {
                System.out.println("Account ID: " + account.id);
                System.out.println("Current Balance: " + account.balance);
                System.out.println("Initial Balance: " + account.initialBalance);
                System.out.println("Transactions Log:");

                for (Operation operation : account.log) {
                    System.out.println("    Operation Serial Number: " + operation.serialNumber);
                    System.out.println("    Source Account ID: " + operation.sourceAccountId);
                    System.out.println("    Destination Account ID: " + operation.destinationAccountId);
                    System.out.println("    Amount: " + operation.amount);
                    System.out.println();
                }
                System.out.println("------------------------");
            } finally {
                // Unlock the account after printing its details
                accountsLocks[accountId].unlock();
            }
        }
    }


    public static int generateRandomNumberInRange(int min, int max) {
        Random random = new Random();
        return random.nextInt((max - min) + 1) + min;
    }

    public static void createTransaction() {
        Operation operation = new Operation();
        operation.amount = generateRandomNumberInRange(1, 100);

        int senderAccount = generateRandomNumberInRange(0, accounts.size() - 1);
        int receiverAccount = generateRandomNumberInRange(0, accounts.size() - 1);

        while (senderAccount == receiverAccount) {
            receiverAccount = generateRandomNumberInRange(0, accounts.size() - 1);
        }

        operation.sourceAccountId = senderAccount;
        operation.destinationAccountId = receiverAccount;

        if (operation.sourceAccountId < operation.destinationAccountId) {
            accountsLocks[operation.sourceAccountId].lock();
            accountsLocks[operation.destinationAccountId].lock();
        } else {
            accountsLocks[operation.destinationAccountId].lock();
            accountsLocks[operation.sourceAccountId].lock();
        }

        try {
            if (accounts.get(operation.sourceAccountId).balance < operation.amount) {
                accountsLocks[operation.sourceAccountId].unlock();
                accountsLocks[operation.destinationAccountId].unlock();
                return;
            }

            serialNumberLock.lock();
            try {
                operation.serialNumber = nextSerialNumber++;
            } finally {
                serialNumberLock.unlock();
            }

            Account sender = accounts.get(operation.sourceAccountId);
            Account receiver = accounts.get(operation.destinationAccountId);

            sender.balance -= operation.amount;
            sender.log.add(operation);

            receiver.balance += operation.amount;
            receiver.log.add(operation);

            operationLock.lock();
            try {
                operations.add(operation);
            } finally {
                operationLock.unlock();
            }
        } finally {
            accountsLocks[operation.sourceAccountId].unlock();
            accountsLocks[operation.destinationAccountId].unlock();
        }
    }

    public static boolean checkIfOperationExistsInLog(List<Operation> log, Operation operation) {
        for (Operation logOperation : log) {
            if (logOperation.serialNumber == operation.serialNumber) {
                return true;
            }
        }
        return false;
    }

    public static void checkConsistency() {
        boolean isConsistent = true;

        for (Account account : accounts.values()) {
            accountsLocks[account.id].lock();
            try {
                int initialBalance = account.initialBalance;

                for (Operation operation : account.log) {
                    if (operation.sourceAccountId == account.id) {
                        initialBalance -= operation.amount;
                        isConsistent = checkIfOperationExistsInLog(accounts.get(operation.destinationAccountId).log, operation);
                    } else {
                        initialBalance += operation.amount;
                        isConsistent = checkIfOperationExistsInLog(accounts.get(operation.sourceAccountId).log, operation);
                    }

                    if (!isConsistent) {
                        break;
                    }
                }

                if (initialBalance != account.balance) {
                    isConsistent = false;
                    break;
                }
            } finally {
                accountsLocks[account.id].unlock();
            }

            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        if (isConsistent) {
            System.out.println("Consistency check passed");
        } else {
            System.out.println("Consistency check failed");
        }
    }

    public static void main(String[] args) throws IOException {
        accounts = readAllAccounts("C:/Users/alexi/OneDrive/Documents/Facultate/Anul_3/Sem_1/PPD/lab1/src/accounts.txt");

        accountsLocks = new ReentrantLock[accounts.size()];
        for (int i = 0; i < accounts.size(); i++) {
            accountsLocks[i] = new ReentrantLock();
        }

        Thread[] creatorThreads = new Thread[CREATOR_THREAD_COUNT];
        for (int i = 0; i < CREATOR_THREAD_COUNT; i++) {
            creatorThreads[i] = new Thread(Main::createTransaction);
            creatorThreads[i].start();
        }

        for (int i = 0; i < CREATOR_THREAD_COUNT; i++) {
            try {
                creatorThreads[i].join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }

            if (i % 6 == 0) {
                checkConsistency();
            }
        }

        Thread checkerThread = new Thread(Main::checkConsistency);
        checkerThread.start();
        try {
            checkerThread.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        printAllAccounts();

        Thread printerThread = new Thread(Main::printAllOperations);
        printerThread.start();
        try {
            printerThread.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
