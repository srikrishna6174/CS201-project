#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splay_tree.h"

// Function to convert date string (MM/DD/YYYY) to an integer for regression
int dateToInt(char* date) {
    int month, day, year;
    sscanf(date, "%d/%d/%d", &month, &day, &year);
    return year * 10000 + month * 100 + day;
}

// Function to perform linear regression and predict the price for a future date
float predictPrice(char dates[][11], float prices[], int size, char* futureDate) {
    int *x = malloc(size * sizeof(int)); // Store dates as integers
    float *y = prices;

    // Convert dates to integers
    for (int i = 0; i < size; i++) {
        x[i] = dateToInt(dates[i]);
    }

    // Linear regression calculations
    float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    for (int i = 0; i < size; i++) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    float slope = (size * sumXY - sumX * sumY) / (size * sumX2 - sumX * sumX);
    float intercept = (sumY - slope * sumX) / size;

    // Convert the future date to an integer
    int futureX = dateToInt(futureDate);

    // Predict price
    float predictedPrice = slope * futureX + intercept;

    free(x);
    return predictedPrice;
}

int main() {
    int n;
    printf("Enter the number of days data to analyze: ");
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

    // Prediction for a future date
    char futureDate[11];
    printf("Enter the future date (MM/DD/YYYY) for prediction: ");
    scanf("%10s", futureDate);

    float predictedPrice = predictPrice(date, price, n, futureDate);
    printf("Predicted price for %s: %.2f\n", futureDate, predictedPrice);

    return 0;
}
