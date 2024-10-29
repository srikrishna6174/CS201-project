#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splay_tree.h"

#define NOT_FOUND_PRICE -1 // Define a constant for "not found" prices

Node* root = NULL; // Initialize the root as NULL

// Right rotation
Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Function to create a new node
Node* createNode(char* date, float price) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL; // Check for allocation failure
    strcpy(newNode->date, date);
    newNode->price = price;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Check if a year is a leap year
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// This function converts a date string to the number of days for comparison
// If an invalid date is provided  , the function returns -1.
int dateToDays(char* date) {
    int year, month, day;
    if (sscanf(date, "%d/%d/%d", &month, &day, &year) != 3) {
        return -1; // Invalid format
    }

    // Check for valid month and day
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return -1; // Invalid month or day
    }

    // Days in each month
    int monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) {
        monthDays[2] = 29; // Adjust for leap year
    }

    // Check for valid day in the specific month
    if (day > monthDays[month]) {
        return -1; // Invalid day for the given month
    }

    // Calculate total days up to the given year
    int totalDays = year * 365 + year / 4 - year / 100 + year / 400;

    for (int i = 1; i < month; i++) {
        totalDays += monthDays[i];
    }

    totalDays += day;

    return totalDays;
}

// Splay operation
Node* splay(Node* root, char* date) {
    if (root == NULL || dateToDays(root->date) == dateToDays(date))
        return root;

    // Date is smaller than root's date
    if (dateToDays(date) < dateToDays(root->date)) {
        if (root->left == NULL) return root;

        // Zig-Zig (Left Left)
        if (dateToDays(date) < dateToDays(root->left->date)) {
            root->left = splay(root->left, date);
            root = rightRotate(root);
        }
        // Zig-Zag (Left Right)
        else if (dateToDays(date) > dateToDays(root->left->date)) {
            root->left->right = splay(root->left->right, date);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        return (root->left == NULL) ? root : rightRotate(root);
    } else { // Date is greater than root's date
        if (root->right == NULL) return root;

        // Zag-Zag (Right Right)
        if (dateToDays(date) > dateToDays(root->right->date)) {
            root->right = splay(root->right, date);
            root = leftRotate(root);
        }
        // Zag-Zig (Right Left)
        else if (dateToDays(date) < dateToDays(root->right->date)) {
            root->right->left = splay(root->right->left, date);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }

        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// Insert a new node
Node* insert(Node* root, char* date, float price) {
    if (root == NULL) return createNode(date, price);

    root = splay(root, date);

    if (dateToDays(date) == dateToDays(root->date)) {
        // If the date already exists, update the price
        root->price = price;
        return root;
    }

    Node* newNode = createNode(date, price);
    if (!newNode) return NULL; // Check for allocation failure

    if (dateToDays(date) < dateToDays(root->date)) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = NULL;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = NULL;
    }

    return newNode;
}

// Batch insert function
void batchInsert(Node** root, char dates[][11], float prices[], int size) {
    for (int i = 0; i < size; i++) {
        *root = insert(*root, dates[i], prices[i]);
    }
}

// Search by date
float searchByDate(Node** root, char* date) {
    if (*root == NULL) {
        printf("Invalid date: %s\n", date);
        return NOT_FOUND_PRICE;
    }

    *root = splay(*root, date);

    if (dateToDays((*root)->date) == dateToDays(date)) {
        return (*root)->price;
    } else {
        printf("Invalid date: %s\n", date);
        return NOT_FOUND_PRICE;
    }
}

// Initialize a dynamic array of nodes
void initNodeArray(NodeArray* arr, size_t initialCapacity) {
    arr->nodes = malloc(initialCapacity * sizeof(Node*));
    if (arr->nodes == NULL) {
        fprintf(stderr, "Memory allocation failed for NodeArray\n");
        exit(1);
    }
    arr->size = 0;
    arr->capacity = initialCapacity;
}

// Free the node array
void freeNodeArray(NodeArray* arr) {
    if (arr->nodes != NULL) {
        free(arr->nodes);
    }
}

// In-order traversal to populate the NodeArray
void inOrder(Node* root, NodeArray* arr) {
    if (root) {
        inOrder(root->left, arr);

        if (arr->size == arr->capacity) {
            Node** newNodes = realloc(arr->nodes, arr->capacity * 2 * sizeof(Node*));
            if (newNodes == NULL) {
                fprintf(stderr, "Reallocation failed for NodeArray\n");
                exit(1);
            }
            arr->nodes = newNodes;
            arr->capacity *= 2;
        }

        arr->nodes[arr->size++] = root;

        inOrder(root->right, arr);
    }
}

// Print all nodes in the NodeArray
void printNodes(const NodeArray* arr) {
    for (size_t i = 0; i < arr->size; ++i) {
        printf("Date: %s, Price: %.2f\n", arr->nodes[i]->date, arr->nodes[i]->price);
    }
}
