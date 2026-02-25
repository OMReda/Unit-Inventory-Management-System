#include "Inventory.h"
#include <cassert>
#include <filesystem>
#include <iostream>


namespace fs = std::filesystem;

void testBasicOperations() {
  std::string testFile = "test_inventory.csv";
  if (fs::exists(testFile))
    fs::remove(testFile);

  Inventory inv(testFile);

  // Test Add
  inv.add({101, "Test Widget", 19.99, 50});
  assert(inv.getProducts().size() == 1);
  assert(inv.findById(101)->name == "Test Widget");

  // Test Search
  auto results = inv.searchByName("Widget");
  assert(results.size() == 1);

  // Test Update
  inv.update(101, 60, 24.99);
  assert(inv.findById(101)->quantity == 60);
  assert(inv.findById(101)->price == 24.99);

  // Test Persistence
  Inventory inv2(testFile);
  inv2.load();
  assert(inv2.getProducts().size() == 1);
  assert(inv2.findById(101)->name == "Test Widget");

  // Test Backup
  assert(fs::exists("inventory_backup.txt"));

  // Test Delete
  inv.remove(101);
  assert(inv.getProducts().size() == 0);

  std::cout << "All basic assertions passed!" << std::endl;

  if (fs::exists(testFile))
    fs::remove(testFile);
}

int main() {
  testBasicOperations();
  return 0;
}
