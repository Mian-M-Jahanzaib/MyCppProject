#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <random>
#include <algorithm>
using namespace std;
class Account;
class Bank;
class ATM;
class Person {
protected:
    string name;
    string fatherName;
    string address;
    string phoneNumber;
public:
    Person(const string& name, const string& fatherName, const string& address, const string& phoneNumber)
        : name(name), fatherName(fatherName), address(address), phoneNumber(phoneNumber) {}
    virtual ~Person() = default;
    virtual void display() const {
        cout << "\nName : " << name << endl;
        cout << "Father's Name : " << fatherName << endl;
        cout << "Address : " << address << endl;
        cout << "Phone Number : " << phoneNumber << endl;
    }
    string getPhoneNumber() const {
        return phoneNumber;
    }
};
class Account : public Person {
private:
    string accountNumber;
    string pinCode;
    string password;
    double balance;
    unordered_map<string, bool> paidBills;

public:
    Account(const string& name, const string& fatherName, const string& address, const string& phoneNumber, const string& accountNumber, const string& pinCode, const string& password, double initialBalance)
        : Person(name, fatherName, address, phoneNumber), accountNumber(accountNumber), pinCode(pinCode), password(password), balance(initialBalance) {}

    ~Account() {

    }

    bool authenticate(const string& enteredPinCode, const string& enteredPassword) const {
        return pinCode == enteredPinCode && password == enteredPassword;
    }

    bool authenticatePin(const string& enteredPinCode) const {
        return pinCode == enteredPinCode;
    }

    bool authenticatePassword(const string& enteredPassword) const {
        return password == enteredPassword;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    bool transfer(Account& toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            return true;
        }
        return false;
    }

    void payBill(const string& billNumber, double amount) {
        if (paidBills.find(billNumber) == paidBills.end()) {
            balance -= amount;
            paidBills[billNumber] = true;
        }
    }

    bool isBillPaid(const string& billNumber) const {
        return paidBills.find(billNumber) != paidBills.end();
    }

    double getBalance() const {
        return balance;
    }

    void display() const override {
        Person::display();
        cout << "\nAccount Number : " << accountNumber << endl;
        cout << "Balance : " << balance << endl;
    }

    string getPassword() const {
        return password;
    }

    string getPinCode() const {
        return pinCode;
    }

    string getAccountNumber() const {
        return accountNumber;
    }
};
class Bank {
private:
    unordered_map<string, unique_ptr<Account>> accounts;
    unordered_map<string, string> phoneToAccount;

    void saveAccountDetails() {
        ofstream file("accounts.txt");
        if (file.is_open()) {
            for (const auto& pair : accounts) {
                const Account& account = *pair.second;
                file << account.getAccountNumber() << " " << account.getBalance() << " " << account.getPinCode() << " " << account.getPassword() << endl;
            }
            file.close();
        }
    }

    void loadAccountDetails() {
        ifstream file("accounts.txt");
        if (file.is_open()) {
            string accountNumber;
            double balance;
            string pinCode;
            string password;
            while (file >> accountNumber >> balance >> pinCode >> password) {
                accounts[accountNumber] = make_unique<Account>("Loaded", "Loaded", "Loaded", "Loaded", accountNumber, pinCode, password, balance);
            }
            file.close();
        }
    }

    string generateUniqueAccountNumber() {
        const string characters = "abcdefghijklmnopqrstuvwxyz0123456789";
        const int length = 5;
        string accountNumber;
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> distribution(0, characters.size() - 1);

        do {
            accountNumber.clear();
            for (int i = 0; i < length; ++i) {
                accountNumber += characters[distribution(generator)];
            }
        } while (accounts.find(accountNumber) != accounts.end());

        return accountNumber;
    }

public:
    Bank() {
        loadAccountDetails();
    }

    ~Bank() {
        saveAccountDetails();
    }

    string addAccount(const string& name, const string& fatherName, const string& address, const string& phoneNumber, const string& pinCode, const string& password, double initialBalance) {
        string accountNumber = generateUniqueAccountNumber();
        auto account = make_unique<Account>(name, fatherName, address, phoneNumber, accountNumber, pinCode, password, initialBalance);
        accounts[accountNumber] = move(account);
        phoneToAccount[phoneNumber] = accountNumber;
        return accountNumber;
    }

    Account* findAccount(const string& accountNumber) {
        if (accounts.find(accountNumber) != accounts.end()) {
            return accounts[accountNumber].get();
        }
        return nullptr;
    }

    string findAccountByPhone(const string& phoneNumber) {
        if (phoneToAccount.find(phoneNumber) != phoneToAccount.end()) {
            return phoneToAccount[phoneNumber];
        }
        return "";
    }

    void displayAllAccounts() const {
        if (accounts.empty()) {
            cout << "\n-------> No records available <-------" << endl;
        }
        else {
            for (const auto& pair : accounts) {
                pair.second->display();
            }
        }
    }

    void deleteAccount(const string& accountNumber) {
        if (accounts.find(accountNumber) != accounts.end()) {
            phoneToAccount.erase(accounts[accountNumber]->getPhoneNumber());
            accounts.erase(accountNumber);
        }
    }
};
class ATM {
private:
    Bank& bank;

public:
    ATM(Bank& bank) : bank(bank) {}

    void userLogin() {
        string accountNumber;
        string pinCode, password;

        for (int attempt = 0; attempt < 3; ++attempt) {
            cout << "\nEnter Account Number : ";
            cin >> accountNumber;
            cout << "Enter Pin Code : ";
            cin >> pinCode;
            cout << "Enter Password : ";
            cin >> password;

            Account* account = bank.findAccount(accountNumber);
            if (account && account->authenticate(pinCode, password)) {
                cout << "\n-------> Login successful <-------\nYour balance is : " << account->getBalance() << endl;
                return;
            }
            cout << "\n !!! Invalid credentials !!! Try again" << endl;
        }

        cout << "\n !!! Too many failed attempts !!! Returning to main menu " << endl;
    }

    void withdrawAmount() {
        string accountNumber;
        string pinCode;
        double amount;

        cout << "\nEnter Account Number : ";
        cin >> accountNumber;
        cout << "Enter Pin Code : ";
        cin >> pinCode;

        Account* account = bank.findAccount(accountNumber);
        if (account && account->authenticatePin(pinCode)) {
            cout << "Enter amount to withdraw : ";
            cin >> amount;

            if (account->withdraw(amount)) {
                cout << "\n-------> Withdrawal successful <-------\nYour new balance is : " << account->getBalance() << endl;
            }
            else {
                cout << "\n!!! Insufficient funds !!!" << endl;
            }
        }
        else {
            cout << "\n!!! Invalid pin code or account number !!!" << endl;
        }
    }

    void accountDetails() {
        string accountNumber;
        string password;

        cout << "\nEnter Account Number : ";
        cin >> accountNumber;
        cout << "Enter Password : ";
        cin >> password;

        Account* account = bank.findAccount(accountNumber);
        if (account && account->authenticatePassword(password)) {
            account->display();
        }
        else {
            cout << "\n !!! Invalid credentials !!!" << endl;
        }
    }

    void goBack() {
        cout << "Returning to main menu." << endl;
    }
};

int main() {
    Bank bank;
    ATM atm(bank);
    int choice;

    while (true) {
        cout << "\n-------------------------- Bank Management System --------------------------" << endl;
        cout << "\nMain Menu :-\n";
        cout << "\n(1) New User\n";
        cout << "(2) ATM Management\n";
        cout << "(3) Bank Management\n";
        cout << "(4) Close\n";
        cout << "\nEnter your choice : ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, fatherName, address, phoneNumber, pinCode, password;
            double initialBalance;

            cin.ignore();
            cout << "\nEnter Name : ";
            getline(cin, name);
            cout << "Enter Father's Name : ";
            getline(cin, fatherName);
            cout << "Enter Address : ";
            getline(cin, address);


            for (int attempt = 0; attempt < 3; ++attempt) {
                cout << "Enter 11-Digit Phone Number : ";
                cin >> phoneNumber;
                if (phoneNumber.length() == 11 && all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit)) {
                    if (bank.findAccountByPhone
                    (phoneNumber).empty()) {
                        break;
                    }
                    else {
                        cout << "\n!!! Phone number already in use !!! Try again" << endl;
                    }
                }
                else {
                    cout << "\n!!!Invalid phone number !!! Try again" << endl;
                }
            }
            if (phoneNumber.length() != 11) {
                cout << "\n!!!Too many failed attempt !!! Returning to main menu." << endl;
                break;
            }

            while (true) {
                cout << "Set 4-Digit Pin Code : ";
                cin >> pinCode;
                if (pinCode.length() == 4 && all_of(pinCode.begin(), pinCode.end(), ::isdigit)) {
                    break;
                }
                else {
                    cout << "\n!!! Invalid pin code !!! Try again" << endl;
                }
            }

            while (true) {
                cout << "Enter 8-Character Password (letters and/or digits) : ";
                cin >> password;
                if (password.length() == 8 && all_of(password.begin(), password.end(), [](char c) { return isalnum(c); })) {
                    break;
                }
                else {
                    cout << "\n!!! Invalid password !!! Try again" << endl;
                }
            }

            cout << "Enter Initial Balance : ";
            cin >> initialBalance;

            string accountNumber = bank.addAccount(name, fatherName, address, phoneNumber, pinCode, password, initialBalance);
            cout << "\n-------> Account created successfull <-------\nYour account number is : " << accountNumber << endl;
            break;
        }
        case 2:
            while (true) {
                cout << "\nATM Management Menu :-\n";
                cout << "\n(1) User Login\n";
                cout << "(2) Withdraw Amount\n";
                cout << "(3) Account Details\n";
                cout << "(4) Go Back\n";
                cout << "\nEnter your choice : ";
                cin >> choice;

                switch (choice) {
                case 1:
                    atm.userLogin();
                    break;
                case 2:
                    atm.withdrawAmount();
                    break;
                case 3:
                    atm.accountDetails();
                    break;
                case 4:
                    atm.goBack();
                    goto MAIN_MENU;
                default:
                    cout << "\n !!! Invalid choice !!! Try again" << endl;
                }
            }
        case 3:
            while (true) {
                cout << "\nBank Management Menu :-\n";
                cout << "\n(1) Deposit\n";
                cout << "(2) Withdraw\n";
                cout << "(3) Transfer\n";
                cout << "(4) Pay Bills\n";
                cout << "(5) Delete User Record\n";
                cout << "(6) Show All Records\n";
                cout << "(7) Go Back\n";
                cout << "\nEnter your choice : ";
                cin >> choice;

                switch (choice) {
                case 1: {
                    string accountNumber;
                    double amount;

                    cout << "\nEnter Account Number : ";
                    cin >> accountNumber;
                    cout << "Enter Amount to Deposit : ";
                    cin >> amount;

                    Account* account = bank.findAccount(accountNumber);
                    if (account) {
                        account->deposit(amount);
                        cout << "\n-------> Deposit successful <-------\nYour new balance is : " << account->getBalance() << endl;
                    }
                    else {
                        cout << "\n !!!Account not found !!!" << endl;
                    }
                    break;
                }
                case 2: {
                    string accountNumber;
                    double amount;

                    cout << "\nEnter Account Number : ";
                    cin >> accountNumber;
                    cout << "Enter Amount to Withdraw : ";
                    cin >> amount;

                    Account* account = bank.findAccount(accountNumber);
                    if (account) {
                        if (account->withdraw(amount)) {
                            cout << "\n-------> Withdrawal successful <-------\nYour new balance is : " << account->getBalance() << endl;
                        }
                        else {
                            cout << "\n!!! Insufficient funds !!!" << endl;
                        }
                    }
                    else {
                        cout << "\n!!! Account not found !!!" << endl;
                    }
                    break;
                }
                case 3: {
                    string fromAccountNumber, toAccountNumber;
                    double amount;

                    cout << "\n Enter Your Account Number : ";
                    cin >> fromAccountNumber;
                    cout << "Enter Receiver's Account Number : ";
                    cin >> toAccountNumber;
                    cout << "Enter Amount to Transfer : ";
                    cin >> amount;

                    Account* fromAccount = bank.findAccount(fromAccountNumber);
                    Account* toAccount = bank.findAccount(toAccountNumber);

                    if (!fromAccount && !toAccount) {
                        cout << "\n!!!Both your account number and the receiver's account number are incorrect !!!" << endl;
                    }
                    else if (!fromAccount) {
                        cout << "\n!!! Your account number is incorrect !!!" << endl;
                    }
                    else if (!toAccount) {
                        cout << "\n!!! Receiver's account number not found !!!" << endl;
                    }
                    else if (fromAccount->transfer(*toAccount, amount)) {
                        cout << "\n-------> Transfer successful <-------" << endl;
                    }
                    else {
                        cout << "\n!!! Insufficient funds !!!" << endl;
                    }
                    break;
                }
                case 4: {
                    string accountNumber, billNumber;
                    int billType;
                    double amount;

                    cout << "\nEnter Account Number : ";
                    cin >> accountNumber;
                    cout << "Enter Bill Type ( 1 for Electricity, 2 for Gas, 3 for Internet) : ";
                    cin >> billType;
                    cout << "Enter 10-Digit Bill Number : ";
                    cin >> billNumber;
                    cout << "Enter Bill Amount : ";
                    cin >> amount;

                    Account* account = bank.findAccount(accountNumber);
                    if (account && billNumber.length() == 10) {
                        if (account->isBillPaid(billNumber)) {
                            cout << "\n!!! Bill already paid !!!" << endl;
                        }
                        else if (account->getBalance() >= amount) {
                            account->payBill(billNumber, amount);
                            cout << "\n-------> Bill paid successfully <-------\nYour new balance is : " << account->getBalance() << endl;
                        }
                        else {
                            cout << "\n!!! Insufficient funds !!!" << endl;
                        }
                    }
                    else {
                        cout << "\n!!! Invalid bill number or account not found !!!" << endl;
                    }
                    break;
                }
                case 5: {
                    string accountNumber;

                    cout << "\nEnter Account Number : ";
                    cin >> accountNumber;

                    bank.deleteAccount(accountNumber);
                    cout << "\n-------> Account deleted successfully <-------" << endl;
                    break;
                }
                case 6:
                    bank.displayAllAccounts();
                    break;
                case 7:
                    goto MAIN_MENU;
                default:
                    cout << "\n!!! Invalid choice !!! Try again" << endl;
                }
            }
        case 4:
            cout << "Exiting the system" << endl;
            return 0;
        default:
            cout << "\n!!! Invalid choice !!! Try again" << endl;
        }

    MAIN_MENU:
        continue;
    }

    return 0;
}