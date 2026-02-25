#include "Inventory.h"
#include "Utils.h"
#include <iomanip>
#include <iostream>

using namespace Utils;

void displayTable(const std::vector<Product> &list,
                  const std::string &sortMode = "NONE") {
  std::cout << "  " << BOLD << CYAN << "UNIT INVENTORY DASHBOARD" << RESET;
  std::cout << "  [" << BOLD << YELLOW << "SORT: " << sortMode << RESET
            << "]\n";
  std::cout << "  " << std::string(85, '=') << "\n";
  std::cout << "  " << BOLD << WHITE << std::left << std::setw(6) << "ID"
            << std::setw(30) << "Product Name" << std::setw(15) << "Unit Price"
            << std::setw(10) << "Stock"
            << "Visual Stock Level" << RESET << std::endl;
  std::cout << "  " << std::string(85, '-') << "\n";

  for (const auto &p : list) {
    std::string barColor = (p.quantity < 10)   ? BG_RED
                           : (p.quantity < 25) ? BG_YELLOW
                                               : BG_GREEN;

    std::cout << "  " << std::left << std::setw(6) << p.id << std::left
              << std::setw(30) << p.name << "  $" << std::fixed
              << std::setprecision(2) << std::setw(12) << p.price << std::left
              << std::setw(10) << p.quantity;

    int barLength = p.quantity / 5;
    if (barLength < 0)
      barLength = 0;
    if (barLength > 20)
      barLength = 20;

    std::cout << barColor << std::string(barLength, ' ') << RESET << BG_GRAY
              << std::string(20 - barLength, ' ') << RESET << std::endl;
  }
  std::cout << "  " << std::string(85, '=') << "\n";
}

void printMenu(const Inventory &inv, const std::string &sortMode) {
  clearScreen();
  displayTable(inv.getProducts(), sortMode);

  std::cout << "\n  " << BOLD << MAGENTA << "ACTIONS:" << RESET << "\n";
  std::cout << "  " << BLUE << "1." << RESET << " Add Item          " << BLUE
            << "6." << RESET << " Sort: ID\n";
  std::cout << "  " << BLUE << "2." << RESET << " Update Stock      " << BLUE
            << "7." << RESET << " Sort: Name\n";
  std::cout << "  " << BLUE << "3." << RESET << " Remove Item       " << BLUE
            << "8." << RESET << " Sort: Price\n";
  std::cout << "  " << BLUE << "4." << RESET << " Search ID         " << BLUE
            << "9." << RESET << " Valuation\n";
  std::cout << "  " << BLUE << "5." << RESET << " Search Name\n\n";

  std::cout << "  " << RED << "0. EXIT SYSTEM" << RESET << "\n";
  std::cout << "  " << std::string(35, '-') << "\n";
}

int main() {
  enableAnsiSupport();
  Inventory inv("inventory.csv");
  inv.load();
  std::string sortMode = "DEFAULT";

  while (true) {
    printMenu(inv, sortMode);
    int choice = getValidInt("  " + BOLD + WHITE + "Execute » " + RESET, 0);

    if (choice == 0)
      break;

    switch (choice) {
    case 1: {
      std::cout << "\n  " << BOLD << CYAN << " » NEW ASSET" << RESET << "\n";
      int id = getValidInt("    ID: ", 1);
      if (inv.findById(id)) {
        std::cout << "    " << RED << "ID CONFLICT." << RESET << "\n";
      } else {
        std::string name = getValidString("    Name: ");
        double price = getValidDouble("    Price ($): ", 0.0);
        int qty = getValidInt("    Initial Stock: ", 0);
        inv.add({id, name, price, qty});
        std::cout << "    " << GREEN << "ASSET LOGGED." << RESET << "\n";
        sortMode = "DEFAULT";
      }
      pause();
      break;
    }
    case 2: {
      std::cout << "\n  " << BOLD << CYAN << " » STOCK ADJUSTMENT" << RESET
                << "\n";
      int id = getValidInt("    Target ID: ", 1);
      if (!inv.findById(id)) {
        std::cout << "    " << RED << "ID UNKNOWN." << RESET << "\n";
      } else {
        int qty = getValidInt("    Set Stock: ", 0);
        double price = getValidDouble("    Set Price (-1 to keep): ", -1.0);
        inv.update(id, qty, price);
        std::cout << "    " << GREEN << "STOCK BALANCE UPDATED." << RESET
                  << "\n";
      }
      pause();
      break;
    }
    case 3: {
      std::cout << "\n  " << BOLD << CYAN << " » ASSET DISPOSAL" << RESET
                << "\n";
      int id = getValidInt("    Target ID: ", 1);
      std::string confirm = getValidString("    Confirm Disposal? (y/n): ");
      if (confirm == "y" || confirm == "Y") {
        if (inv.remove(id)) {
          std::cout << "    " << GREEN << "ASSET REMOVED." << RESET << "\n";
        } else {
          std::cout << "    " << RED << "ID UNKNOWN." << RESET << "\n";
        }
      }
      pause();
      break;
    }
    case 4: {
      int id = getValidInt("  Query ID: ", 1);
      const Product *p = inv.findById(id);
      if (p) {
        clearScreen();
        displayTable({*p}, sortMode);
      } else {
        std::cout << "  " << RED << "RESULT: NULL." << RESET << "\n";
      }
      pause();
      break;
    }
    case 5: {
      std::string query = getValidString("  Query Name: ");
      auto results = inv.searchByName(query);
      if (results.empty()) {
        std::cout << "  " << YELLOW << "RESULT: EMPTY." << RESET << "\n";
      } else {
        clearScreen();
        displayTable(results, sortMode);
      }
      pause();
      break;
    }
    case 6:
      inv.sortById();
      inv.save();
      sortMode = "ID (ASC)";
      std::cout << "\n    " << GREEN << "LOG: Executing sortById()..." << RESET
                << "\n";
      std::cout << "    " << GREEN << "SUCCESS: Products reordered by ID."
                << RESET << "\n";
      pause();
      break;
    case 7:
      inv.sortByName();
      inv.save();
      sortMode = "NAME (ASC)";
      std::cout << "\n    " << GREEN << "LOG: Executing sortByName()..."
                << RESET << "\n";
      std::cout << "    " << GREEN
                << "SUCCESS: Products reordered Alphabetically." << RESET
                << "\n";
      pause();
      break;
    case 8:
      inv.sortByPrice();
      inv.save();
      sortMode = "PRICE (ASC)";
      std::cout << "\n    " << GREEN << "LOG: Executing sortByPrice()..."
                << RESET << "\n";
      std::cout << "    " << GREEN << "SUCCESS: Products reordered by Price."
                << RESET << "\n";
      pause();
      break;
    case 9:
      std::cout << "\n  " << BOLD << MAGENTA << "VALUATION REPORT" << RESET
                << "\n";
      std::cout << "  Total Assets: " << BOLD << GREEN << "$" << std::fixed
                << std::setprecision(2) << inv.calculateTotalValue() << RESET
                << "\n";
      pause();
      break;
    default:
      std::cout << "  " << RED << "COMMAND INVALID." << RESET << "\n";
      pause();
    }
  }

  clearScreen();
  std::cout << "\n  " << BOLD << BLUE << "SYSTEM SECURED. PROCESS TERMINATED."
            << RESET << "\n";
  return 0;
}
