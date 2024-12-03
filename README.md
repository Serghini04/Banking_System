# 🏦 Banking System Management Application 💰

## 🌟 Overview

This is a comprehensive Banking System Management Application developed in C++ 💻, providing a robust and secure platform for banking operations. The application offers a wide range of features for managing bank clients, transactions, and user accounts with advanced security and permission controls.

## ✨ Features

### 1. 🔐 User Authentication
- Secure login system with encrypted passwords
- User permission management
- Multiple user roles with different access levels

### 2. 👥 Client Management
- Add new clients
- View client list
- Update client information
- Delete client accounts
- Find specific client details

### 3. 💸 Transactions
- Deposit funds
- Withdraw funds
- Transfer money between accounts
- View total balances
- Transaction logs

### 4. 👤 User Management
- List users
- Add new users
- Delete users
- Update user information
- Manage user permissions

### 5. 📋 Login Register
- Track login attempts
- Record user login history with timestamps

## 🗂 System Outputs

### Login Screen 🖥️
```
______________________________________
              Login Screen
______________________________________
User :
Date : 3/12/2024

Enter Username?
```

### Main Menu 📋
```
______________________________________
              Main Screen
______________________________________
User : Serghini
Date : 3/12/2024

===========================================
             Main Menu
===========================================
[1] Show Client List
[2] Add New Client
[3] Delete Client
[4] Update Client Info
[5] Find Client
[6] Transactions
[7] Manage Users
[8] Login Register
[9] Logout
===========================================
```

### Transactions Menu 💳
```
===========================================
          Transactions Menu
===========================================
[1] Deposit
[2] Withdraw
[3] Total Balances
[4] Transfer
[5] Transfer Log
[6] Main Menu
===========================================
```

### Usage

1. **Compile and run the program:**
    ```bash
    c++ -std=c++11 main.cpp -o my_program
    ./my_program
    ```

2. **Log in using credentials from `database/realpassword.txt`.**

3. **Navigate through the menu using numeric inputs.**

## 🔮 The Permissions Prophecy

Our permission system isn't just a feature - it's a sophisticated ecosystem:
- 🌟 `eALL`: The Archmage (Full System Control)
- 📋 `pListClients`: The Scroll Keeper
- ➕ `pAddNewClient`: The Welcoming Wizard
- ❌ `pDeleteClient`: The Realm Cleanser
- 🔄 `pUpdateClients`: The Transformation Specialist
- 🔍 `pFindClient`: The Seeker
- 💳 `pTransactions`: The Economic Alchemist
- 👥 `pManageUsers`: The Realm Administrator
- 📖 `pLoginRegister`: The Chronicle Keeper

## 🧰 Technological Enchantments
- 🐉 C++ Dragon (version 11 and beyond)
- 🏗️ Object-Oriented Architectural Spells
- 🔒 Encryption Charms
- 🛡️ Defensive Programming Shields



## Security Features
- Password encryption
- User permission levels
- Secure file-based data storage
- Input validation
