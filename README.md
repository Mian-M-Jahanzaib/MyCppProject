Bank Management System 🏦
A robust, console-based Bank and ATM Management System built in C++. This project demonstrates core Object-Oriented Programming (OOP) concepts, secure credential validation, and file-based data persistence. It serves as a comprehensive simulation of real-world banking and ATM operations.

🌟 Key Features
1. User Management
Account Creation: Register new users with strict input validation.

11-digit phone number validation.

4-digit PIN code setup.

8-character alphanumeric password enforcement.

Auto-Generated Accounts: Automatically generates unique 5-character alphanumeric account numbers.

Account Deletion: Admins can safely remove user records from the system.

2. ATM Management
Secure Login: 3-attempt lockout system for incorrect credentials.

Cash Withdrawal: Secure withdrawals requiring PIN authentication.

Account Inquiry: View detailed account information and current balances safely.

3. Bank Management
Deposits & Withdrawals: Manage funds directly through the banking interface.

Fund Transfers: Seamlessly transfer money between different user accounts.

Utility Bill Payments: Pay Electricity, Gas, or Internet bills. Tracks paid bills (using 10-digit bill numbers) to prevent duplicate payments.

Global Database Access: View all registered accounts in the system.

4. Data Persistence
Automatic Save/Load: Account details (Account Number, Balance, PIN, Password) are automatically saved to accounts.txt upon exit and reloaded upon startup, ensuring no data is lost between sessions.

💻 Technical Stack & Concepts Used
Language: C++ (Requires C++14 or higher)

Object-Oriented Programming (OOP): Heavy use of Classes, Inheritance (e.g., Account inherits from Person), Polymorphism, and Encapsulation.

Memory Management: Utilizes Smart Pointers (std::unique_ptr) to prevent memory leaks.

Standard Template Library (STL): * std::unordered_map for O(1) average time complexity lookups (mapping account numbers to account objects, and tracking paid bills).

std::string and string manipulation.

File I/O: std::ifstream and std::ofstream for reliable data storage.

Randomization: <random> library (std::mt19937) for generating unique account numbers.

🚀 Getting Started
Prerequisites
Make sure you have a C++ compiler installed (such as GCC, Clang, or MSVC) that supports at least C++14.

Installation & Execution
Clone the repository:

Bash
git clone https://github.com/Mian-M-Jahanzaib/MyCppProject.git
cd MyCppProject
Compile the code:

Bash
g++ main.cpp -o bank_system
Run the application:

Bash
# On Windows
bank_system.exe

# On Linux/macOS
./bank_system
📄 Documentation & Visuals
This repository includes a comprehensive PDF document containing detailed project documentation, flowcharts, and screenshots of the console interface in action.

Please refer to the attached PDF file in the repository to view visual demonstrations of the menus, error handling, and successful transactions.

🛠️ Usage Guide
Upon running the program, you will be greeted with the Main Menu:

New User: Start here to create your first account. Follow the prompts to enter your personal details, phone number, PIN, password, and initial deposit. Keep note of the generated Account Number!

ATM Management: Use this to simulate an ATM machine. You will need your Account Number, PIN, and Password depending on the action.

Bank Management: Use this to simulate a bank teller. Perform deposits, withdrawals, fund transfers, or pay your utility bills.

Close: Safely exits the program and saves all current data to accounts.txt.

🤝 Contributing
Contributions, issues, and feature requests are welcome! Feel free to check the issues page if you want to contribute.

Author : Mian M Jahanzaib

📝 License
This project is open-source and available under the MIT License.
