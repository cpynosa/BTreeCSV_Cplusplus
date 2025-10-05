#include <iostream>
#include "csvManager.h"
#include <memory>
struct BTreeNode{
     std::unique_ptr<int[]> nodeElements;
     std::unique_ptr<std::unique_ptr<BTreeNode>[]> children;
     int keyCounter = 0;
     bool isLeaf = true;
};

class BTree {
private:
    std::unique_ptr<BTreeNode> root;
    int treeDegree;
    int maxKeys;
    int minKeys;
    int medianIndex;

    bool const checkTreeDegree(){

        if(this->treeDegree < 2){
            std::cout << "Invalid degree, try again." << std::endl;
            return false;
        }
        return true;
    }
    void getTreeDegree(){
        std::cout << "Type the tree degree (2<=t): ";
        std::cin >> this->treeDegree;
    }

    std::unique_ptr<BTreeNode> createNode(bool isLeaf) {
        auto node = std::make_unique<BTreeNode>();
        node->nodeElements = std::make_unique<int[]>(maxKeys);
        node->children = std::make_unique<std::unique_ptr<BTreeNode>[]>(maxKeys + 1);
        node->isLeaf = isLeaf;
        return node;
    }

    bool isNodeFull(BTreeNode* node){return node->keyCounter == this->maxKeys;}

    int indexInsertSearch(int value, int elements[], BTreeNode* node){
        for(int i = 0; i < node->keyCounter; i++)
        {
            if(value < elements[i])return i;
        }
        return node->keyCounter;
    }

    void displaceElements(int index, int elements[], int keyCounter){
        for(int i = keyCounter; i>index; i--){
            elements[i] = elements[i-1];
        }
    }

    void splitRoot(){
        auto newRoot = createNode(false);
        auto leftChild = root.get();
        auto rightChild = createNode(true);


        for(int i = 0; i < minKeys; ++i){
            rightChild->nodeElements[i] = leftChild->nodeElements[i + treeDegree];
        }

        leftChild->keyCounter = minKeys;
        rightChild->keyCounter = minKeys;

        newRoot->children[0] = std::move(root);
        newRoot->children[1] = std::move(rightChild);

        newRoot->nodeElements[0] = newRoot->children[0]->nodeElements[medianIndex];
        newRoot->keyCounter = 1;
        root = std::move(newRoot);


    }




public:

    BTree(int firstKey) {
        do{getTreeDegree();}while(!checkTreeDegree());
        this->maxKeys = (2 * this->treeDegree) - 1;
        this->minKeys = treeDegree - 1;
        this->medianIndex = this->treeDegree-1;

        root = createNode(true);
        root->nodeElements[0] = firstKey;
        this->root->keyCounter = 1;

    }

    BTreeNode* getRoot(){return this->root.get();}

    void insertKey(int value){

        if(isNodeFull(root.get())){
            splitRoot();
        }

        int index = indexInsertSearch(value, root->nodeElements.get(), root.get());
        displaceElements(index, root->nodeElements.get(), root->keyCounter);
        root->nodeElements[index] = value;
        root->keyCounter += 1;
    }
    void const print(BTreeNode* node){
        for(int i = 0; i < node->keyCounter; ++i){
            std::cout << node->nodeElements[i] << " ";
        }
    }
};


int main() {
	CSVFile csvFile;
	string const fileName = "C:/Users/razoc/CLionProjects/BTreeCSV_Cplusplus/cmake-build-debug/products.csv";
	//csvFile.add_product({ 1, "Laptop", 10000.25 });
	//csvFile.add_product({ 2, "Mouse", 300.25 });
	//csvFile.write(fileName);
	bool header = true;
	csvFile.read(fileName, header);
	csvFile.print();
    BTree b(9);
    b.insertKey(3);
    b.insertKey(10);
    b.print(b.getRoot());
    b.insertKey(5);
    b.print(b.getRoot());
    // Falta buscar el hijo en el cual se debe insertar y generalizar la subida de nodos
	return 0;
}
//Transformar string a un producto
//Cada nodo será un archivo y las claves estarán dentro del archivo en el árbol B