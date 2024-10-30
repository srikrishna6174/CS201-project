//1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splay_tree.h"
#include "plot.h"

int main() {
    int n;
    printf("Enter the number of latest days data to analyze: ");
    scanf("%d", &n);

    // Arrays to store date, price, and volume data
    char date[n][11];
    float price[n];
    int volume[n];

    FILE *file = fopen("Project.txt", "r");
    if (!file) {
        fprintf(stderr, "Error opening file\n");
        return EXIT_FAILURE;
    }

    // Read all entries from the file
    int totalCount = 0;
    while (fscanf(file, "%10s %f %d", date[totalCount], &price[totalCount], &volume[totalCount]) == 3) {
        totalCount++;
        if (totalCount >= n) break;  // Prevent exceeding array bounds
    }
    fclose(file);

    // Adjust `n` if more data is requested than available
    /*if (n > totalCount) {
        fprintf(stderr, "Only %d entries available, adjusting `n` to %d.\n", totalCount, totalCount);
        n = totalCount;
    }*/

    // Calculate start index to use only the last `n` entries
    //int startIndex = totalCount - n;

    // Batch insert only the last `n` entries
    batchInsert(&root, date, price, n);
    /*int sx = 0;
    float sy = 0;
    int sxx = 0;
    float sxy = 0;
    int diff = dateToDays(date[0]);

    for (int i = 0; i < n; i++) {
        int x_value = dateToDays(date[i]) - diff + 1; // X value after transformation
        sx += x_value;
        sy += price[i];
        sxx += (x_value * x_value);      // Square of x_value
        sxy += (x_value * price[i]);     // x_value * corresponding y_value (price)
    }

    printf("sx = %d\n", sx);
    printf("sy = %f\n", sy);
    printf("sxx = %d\n", sxx);
    printf("sxy = %f\n", sxy);
    float slope = ((n * sxy) - (sx * sy)) / ((n * sxx) - (sx * sx));
    printf("Slope = %f\n", slope);
    */


    // Prepare NodeArray for in-order traversal
    NodeArray arr;
    initNodeArray(&arr, 10); // Initial capacity of 10
    inOrder(root, &arr);
    
    // Plot the prices
    //plotPrices(date,price,n-1);

    printNodes(&arr);

    // Clean up
   
    /*
    // Searching for speci12fic dates in the last `n` entries
    for (int i = startIndex; i < totalCount; i++) {
        float search = searchByDate(&root, date[i]);
        if (search != -1) {
            printf("The price is %.2f on %s\n", search, date[i]);
        } else {
            printf("Date %s not found in the splay tree.\n", date[i]);
        }
    }

    char v[11];
    printf("Enter the date (MM/DD/YYYY) for search: ");
    scanf("%10s",&v);
    float search = searchByDate(&root, v);
    if (search != -1) {
        printf("The price is %.2f on %s\n", search, v);
    } else {
        printf("Date %s not found in the splay tree.\n", v);
    }

     Get future date from user and predict price*/
    char futureDate[11];
    printf("Enter the future date (MM/DD/YYYY) for prediction: ");
    scanf("%10s", futureDate);
    
    float predictedPrice = predictPrice(&arr,futureDate);
    printf("Predicted price for %s: %.2f\n", futureDate, predictedPrice);
    freeNodeArray(&arr);

    return 0;
}
