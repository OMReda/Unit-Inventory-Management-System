#include "Inventory.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

void Inventory::updateIndex() {
  idToIndex.clear();
  for (size_t i = 0; i < products.size(); ++i) {
    idToIndex[products[i].id] = i;
  }
}

void Inventory::createBackup() {
  if (fs::exists(filename)) {
    fs::copy_file(filename, "inventory_backup.txt",
                  fs::copy_options::overwrite_existing);
  }
}

bool Inventory::load() {
  products.clear();
  std::ifstream file(filename);
  if (!file.is_open())
    return false;

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;
    try {
      products.push_back(Product::fromCSV(line));
    } catch (...) {
    } // Skip malformed lines
  }
  file.close();
  updateIndex();
  return true;
}

bool Inventory::save() {
  createBackup();
  std::ofstream file(filename);
  if (!file.is_open())
    return false;

  for (const auto &p : products) {
    file << p.toCSV() << "\n";
  }
  file.close();
  return true;
}

void Inventory::add(const Product &p) {
  products.push_back(p);
  save();
  updateIndex();
}

bool Inventory::remove(int id) {
  auto it = idToIndex.find(id);
  if (it != idToIndex.end()) {
    products.erase(products.begin() + it->second);
    save();
    updateIndex();
    return true;
  }
  return false;
}

bool Inventory::update(int id, int newQty, double newPrice) {
  auto it = idToIndex.find(id);
  if (it != idToIndex.end()) {
    products[it->second].quantity = newQty;
    if (newPrice >= 0)
      products[it->second].price = newPrice;
    save();
    return true;
  }
  return false;
}

const Product *Inventory::findById(int id) const {
  auto it = idToIndex.find(id);
  if (it != idToIndex.end()) {
    return &products[it->second];
  }
  return nullptr;
}

std::vector<Product> Inventory::searchByName(const std::string &query) const {
  std::vector<Product> results;
  std::string lowerQuery = query;
  std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(),
                 ::tolower);

  for (const auto &p : products) {
    std::string lowerName = p.name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                   ::tolower);
    if (lowerName.find(lowerQuery) != std::string::npos) {
      results.push_back(p);
    }
  }
  return results;
}

void Inventory::sortById() {
  std::ofstream trace("execution_trace.txt", std::ios::app);
  trace << "DEBUG: sortById() executed.\n";
  trace.close();
  std::sort(products.begin(), products.end(),
            [](const Product &a, const Product &b) { return a.id < b.id; });
  updateIndex();
}

void Inventory::sortByName() {
  std::ofstream trace("execution_trace.txt", std::ios::app);
  trace << "DEBUG: sortByName() executed.\n";
  trace.close();
  std::sort(
      products.begin(), products.end(), [](const Product &a, const Product &b) {
        std::string nameA = a.name;
        std::string nameB = b.name;
        std::transform(nameA.begin(), nameA.end(), nameA.begin(), ::tolower);
        std::transform(nameB.begin(), nameB.end(), nameB.begin(), ::tolower);
        return nameA < nameB;
      });
  updateIndex();
}

void Inventory::sortByPrice() {
  std::ofstream trace("execution_trace.txt", std::ios::app);
  trace << "DEBUG: sortByPrice() executed.\n";
  trace.close();
  std::sort(
      products.begin(), products.end(),
      [](const Product &a, const Product &b) { return a.price < b.price; });
  updateIndex();
}

double Inventory::calculateTotalValue() const {
  double total = 0;
  for (const auto &p : products) {
    total += p.price * p.quantity;
  }
  return total;
}
