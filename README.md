# 📦 Unit Inventory Management System

[![C++](https://img.shields.io/badge/C++-11%2B-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B11)
[![Build Status](https://img.shields.io/badge/Build-Success-brightgreen.svg)]()

A high-performance, **ANSI-powered** terminal application for professional inventory oversight. This system combines robust C++ logic with a modern, reactive console dashboard, providing real-time stock visualization and automated data persistence.

---

## 🚀 Key Features

### 📊 Dynamic Visual Dashboard
- **Reactive UI**: Real-time inventory table with color-coded stock levels.
- **Visual Analytics**: Instant stock level bars (**[ Green ]** for healthy, **[ Yellow ]** for warning, **[ Red ]** for critical).
- **ANSI Support**: Full virtual terminal processing for a premium look and feel.

### 🧠 Smart Data Management
- **Persistent Storage**: Automated CSV-based data logging (`inventory.csv`).
- **Safety First**: Integrated backup mechanism to prevent data loss.
- **Input Validation**: Robust error handling for all user inputs (IDs, prices, and quantities).

### ⚡ Professional Toolkit
- **Advanced Sorting**: Reorder your entire catalog by **ID**, **Alphabetical Name**, or **Unit Price**.
- **Instant Search**: Locating assets via ID or fuzzy name search.
- **Valuation Intelligence**: Real-time reporting on the total net worth of all managed assets.

---

## 🛠️ Getting Started

### Prerequisites
- A C++11 compatible compiler (`g++`, `clang`, or `MSVC`).
- Windows 10/11 (Optimized for Windows Terminal) or a modern POSIX terminal with ANSI support.

### Installation & Build

1. **Clone the repository** (if applicable):
   ```bash
   git clone https://github.com/OMReda/inventory-management-system.git
   cd inventory-management-system
   ```

2. **Compile the system**:
   ```powershell
   g++ main.cpp Inventory.cpp -o inventory.exe
   ```

3. **Launch the application**:
   - Via double-click: Run `launch_inventory.bat`
   - Via terminal: `.\inventory.exe`

---

## 🏗️ Project Architecture

| Component | Responsibility |
| :--- | :--- |
| **`Product.h`** | Core data structure and CSV serialization logic. |
| **`Inventory.h/cpp`** | Business logic, sorting algorithms, and persistence management. |
| **`Utils.h`** | ANSI terminal drivers, I/O validation, and UI helpers. |
| **`main.cpp`** | System orchestration and user interface loop. |

---

## 🧪 Quality Assurance

We maintain high standards for data integrity and performance:

- **Unit Testing**: Run `unit_test.cpp` to verify core logic.
- **PowerShell Verification**: Use `verify_sorts.ps1` for automated sorting validation.

To run tests:
```powershell
g++ unit_test.cpp -o unit_test.exe
.\unit_test.exe
```
---
*Developed by [OMReda](https://github.com/OMReda)*
