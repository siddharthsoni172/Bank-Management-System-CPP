# Bank-Management-System-CPP
# Bank Management Application

A secure and lightweight command-line console application designed in C++ to simulate core transactional banking systems. This project applies foundational Object-Oriented Programming (OOP) paradigms alongside permanent file handling streams to execute data management cleanly without reliance on complex SQL servers.

## 🚀 Core Features
* **Account Generation:** Open new Savings or Current accounts with unique identification keys and structural limits.
* **Secure Persistent Storage:** Customer records are stored locally as structured binary data (`accounts.dat`), protecting customer entries across application lifecycles.
* **Transaction Module:** Fully functional operations handling dynamic account deposits and context-validated fund withdrawals.
* **Balance Inquiries:** Instantly process real-time ledger evaluations on targeted records.

## 🛠️ Concepts & Engineering Focus
* **Encapsulation:** Program properties are cleanly wrapped securely within customized objects utilizing clear accessibility filters.
* **Binary File Serialization:** Utilizes binary block streams (`read` and `write`) combined with memory conversions (`reinterpret_cast`) to preserve computational stability.
* **Stream Formatting:** Structured layout configurations generated using programmatic stream manipulation tools (`iomanip`).

## 📂 Architecture Map
* `main.cpp` - Holds primary execution trees, logical algorithms, and contextual verification conditions.
* `accounts.dat` - Automatically constructed runtime execution file containing safe record data.
