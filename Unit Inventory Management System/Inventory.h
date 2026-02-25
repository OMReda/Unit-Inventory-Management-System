#ifndef INVENTORY_H
#define INVENTORY_H

#include "Product.h"
#include <string>
#include <unordered_map>
#include <vector>


class Inventory {
private:
  std::vector<Product> products;
  std::unordered_map<int, size_t> idToIndex;
  std::string filename;

  void updateIndex();
  void createBackup();

public:
  Inventory(const std::string &fname) : filename(fname) {}

  bool load();
  bool save();

  void add(const Product &p);
  bool remove(int id);
  bool update(int id, int newQty, double newPrice = -1.0);

  const std::vector<Product> &getProducts() const { return products; }
  const Product *findById(int id) const;
  std::vector<Product> searchByName(const std::string &query) const;

  void sortById();
  void sortByName();
  void sortByPrice();

  double calculateTotalValue() const;
};

#endif // INVENTORY_H
