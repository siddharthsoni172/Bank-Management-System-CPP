#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Class to handle banking data and operations
class BankAccount {
private:
    int accountNumber;
    char accountHolderName[50];
    char accountType; // 'S' for Saving, 'C' for Current
    double balance;

public:
    // Function to take input from the user
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer

        cout << "Enter Account Holder Name: ";
        cin.getline(accountHolderName, 50);

        cout << "Enter Account Type (S for Saving / C for Current): ";
        cin >> accountType;
        accountType = toupper(accountType);

        cout << "Enter Initial Deposit Amount: ";
        cin >> balance;
        
        cout << "\nAccount Created Successfully!";
    }

    // Function to display account details
    void showAccountDetails() const {
        cout << "\n------------------------------------";
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nHolder Name    : " << accountHolderName;
        cout << "\nAccount Type   : " << (accountType == 'S' ? "Savings" : "Current");
        cout << "\nCurrent Balance: ₹" << fixed << setprecision(2) << balance;
        cout << "\n------------------------------------";
    }

    // Function to deposit money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "\nAmount ₹" << amount << " deposited successfully.";
        } else {
            cout << "\nInvalid deposit amount.";
        }
    }

    // Function to withdraw money
    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "\nInvalid withdrawal amount.";
            return false;
        }
        if (amount > balance) {
            cout << "\nInsufficient balance! Transaction failed.";
            return false;
        }
        balance -= amount;
        cout << "\nAmount ₹" << amount << " withdrawn successfully.";
        return true;
    }

    // Getter functions
    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
};

// File helper function declarations
void writeNewAccount();
void displayAccount(int accNum);
void performTransaction(int accNum, int transactionType); // 1 = Deposit, 2 = Withdraw
void displayAllAccounts();

int main() {
    int choice;
    int accNum;

    do {
        cout << "\n======================================";
        cout << "\n       BANK MANAGEMENT SYSTEM         ";
        cout << "\n======================================";
        cout << "\n1. Open New Account";
        cout << "\n2. Balance Inquiry";
        cout << "\n3. Deposit Money";
        cout << "\n4. Withdraw Money";
        cout << "\n5. Display All Registered Accounts";
        cout << "\n6. Exit";
        cout << "\n======================================";
        cout << "\nEnter your choice (1-6): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                writeNewAccount();
                break;
            case 2:
                cout << "\nEnter Account Number: ";
                cin >> accNum;
                displayAccount(accNum);
                break;
            case 3:
                cout << "\nEnter Account Number: ";
                cin >> accNum;
                performTransaction(accNum, 1);
                break;
            case 4:
                cout << "\nEnter Account Number: ";
                cin >> accNum;
                performTransaction(accNum, 2);
                break;
            case 5:
                displayAllAccounts();
                break;
            case 6:
                cout << "\nThank you for using our banking system. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice! Please select between 1-6.\n";
        }
    } while (choice != 6);

    return 0;
}

void writeNewAccount() {
    BankAccount ac;
    ofstream outFile("accounts.dat", ios::binary | ios::app);
    
    if (!outFile) {
        cout << "\nFile could not be opened. Action aborted.";
        return;
    }
    
    ac.createAccount();
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(BankAccount));
    outFile.close();
}

void displayAccount(int accNum) {
    BankAccount ac;
    ifstream inFile("accounts.dat", ios::binary);
    bool found = false;

    if (!inFile) {
        cout << "\nDatabase empty or unavailable.";
        return;
    }

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(BankAccount))) {
        if (ac.getAccountNumber() == accNum) {
            ac.showAccountDetails();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) {
        cout << "\nAccount Number " << accNum << " does not exist.";
    }
}

void performTransaction(int accNum, int transactionType) {
    BankAccount ac;
    fstream file("accounts.dat", ios::binary | ios::in | ios::out);
    bool found = false;
    double amount;

    if (!file) {
        cout << "\nDatabase empty or unavailable.";
        return;
    }

    while (file.read(reinterpret_cast<char*>(&ac), sizeof(BankAccount))) {
        if (ac.getAccountNumber() == accNum) {
            found = true;
            ac.showAccountDetails();

            if (transactionType == 1) { // Deposit
                cout << "\nEnter the amount to deposit: ₹";
                cin >> amount;
                ac.deposit(amount);
            } 
            else if (transactionType == 2) { // Withdraw
                cout << "\nEnter the amount to withdraw: ₹";
                cin >> amount;
                ac.withdraw(amount);
            }

            // Move pointer back to overwrite old block with updated balance data
            int pos = -1 * static_cast<int>(sizeof(BankAccount));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&ac), sizeof(BankAccount));
            break;
        }
    }
    file.close();
    if (!found) {
        cout << "\nAccount Number " << accNum << " does not exist.";
    }
}

void displayAllAccounts() {
    BankAccount ac;
    ifstream inFile("accounts.dat", ios::binary);

    if (!inFile) {
        cout << "\nNo accounts registered yet.";
        return;
    }

    cout << "\n-------------------------------------------------------------";
    cout << "\n" << left << setw(15) << "Acc No." << setw(25) << "Name" << setw(12) << "Type" << "Balance";
    cout << "\n-------------------------------------------------------------";

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(BankAccount))) {
        // Simple trick to read values since details are private inside objects
        // We're displaying formatted linear columns
        int num = ac.getAccountNumber();
        double bal = ac.getBalance();
        
        cout << "\n" << left << setw(15) << num 
             << setw(25) << "Customer Record" // Stand-in text for safety or read parameters
             << setw(12) << "Active" 
             << "₹" << fixed << setprecision(2) << bal;
    }
    cout << "\n-------------------------------------------------------------\n";
    inFile.close();
}
