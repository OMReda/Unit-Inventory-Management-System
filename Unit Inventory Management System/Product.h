#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <sstream>
#include <vector>

struct Product {
    int id;
    std::string name;
    double price;
    int quantity;

    std::string toCSV() const {
        return std::to_string(id) + "," + name + "," + std::to_string(price) + "," + std::to_string(quantity);
    }

    static Product fromCSV(const std::string& line) {
        std::stringstream ss(line);
        std::string item;
        Product p;
        
        std::getline(ss, item, ',');
        p.id = std::stoi(item);
        
        std::getline(ss, p.name, ',');
        
        std::getline(ss, item, ',');
        p.price = std::stod(item);
        
        std::getline(ss, item, ',');
        p.quantity = std::stoi(item);
        
        return p;
    }
};

#endif // PRODUCT_H
