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
    printf("Enter the number of latest days data to analyze: ");
    scanf("%d", &n);

    // Arrays to store date, price, and volume data
    char date[1000][11];
    float price[1000];
    int volume[1000];

    FILE *file = fopen("Project.txt", "r");
    if (!file) {
        fprintf(stderr, "Error opening file\n");
        return EXIT_FAILURE;
    }

    // Read all entries from the file
    int totalCount = 0;
    while (fscanf(file, "%10s %f %d", date[totalCount], &price[totalCount], &volume[totalCount]) == 3) {
        totalCount++;
        if (totalCount >= 1000) break;  // Prevent exceeding array bounds
    }
    fclose(file);

    // Adjust `n` if more data is requested than available
    if (n > totalCount) {
        fprintf(stderr, "Only %d entries available, adjusting `n` to %d.\n", totalCount, totalCount);
        n = totalCount;
    }

    // Calculate start index to use only the last `n` entries
    int startIndex = totalCount - n;

    // Batch insert only the last `n` entries
    batchInsert(&root, &date[startIndex], &price[startIndex], n);

    // Prepare NodeArray for in-order traversal
    NodeArray arr;
    initNodeArray(&arr, 10); // Initial capacity of 10
    inOrder(root, &arr);
    printNodes(&arr);

    // Plot the prices
    plotPrices(&arr);

    // Clean up
    freeNodeArray(&arr);

    // Searching for specific dates in the last `n` entries
    for (int i = startIndex; i < totalCount; i++) {
        float search = searchByDate(&root, date[i]);
        if (search != -1) {
            printf("The price is %.2f on %s\n", search, date[i]);
        } else {
            printf("Date %s not found in the splay tree.\n", date[i]);
        }
    }

    // Get future date from user and predict price
    char futureDate[11];
    printf("Enter the future date (MM/DD/YYYY) for prediction: ");
    scanf("%10s", futureDate);
    
    float predictedPrice = predictPrice(&date[startIndex], &price[startIndex], n, futureDate);
    printf("Predicted price for %s: %.2f\n", futureDate, predictedPrice);

    return 0;
}
