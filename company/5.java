/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
5) Write a class “BankAccount” with the following instance variables:
AccountNumber (an integer), balance a floating-point number),
and “ownerName” (a String). Write proper constructor for this class.
Also write methods balance, add (to deposit an amount), and subtract (to withdraw an amount) and implement them.
Now create another class “AccountManager” that contains an array of BankAccount.
Write methods create (to create an account), delete(to terminate an account),
deposit (to deposit an amount to an account) and withdraw (to withdraw an amount from an account).
Also write a class “Bank”, add main() function that creates an AccountManager and add 5 accounts.
Now print the details of all accounts in this Bank
 */

class BankAccount {
    private int accountNumber;
    private double balance;
    private String ownerName;

    public BankAccount(String ownerName, int accountNumber) // new account => balance=0.0
    {
        this.ownerName = ownerName;
        this.accountNumber = accountNumber;
        this.balance = 1000.0; // default base balance
    }

    public void setOwner(String ownerName) {
        this.ownerName = ownerName;
    }

    public String getOwner() {
        return this.ownerName;
    }

    public void getAccNo(int accountNumber) {
        this.accountNumber = accountNumber;
    }

    public int getAccNo() {
        return this.accountNumber;
    }

    public double getBalance() {
        return this.balance;
    }

    public void add(double amt) {
        this.balance += amt;
    }

    public void subtract(double amt) {
        if (amt > this.balance)
            System.out.println("Insufficient balance !");
        else
            this.balance -= amt;
    }
}

class AccountManager {
    private BankAccount bank_acc[];
    private int max_accs, idx;

    public AccountManager(int nos_acc) {
        this.bank_acc = new BankAccount[nos_acc];
        max_accs = nos_acc;
        idx = -1;
    }

    public void addAccount(BankAccount acc) {
        if (idx == -1) {
            // library is empty
            bank_acc[++idx] = acc;
            System.out.println("Account created successfully: " + acc.getOwner());
        } else {
            int flag = 0;
            for (int i = 0; i <= idx; i++) {
                if (bank_acc[i] == null) {
                    bank_acc[i] = acc;
                    flag = 1;
                    System.out.println("Account created successfully: " + acc.getOwner());
                    break;
                }
            }
            if (flag == 0) {
                // no intermediate space left
                if (idx < max_accs - 1) {
                    bank_acc[++idx] = acc;
                    System.out.println("Account created successfully: " + acc.getOwner());
                } else {
                    // library is full
                    System.out.println("No more accounts possible !");
                }
            }
        }
    }

    public void deleteAccount(String ownerName, int accountNumber) {
        if (idx == -1) {
            System.out.println("Bank has no accounts !");
        } else {
            int flag = 0;
            for (int i = 0; i < max_accs; i++) {
                if (bank_acc[i] != null && bank_acc[i].getAccNo() == accountNumber
                        && bank_acc[i].getOwner().equalsIgnoreCase(ownerName)) {
                    bank_acc[i] = null;
                    flag = 1;
                    System.out.println("Account deleted successfully: " + ownerName + " : " + accountNumber);
                    break;
                }
            }
            if (flag == 0) {
                System.out.println("Account not found !");
            }
        }
    }

    public BankAccount getAccount(int idx) {
        return bank_acc[idx];
    }
}

class Bank {
    public static void main(String[] args) {
        BankAccount ba1 = new BankAccount("Monkey D. Luffy", 1500000);
        BankAccount ba2 = new BankAccount("Roronoa Zoro", 320000 );
        BankAccount ba3 = new BankAccount("Vinsmoke Sanji", 3300000);
        BankAccount ba4 = new BankAccount("Nico Robin", 130000);
        BankAccount ba5 = new BankAccount("God Ussop", 200000);
        BankAccount ba6 = new BankAccount("Chopper", 1000);

        // transactions
        ba1.add(450000);
        ba2.add(17000);
        ba3.subtract(400);
        ba2.subtract(5000);
        ba5.add(1500);
        ba6.add(1400);
        ba5.subtract(200);

        AccountManager manager = new AccountManager(5);

        manager.addAccount(ba1);
        manager.addAccount(ba2);
        manager.addAccount(ba3);
        manager.addAccount(ba4);
        manager.addAccount(ba5);

        manager.deleteAccount("Chopper", 1000);
        manager.deleteAccount("Nami", 63000); // account does not exist

        manager.addAccount(ba6);

        // print details of all accounts
        System.out.println("\n\n");
        for (int i = 0; i < 5; i++) {
            BankAccount ba = manager.getAccount(i);
            if (ba != null) {
                // randomly add or subtract a random amount from each account
                if ((int) Math.ceil(Math.random() * 10) % 2 == 0)
                    ba.add(Math.random() * 1000.0);
                else
                    ba.subtract(Math.random() * 1000.0);
                // print details
                System.out.println("Name of a/c holder: " + ba.getOwner());
                System.out.println("a/c number: " + ba.getAccNo());
                System.out.println("Current Balance: " + ba.getBalance());
                System.out.println();
            }
        }
    }
}
