#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
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
	double price = 0;
};

class CSVFile : public FileHandler {
private:
	vector<Product> products;
public:
	void add_product(const Product& p) {
		this->products.push_back(p);
	}
	void print() {
		for (const auto& product : products) {
			std::cout << "ID: " << product.id << std::endl;
			std::cout << "Name: " << product.name << std::endl;
			std::cout << "Price: " << product.price << std::endl;
			std::cout << std::endl;
		}
	}
	void write(const string& filename) override {
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
	void read(const string& filename, bool header) override {
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cout << "Error al abrir el archivo";
			return;
		}
		string line;
		char delimiter = ',';

		while (std::getline(file, line)) {
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

};

int main() {
	CSVFile csvFile;
	string fileName = "products.csv";
	csvFile.add_product({ 1, "Laptop", 10000.25 });
	csvFile.add_product({ 2, "Mouse", 300.25 });
	csvFile.write(fileName);
	bool header = true;
	csvFile.read(fileName, header);
	//csvFile.print();
	return 0;
}
//Transformar string a un producto
//Cada nodo será un archivo y las claves estarán dentro del archivo en el árbol B