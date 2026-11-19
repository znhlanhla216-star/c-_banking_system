#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// These functions are used to get valid input from the user.
int getNumber(string message) {
    int number;

    while (true) {
        cout << message;
        cin >> number;

        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }

        cout << "Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double getAmount(string message) {
    double amount;

    while (true) {
        cout << message;
        cin >> amount;

        if (!cin.fail() && amount > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return amount;
        }

        cout << "Please enter an amount greater than 0.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Find a user by their account number. It returns the user's position in the arrays.
int findUser(string accountNumbers[], int userCount, string accountNumber) {
    for (int i = 0; i < userCount; i++) {
        if (accountNumbers[i] == accountNumber) {
            return i;
        }
    }

    return -1; // -1 means that the account was not found.
}

// Check the account number and PIN before allowing the user into the system.
int login(string names[], string accountNumbers[], string pins[], int userCount) {
    string enteredAccount;
    string enteredPin;

    cout << "\n========== GCC BANK LOGIN ==========\n";
    cout << "Enter your account number: ";
    cin >> enteredAccount;
    cout << "Enter your PIN: ";
    cin >> enteredPin;

    int userIndex = findUser(accountNumbers, userCount, enteredAccount);

    if (userIndex != -1 && pins[userIndex] == enteredPin) {
        cout << "\nWelcome, " << names[userIndex] << "!\n";
        return userIndex;
    }

    cout << "\nThe account number or PIN is incorrect.\n";
    return -1;
}

// Display the banking options and return the option selected by the user.
int displayMenu() {
    cout << "\n========== GCC BANK ==========\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Send Cash\n";
    cout << "4. Check Balance\n";
    cout << "5. Exit\n";

    return getNumber("Enter your choice: ");
}

// Add money to the selected user's account.
bool deposit(double &balance, string userName) {
    double amount = getAmount("Enter the amount you want to deposit: R");

    balance = balance + amount;

    cout << "R" << fixed << setprecision(2) << amount
         << " has been deposited into " << userName << "'s account.\n";
    cout << "Your new balance is: R" << balance << "\n";
    return true;
}

// Remove money only when the user has enough money in the account.
bool withdraw(double &balance) {
    double amount = getAmount("Enter the amount you want to withdraw: R");

    if (amount > balance) {
        cout << "Sorry, you do not have enough money for this withdrawal.\n";
        cout << "Your current balance is: R" << fixed << setprecision(2)
             << balance << "\n";
        return false;
    }

    balance = balance - amount;

    cout << "Withdrawal successful. You withdrew R"
         << fixed << setprecision(2) << amount << ".\n";
    cout << "Your new balance is: R" << balance << "\n";
    return true;
}

// Transfer money from the logged-in user to another registered account.
bool sendCash(double balances[], string accountNumbers[], int userCount,
              int senderIndex) {
    string recipientAccount;

    cout << "Enter the recipient's account number: ";
    cin >> recipientAccount;

    int recipientIndex = findUser(accountNumbers, userCount, recipientAccount);

    if (recipientIndex == -1) {
        cout << "That account number does not exist. No money was sent.\n";
        return false;
    }

    if (recipientIndex == senderIndex) {
        cout << "You cannot send cash to your own account.\n";
        return false;
    }

    double amount = getAmount("Enter the amount you want to send: R");

    if (amount > balances[senderIndex]) {
        cout << "You do not have enough money to make this transfer.\n";
        return false;
    }

    balances[senderIndex] = balances[senderIndex] - amount;
    balances[recipientIndex] = balances[recipientIndex] + amount;

    cout << "Cash sent successfully to account " << recipientAccount << ".\n";
    cout << "Your new balance is: R" << fixed << setprecision(2)
         << balances[senderIndex] << "\n";
    return true;
}

// Show the current balance of the logged-in user.
void checkBalance(double balance, string userName) {
    cout << "\n" << userName << ", your current balance is R"
         << fixed << setprecision(2) << balance << ".\n";
}

int main() {
    // The three users are stored in arrays. The same position belongs to the same user.
    const int userCount = 3;
    string names[userCount] = {"Thabo Mokoena", "Lerato Dlamini", "Sipho Nkosi"};
    string accountNumbers[userCount] = {"1001", "1002", "1003"};
    string pins[userCount] = {"1234", "2222", "3333"};
    double balances[userCount] = {1500.00, 2500.00, 1000.00};

    cout << "Welcome to Gauteng City College Bank!\n";
    cout << "For this demonstration, use one of the sample accounts below:\n";
    cout << "Account 1001 | PIN 1234\n";
    cout << "Account 1002 | PIN 2222\n";
    cout << "Account 1003 | PIN 3333\n";

    int currentUser = login(names, accountNumbers, pins, userCount);

    if (currentUser == -1) {
        cout << "Login failed. Please restart the program and try again.\n";
        return 0;
    }

    int choice;

    // The loop keeps showing the menu until the user chooses option 5.
    do {
        choice = displayMenu();

        switch (choice) {
            case 1:
                deposit(balances[currentUser], names[currentUser]);
                break;

            case 2:
                withdraw(balances[currentUser]);
                break;

            case 3:
                sendCash(balances, accountNumbers, userCount, currentUser);
                break;

            case 4:
                checkBalance(balances[currentUser], names[currentUser]);
                break;

            case 5:
                cout << "Thank you for using GCC Bank. Goodbye!\n";
                break;

            default:
                cout << "Invalid menu choice. Please choose a number from 1 to 5.\n";
        }

    } while (choice != 5);

    return 0;
}
