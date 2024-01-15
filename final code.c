#include <stdio.h>

#define MAX_ACCOUNTS 20
#define PIN_LENGTH 4

struct BankAccount {
    int accountNumber;
    int pin;
    float balance;
};

// Declare currentAccountIndex as a global variable
int currentAccountIndex = -1;

struct BankAccount createAccount(int accountNumber, int pin) {
    struct BankAccount newAccount;
    newAccount.accountNumber = accountNumber;
    newAccount.pin = pin;
    newAccount.balance = 0.0;
    return newAccount;
}

int isAccountNumberExists(struct BankAccount *accounts, int accountCount, int accountNumber) {
    int i;
    for (i = 0; i < accountCount; ++i) {
        if (accounts[i].accountNumber == accountNumber) {
            return 1; // Account number already exists
        }
    }
    return 0; // Account number doesn't exist
}

int isValidPin(int pin) {
    // Check if the PIN is a 4-digit number
    return pin >= 1000 && pin <= 9999;
}

int authenticateAccount(struct BankAccount *accounts, int accountCount) {
    int accountNumber, pin;
    printf("Enter your account number: ");
    scanf("%d", &accountNumber);

    // Validate PIN length
    do {
        printf("Enter your PIN (4 digits): ");
        scanf("%d", &pin);

        if (!isValidPin(pin)) {
            printf("Invalid PIN. Please enter a 4-digit PIN.\n");
        } else {
            break;
        }
    } while (1);

    int i;
    for (i = 0; i < accountCount; ++i) {
        if (accounts[i].accountNumber == accountNumber && accounts[i].pin == pin) {
            currentAccountIndex = i;
            return 1; // Authentication successful
        }
    }

    printf("Authentication failed. Invalid account number or PIN.\n");
    return 0; // Authentication failed
}

void deposit(struct BankAccount *account) {
    float amount;
    printf("Enter the amount to deposit: Rs ");
    scanf("%f", &amount);
    account->balance += amount;
    printf("\nDeposited Rs %.2f into account %d\n", amount, account->accountNumber);
}

void withdraw(struct BankAccount *account) {
    float amount;
    printf("Enter the amount to withdraw: Rs ");
    scanf("%f", &amount);
    if (amount <= account->balance) {
        account->balance -= amount;
        printf("\nWithdrawn Rs %.2f from account %d\n", amount, account->accountNumber);
    } else {
        printf("\nInsufficient funds in account %d\n", account->accountNumber);
    }
}

void changePin(struct BankAccount *account) {
    int newPin, confirmPin;

    do {
        // Validate new PIN length
        do {
            printf("Enter your new PIN (4 digits): ");
            scanf("%d", &newPin);

            if (!isValidPin(newPin)) {
                printf("Invalid PIN. Please enter a 4-digit PIN.\n");
            } else {
                break;
            }
        } while (1);

        printf("Re-enter your new PIN for confirmation: ");
        scanf("%d", &confirmPin);

        if (newPin == confirmPin) {
            // Update the PIN
            account->pin = newPin;
            printf("\n\"PIN changed successfully for account %d\"\n", account->accountNumber);
            break;
        } else {
            printf("\n\nPIN entries do not match. Please try again.\n");
        }

    } while (1);
}

void checkBalance(struct BankAccount account) {
    printf("\nAccount %d has a balance of Rs %.2f\n", account.accountNumber, account.balance);
}

void transfer(struct BankAccount *sender, struct BankAccount *receiver, int accountCount, struct BankAccount *accounts) {
    int receiverAccountNumber;
    float amount;

    printf("Enter the recipient account number: ");
    scanf("%d", &receiverAccountNumber);

    int receiverIndex = -1;
    for (int i = 0; i < accountCount; ++i) {
        if (accounts[i].accountNumber == receiverAccountNumber) {
            receiverIndex = i;
            break;
        }
    }

    if (receiverIndex == -1) {
        printf("\nRecipient account not found.\n");
        return;
    }

    if (receiverAccountNumber == accounts[currentAccountIndex].accountNumber) {
        printf("\nYou cannot transfer money to the same account.\n");
        return;
    }

    if (authenticateAccount(accounts, accountCount)) {
        printf("Enter the amount to transfer: Rs ");
        scanf("%f", &amount);

        if (amount <= sender->balance) {
            sender->balance -= amount;
            accounts[receiverIndex].balance += amount;
            printf("\nTransferred Rs %.2f from account %d to account %d\n", amount, sender->accountNumber, accounts[receiverIndex].accountNumber);
        } else {
            printf("\nInsufficient funds in account %d\n", sender->accountNumber);
        }
    } else {
        printf("Authentication failed. Invalid account number or PIN.\n");
    }
}


void printMainMenu() {
    printf("\nMain Menu:\n");
    printf("1. Create Account\n");
    printf("2. Select Account\n");
    printf("3. Quit\n");
}

void printAccountMenu() {
    printf("\nAccount Menu:\n");
    printf("1. Deposit\n");
    printf("2. Withdraw\n");
    printf("3. Change PIN\n");
    printf("4. Check Balance\n");
    printf("5. Transfer Money\n");
    printf("6. Back to Main Menu\n");
}

void createAccountMenu(struct BankAccount *accounts, int *accountCount) {
    if (*accountCount < MAX_ACCOUNTS) {
        int newAccountNumber, newPIN;

        do {
            printf("\nEnter a new account number: ");
            scanf("%d", &newAccountNumber);

            if (isAccountNumberExists(accounts, *accountCount, newAccountNumber)) {
                printf("\nAccount number already exists. Please choose a different account number.\n");
            } else {
                // Validate new PIN length
                do {
                    printf("Enter a PIN (4 digits): ");
                    scanf("%d", &newPIN);

                    if (!isValidPin(newPIN)) {
                        printf("Invalid PIN. Please enter a 4-digit PIN.\n");
                    } else {
                        break;
                    }
                } while (1);

                accounts[*accountCount] = createAccount(newAccountNumber, newPIN);
                (*accountCount)++;
                printf("\n\"Account created successfully.\"\n");
                break; // Exit the loop after creating the account
            }
        } while (1); // Infinite loop until a valid account is created
    } else {
        printf("\nCannot create more accounts. Maximum limit reached.\n");
    }
}

void printPBL() {
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\t\t   ******   *******    ***         \n");
    printf("\t\t\t\t\t\t\t\t\t   **   **  **    **   * *         \n");
    printf("\t\t\t\t\t\t\t\t\t   **   **  **    **   * *         \n");
    printf("\t\t\t\t\t\t\t\t\t   *******  *******    * *         \n");
    printf("\t\t\t\t\t\t\t\t\t   ******   *******    * *         \n");
    printf("\t\t\t\t\t\t\t\t\t   **       **    **   * *         \n");
    printf("\t\t\t\t\t\t\t\t\t   **       **    **   * ******    \n");
    printf("\t\t\t\t\t\t\t\t\t   **       *******    ********    \n");
    printf("\t\t\t\t\t\t\t\t\t   PAKISTAN   BANK     LIMITED\n\n");
    printf("\t\t\t\t\t\t\t\t\t     Where Money Comes First!\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

int main() {
    int choice, accountCount = 0;

    struct BankAccount accounts[MAX_ACCOUNTS];

    printPBL();
    printf("Welcome to PBL, Good Luck for your journey with us!\n");
    do {

        printMainMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccountMenu(accounts, &accountCount);
                break;

            case 2:
                if (accountCount > 0) {
                    if (authenticateAccount(accounts, accountCount)) {
                        printf("\nAuthentication successful. Account %d selected.\n", accounts[currentAccountIndex].accountNumber);
                        int accountChoice;

                        do {
                            printAccountMenu();
                            printf("\nEnter your choice: ");
                            scanf("%d", &accountChoice);

                            switch (accountChoice) {
                                case 1:
                                    deposit(&accounts[currentAccountIndex]);
                                    break;

                                case 2:
                                    withdraw(&accounts[currentAccountIndex]);
                                    break;

                                case 3:
                                    changePin(&accounts[currentAccountIndex]);
                                    break;

                                case 4:
                                    checkBalance(accounts[currentAccountIndex]);
                                    break;

                                case 5:
                                    transfer(&accounts[currentAccountIndex], accounts, accountCount, accounts);
                                    break;

                                case 6:
                                    printf("\nBack to Main Menu.\n");
                                    break;

                                default:
                                    printf("\nInvalid choice. Please enter a valid option.\n");
                            }
                        } while (accountChoice != 6);
                    }
                } else {
                    printf("\nNo accounts available. Please create an account first.\n");
                }
                break;

            case 3:
                printf("\nThank you for using Pakistan Bank Limited.\n");
                break;

            default:
                printf("\"Invalid choice. Please enter a valid option.\"\n");
        }
    } while (choice != 3);

    return 0;
}
