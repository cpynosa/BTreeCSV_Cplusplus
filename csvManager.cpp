//
// Created by razoc on 01/10/2025.
//

#include "csvManager.h"
#include <sstream>

void CSVFile::add_product(const Product &p){
    this->products.push_back(p);
}
void CSVFile::print() const {
    for (const auto& product : products) {
        std::cout << "ID: " << product.id << std::endl;
        std::cout << "Name: " << product.name << std::endl;
        std::cout << "Price: " << product.price << std::endl;
        std::cout << std::endl;
    }
}
void CSVFile::write(const string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error al abrir el archivo";
        return;
    }
    file << "id, name, price \n";
    for (const auto& product : products) {
        file << product.id;
        file << "," << product.name;
        file << "," << product.price;
        file << std::endl;
    }
}
void CSVFile::read(const string& filename, bool header) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error al abrir el archivo";
        return;
    }
    string line;

    while (std::getline(file, line)) {
        char delimiter = ',';
        if (header) {
            header = false;
            continue;
        }
        std::istringstream ss(line);
        string id_str, name, price_str;


        std::getline(ss, id_str, delimiter);
        std::getline(ss, name, delimiter);
        std::getline(ss, price_str, delimiter);
        Product p;
        p.id = std::stoi(id_str);
        p.name = name;
        p.price = std::stod(price_str);
        products.push_back(p);
    }
}