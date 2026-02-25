#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Utils {
// ANSI Colors
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string BOLD = "\033[1m";

// Background Colors for "Connected" Bars
const std::string BG_RED = "\033[41m";
const std::string BG_GREEN = "\033[42m";
const std::string BG_YELLOW = "\033[43m";
const std::string BG_GRAY = "\033[100m";

inline void enableAnsiSupport() {
#ifdef _WIN32
  // Enable ANSI escape sequences
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hOut == INVALID_HANDLE_VALUE)
    return;
  DWORD dwMode = 0;
  if (!GetConsoleMode(hOut, &dwMode))
    return;
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hOut, dwMode);

  // Set console to UTF-8
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif
}

inline void clearScreen() {
  // Portably clear screen using ANSI escape sequences
  std::cout << "\033[2J\033[H" << std::flush;
}

inline void pause() {
  std::cout << "\n  Press ENTER to continue...";
  std::string dummy;
  std::getline(std::cin, dummy);
}

inline void clearInput() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

inline int getValidInt(const std::string &prompt,
                       int min = std::numeric_limits<int>::min()) {
  int val;
  while (true) {
    std::cout << prompt;
    if (std::cin >> val && val >= min) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return val;
    }
    std::cout << RED << "Invalid input. Please enter an integer (min: " << min
              << ")." << RESET << std::endl;
    clearInput();
  }
}

inline double getValidDouble(const std::string &prompt, double min = 0.0) {
  double val;
  while (true) {
    std::cout << prompt;
    if (std::cin >> val && val >= min) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return val;
    }
    std::cout << RED << "Invalid input. Please enter a positive number."
              << RESET << std::endl;
    clearInput();
  }
}

inline std::string getValidString(const std::string &prompt) {
  std::string val;
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, val);
    if (!val.empty())
      return val;
    std::cout << RED << "Input cannot be empty." << RESET << std::endl;
  }
}

inline void printHeader(const std::string &title) {
  std::cout << "\n"
            << BOLD << CYAN << "=== " << title << " ===" << RESET << "\n";
}
} // namespace Utils

#endif // UTILS_H
