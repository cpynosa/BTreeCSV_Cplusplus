#include <iostream>
#include "csvManager.h"

int main() {
	CSVFile csvFile;
	string const fileName = "C:/Users/razoc/CLionProjects/BTreeCSV_Cplusplus/cmake-build-debug/products.csv";
	//csvFile.add_product({ 1, "Laptop", 10000.25 });
	//csvFile.add_product({ 2, "Mouse", 300.25 });
	//csvFile.write(fileName);
	bool header = true;
	csvFile.read(fileName, header);
	csvFile.print();
	return 0;
}
//Transformar string a un producto
//Cada nodo será un archivo y las claves estarán dentro del archivo en el árbol B