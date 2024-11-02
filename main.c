#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "splay_tree.h"  // Header for Splay Tree implementation
#include "plot.h"       // Header for plotting functionality

// Main function of the program
int main() {
    // Print a message indicating the purpose of the code
    printf("This code is the Splay Tree implementation for optimized stock price retrieval and prediction.\n");
    
    // Open the file Project.txt for reading
    FILE *file = fopen("Project.txt", "r");
    // Check if the file was opened successfully
    if (!file) {
        fprintf(stderr, "Error opening file Project.txt\n");
        return 1; // Exit the program with an error code
    }

    NodeArray arr; // Declare a NodeArray to hold nodes
    initNodeArray(&arr, 10);  // Initialize NodeArray with an initial size of 10
    int counts = 0; // Counter for the number of entries
    char choice; // Variable to store user choice

    do {
        // Display the menu of functions for the user
        printf("\nChoose from the following functions:\n");
        printf("Insertion : I\n");
        printf("Plot Graph : G\n");
        printf("Search : S\n");
        printf("Date-wise Inorder traversal : T\n");
        printf("Predict : P\n");
        printf("Quit : Q\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice); // Read user's choice

        switch (choice) {
            case 'I':
            case 'i': { // Insertion option
                char option; // Variable to store manual or automatic insertion choice
                do {
                    // Ask the user how to insert data
                    printf("\nInsert data manually or extract from file Project.txt?\n");
                    printf("Manual Insertion : M\n");
                    printf("Automatic Insertion : A\n");
                    printf("Enter your choice: ");
                    scanf(" %c", &option); // Read user's insertion method choice

                    switch (option) {
                        case 'A':
                        case 'a': { // Automatic insertion from file
                            int n; // Number of data entries to insert
                            printf("Enter the number of day's data to be inserted: ");
                            scanf("%d", &n); // Read number of entries

                            // Allocate memory for date, price, and volume arrays
                            char (*date)[11] = malloc(n * sizeof(char[11]));
                            float *price = malloc(n * sizeof(float));
                            int *volume = malloc(n * sizeof(int));

                            // Check if memory allocation was successful
                            if (!date || !price || !volume) {
                                fprintf(stderr, "Memory allocation failed.\n");
                                return 1; // Exit on failure
                            }

                            int count = 0; // Initialize counter for successful reads
                            // Read data from the file
                            while (count < n && fscanf(file, "%10s %f %d", date[count], &price[count], &volume[count]) == 3) {
                                count++;
                                counts++; // Increment the count of total entries
                            }

                            // Insert the read data into the splay tree
                            batchInsert(&root, date, price, volume, count);

                            // Free allocated memory for date, price, and volume
                            free(date);
                            free(price);
                            free(volume);

                            break; // Exit automatic insertion
                        }
                        case 'M':
                        case 'm': { // Manual insertion
                            int n; // Number of data entries to insert
                            printf("Enter the number of day's data to be inserted: ");
                            scanf("%d", &n); // Read number of entries

                            // Allocate memory for date, price, and volume arrays
                            char (*date)[11] = malloc(n * sizeof(char[11]));
                            float *price = malloc(n * sizeof(float));
                            int *volume = malloc(n * sizeof(int));

                            // Check if memory allocation was successful
                            if (!date || !price || !volume) {
                                fprintf(stderr, "Memory allocation failed.\n");
                                return 1; // Exit on failure
                            }

                            // Prompt the user to enter data manually
                            for (int i = 0; i < n; i++) {
                                printf("Enter date (MM/DD/YYYY): ");
                                scanf("%10s", date[i]); // Read date
                                printf("Enter price: ");
                                scanf("%f", &price[i]); // Read price
                                printf("Enter volume of stock traded: ");
                                scanf("%d", &volume[i]); // Read trading volume
                            }
                            // Insert the entered data into the splay tree
                            batchInsert(&root, date, price, volume, n);
                            counts += n; // Increment the total count

                            // Free allocated memory for date, price, and volume
                            free(date);
                            free(price);
                            free(volume);

                            break; // Exit manual insertion
                        }
                        default:
                            // Handle invalid option for insertion
                            printf("Invalid option for insertion. Please try again.\n");
                            break;
                    }
                } while (option != 'A' && option != 'a' && option != 'M' && option != 'm');
                break; // Exit insertion menu
            }
            case 'G':
            case 'g': { // Graph plotting option
                char option; // Variable to store user choice for plotting
                do {
                    // Ask the user what to plot
                    printf("Plot Prices or Volume of Stocks over time?\n");
                    printf("Prices : P\n");
                    printf("Volume : V\n");
                    printf("Enter your choice: ");
                    scanf(" %c", &option); // Read user's choice

                    switch (option) {
                        case 'P':
                        case 'p':
                            plotPrices(&arr); // Call function to plot prices
                            printf("Plotting Prices over time.\n");
                            break;
                        case 'V':
                        case 'v':
                            plotVolume(&arr); // Call function to plot volume
                            printf("Plotting Volume over time.\n");
                            break;
                        default:
                            // Handle invalid plotting option
                            printf("Invalid choice. Please enter P or V.\n");
                            break;
                    }
                } while (option != 'P' && option != 'p' && option != 'V' && option != 'v');
                break; // Exit plotting menu
            }
            case 'S':
            case 's': { // Search option
                char searchDate[11]; // Variable to store the date for searching
                printf("Enter date to search (MM/DD/YYYY): ");
                scanf("%10s", searchDate); // Read date

                // Measure the time taken for the search operation
                clock_t start = clock();
                float searchPrice = searchByDate(&root, searchDate); // Perform search
                clock_t end = clock();

                // Output the result of the search
                if (searchPrice != -1) {
                    printf("The price on %s is %.2f\n", searchDate, searchPrice);
                } else {
                    printf("Date %s not found in the splay tree.\n", searchDate);
                }
                
                // Calculate and display the time taken for the search operation
                double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
                printf("Search function took %f seconds to execute.\n", time_taken);
                break; // Exit search option
            }
            case 'T':
            case 't': // Date-wise Inorder traversal option
                freeNodeArray(&arr); // Free previously allocated nodes
                initNodeArray(&arr, 10); // Re-initialize NodeArray
                inOrder(root, &arr); // Perform in-order traversal of the tree
                printNodes(&arr); // Print the nodes in the array
                break; // Exit traversal option
            case 'P':
            case 'p': { // Prediction option
                char futureDate[11]; // Variable to store the date for prediction
                printf("Enter the date (MM/DD/YYYY) for prediction: ");
                scanf("%10s", futureDate); // Read the future date
                float predictedPrice = predictPrice(&arr, futureDate); // Predict price for the date
                printf("Predicted price for %s: %.2f\n", futureDate, predictedPrice);
                
                double mse = calculateMSE(&arr); // Calculate Mean Squared Error (MSE)
                if (isnan(mse)) {
                    printf("Error: MSE calculation failed.\n");
                } else {
                    printf("Mean Squared Error (MSE): %.4f\n", mse); // Output the MSE
                }
                break; // Exit prediction option
            }
            case 'Q':
            case 'q': // Quit option
                printf("Quitting the program.\n");
                break; // Exit the main loop
            default:
                // Handle invalid main menu choice
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 'Q' && choice != 'q'); // Continue until the user chooses to quit

    fclose(file); // Close the file after use
    freeNodeArray(&arr); // Free memory allocated for the NodeArray

    return 0; // Successful program termination
}
