# Bank Management System (C++)

A console-based **Bank Management System** written in C++. This project simulates the functionality of a bank and ATM, allowing users to create accounts, deposit, withdraw, transfer funds, and pay bills. The project also demonstrates object-oriented programming concepts including inheritance, encapsulation, and file handling.

---

## Features

### Bank Account Management
- Create new user accounts with unique account numbers.
- Store personal details: name, father's name, address, phone number.
- Deposit and withdraw funds from accounts.
- Transfer funds between accounts.
- Pay utility bills (Electricity, Gas, Internet).
- Display all accounts and account details.
- Delete user accounts.

### ATM Functionality
- User login with account number, PIN, and password.
- Check account balance.
- Withdraw money securely.

### Security & Authentication
- PIN and password verification.
- Maximum login attempts to prevent unauthorized access.
- Tracks paid bills to prevent double payment.

### Data Persistence
- Account details are saved to a local file (`accounts.txt`) for persistence across program runs.

---

## Project Structure

├── main.cpp # Main program with all classes and ATM/Bank logic
├── accounts.txt # Generated file for storing account details (not included in repo)
├── BankManagement.pdf # Documentation / project report
└── README.md # Project overview and instructions

yaml
Copy code

---

## How to Run

1. Clone the repository:

```bash
git clone https://github.com/Mian-M-Jahanzaib/MyCppProject.git
Navigate to the project folder:

bash
Copy code
cd MyCppProject
Compile the program (example with g++):

bash
Copy code
g++ -o BankManagement main.cpp
Run the program:

bash
Copy code
./BankManagement   # On Linux/Mac
BankManagement.exe # On Windows
Dependencies
C++11 or later

Standard C++ libraries: <iostream>, <fstream>, <vector>, <unordered_map>, <memory>, <algorithm>, <random>, <string>

Author
Mian M. Jahanzaib

GitHub: Mian-M-Jahanzaib

Notes
This is a console-based project; no GUI is included.

Ensure that accounts.txt has write permission for saving account details.

Only .cpp and project PDF are included in the repository. Compiled files are excluded via .gitignore.

