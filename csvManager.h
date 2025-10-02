//
// Created by razoc on 01/10/2025.
//

#ifndef BTREECSV_CPLUSPLUS_CSVMANAGER_H
#define BTREECSV_CPLUSPLUS_CSVMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using std::string;
using std::vector;

class FileHandler {
public:
    virtual ~FileHandler() = default;
    virtual void write(const string& file) = 0;
    virtual void read(const string& file, bool header) = 0;

};
struct Product {
    int id = 0;
    string name;
    double price = 0.0;
};

class CSVFile : public FileHandler {
private:
    vector<Product> products;
public:
    void add_product(const Product& p);
    void print() const;
    void write(const string& filename) override;
    void read(const string& filename, bool header) override;
};

#endif //BTREECSV_CPLUSPLUS_CSVMANAGER_H