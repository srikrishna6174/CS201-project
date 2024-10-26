#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

typedef struct Node {
    char date[11]; // Format: MM/DD/YYYY
    float price;
    struct Node* left;
    struct Node* right;
} Node;


typedef struct {
    Node** nodes; // Array of pointers to Node
    size_t size;  // Current number of nodes in the array
    size_t capacity; // Capacity of the array
} NodeArray;

extern struct Node* root;

// Splay tree functions
Node* splay(Node* root, char* date);
Node* insert(Node* root, char* date, float price);

// splay_tree.h

// Other declarations...

void batchInsert(Node** root, char dates[][11], float prices[], int size);

//Stock* update_stock_price(Stock* root, char* symbol, float price);
float searchByDate(Node** root, char* date);
void printNodes(const NodeArray* arr);  // Helper function to display tree
void initNodeArray(NodeArray* arr, size_t initialCapacity);
void freeNodeArray(NodeArray* arr);
void inOrder(Node* root, NodeArray* arr);
#endif
