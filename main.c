#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splay_tree.h"
#include "plot.h"

int main() {
    int n;
    printf("Enter the number of days data is to be analyzed: \n");
    scanf("%d", &n);

    char date[n][11];
    float price[n];
    int volume[n];

    FILE *file = fopen("Project.txt", "r");
    if (!file) {
        fprintf(stderr, "Error opening file\n");
        return EXIT_FAILURE;
    }

    int count = 0;
    while (count < n && fscanf(file, "%10s %f %d", date[count], &price[count], &volume[count]) == 3) {
        count++;
    }
    fclose(file);

    if (count < n) {
        fprintf(stderr, "Error: Only %d entries found in file, expected %d\n", count, n);
        return EXIT_FAILURE;
    }

    // Batch insert
    batchInsert(&root, date, price, n);

    NodeArray arr;
    initNodeArray(&arr, 10); // Initial capacity of 10
    inOrder(root, &arr);
    printNodes(&arr);

    // Plot the prices
    plotPrices(&arr);

    // Clean up
    freeNodeArray(&arr);

    // Searching for specific dates
    for (int i = 0; i < n; i++) {
        float search = searchByDate(&root, date[i]);
        if (search != -1) {
            printf("The price is %.2f on %s\n", search, date[i]);
        } else {
            printf("Date %s not found in the splay tree.\n", date[i]);
        }
    }

    return 0;
}
