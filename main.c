#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "splay_tree.h"
#include "plot.h"

int main() {
    printf("This code is the Splay Tree implementation for optimized stock price retrieval and prediction.\n");
    
    FILE *file = fopen("Project.txt", "r");
    if (!file) {
        fprintf(stderr, "Error opening file Project.txt\n");
        return 1;
    }
    NodeArray arr;
    initNodeArray(&arr, 10);
    int counts = 0;
    
    char choice;
    do {
        printf("Choose from the following functions: \n");
        printf("Insertion : I \n");
        printf("Plot Graph : G \n");
        printf("Search : S \n");
        printf("Date-wise Inorder traversal : T \n");
        printf("Predict : P \n");
        printf("Quit : Q \n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);  // Note the space before %c to consume any leftover newline

        switch (choice) {
            case 'I':
            case 'i': {
                char option;
                do {
                    printf("Do you want to insert data manually or extract data from the file Project.txt?\n");
                    printf("Manual Insertion : M \n");
                    printf("Automatic Insertion : A \n");
                    printf("Enter your choice: ");
                    scanf(" %c", &option);  // Note the space before %c to consume any leftover newline
                    switch (option) {
                        case 'A':
                        case 'a': {
                            int n;
                            printf("Enter the number of day's data to be inserted: ");
                            scanf("%d", &n);

                            // Declare arrays dynamically to avoid fixed size issues
                            char (*date)[11] = malloc(n * sizeof(char[11]));
                            float *price = malloc(n * sizeof(float));
                            int *volume = malloc(n * sizeof(int));

                            if (!date || !price || !volume) {
                                fprintf(stderr, "Memory allocation failed.\n");
                                return 1;
                            }

                            int count = 0;
                            while (count < n && fscanf(file, "%10s %f %d", date[count], &price[count], &volume[count]) == 3) {
                                count++;
                                counts++;
                            }

                            // Batch insert
                            batchInsert(&root, date, price, count);

                            // Free allocated memory for temporary arrays
                            free(date);
                            free(price);
                            free(volume);

                            break;
                        }
                        case 'M':
                        case 'm': {
                            int n;
                            printf("Enter the number of day's data to be inserted: ");
                            scanf("%d", &n);

                            char (*date)[11] = malloc(n * sizeof(char[11]));
                            float *price = malloc(n * sizeof(float));
                            int *volume = malloc(n * sizeof(int));

                            if (!date || !price || !volume) {
                                fprintf(stderr, "Memory allocation failed.\n");
                                return 1;
                            }

                            for (int i = 0; i < n; i++) {
                                printf("Enter date (MM/DD/YYYY): ");
                                scanf("%10s", date[i]);
                                printf("Enter price: ");
                                scanf("%f", &price[i]);
                                printf("Enter volume of stock traded: ");
                                scanf("%d", &volume[i]); // Use %d for integers

                                // Insert each entry one by one instead of in a batch
                                //insert(root, date[i], price[i]);
                            }
                            batchInsert(&root, date, price, n);

                            counts += n;

                            // Free allocated memory for temporary arrays
                            free(date);
                            free(price);
                            free(volume);

                            break;
                        }
                        default:
                            printf("Invalid option for insertion. Please try again.\n");
                            break;
                    }
                } while (option != 'A' && option != 'a' && option != 'M' && option != 'm');
                break;
            }
            case 'G':
            case 'g': {
                char option;
                do {
                    printf("Do you want to plot Prices or Volume of Stocks over time?\n");
                    printf("Prices : P\n");
                    printf("Volume : V\n");
                    printf("Enter your choice: ");
                    scanf(" %c", &option);  // Note the space before %c to consume any leftover newline

                    switch (option) {
                    case 'P':
                    case 'p': {
                        plotPrices(&arr);  // Call plotPrices function
                        printf("Plotting Prices over time.\n");
                        break;
                    }
            case 'V':
            case 'v': {
                // Add function call to plot Volume if implemented
                printf("Plotting Volume over time (to be implemented).\n");
                break;
            }
            default:
                printf("Invalid choice. Please enter P or V.\n");
                break;
            }
            } while (option != 'P' && option != 'p' && option != 'V' && option != 'v');  // Loop until valid option

            printf("Plotting function called.\n");
            break;
            }   
            case 'S':
            case 's': {
                char searchDate[11];
                printf("Enter date to search (MM/DD/YYYY): ");
                scanf("%10s", searchDate);
                clock_t start = clock();
                float searchPrice = searchByDate(&root, searchDate);
                if (searchPrice != -1) {
                    printf("The price is %.2f on %s\n", searchPrice, searchDate);
                } else {
                    printf("Date %s not found in the splay tree.\n", searchDate);
                }
                // Record the end time
                clock_t end = clock();

                // Calculate the elapsed time in seconds
                double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
                printf("myFunction() took %f seconds to execute.\n", time_taken);
                break;
            }
            case 'T':
            case 't':
                // Date-wise Inorder traversal
                freeNodeArray(&arr);
                initNodeArray(&arr, 10); // Reinitialize array after freeing it
                
                inOrder(root, &arr);
                
                printNodes(&arr);
                break;
            case 'P':
            case 'p': {
                char futureDate[11];
                printf("Enter the date (MM/DD/YYYY) for prediction: ");
                scanf("%10s", futureDate);
                float predictedPrice = predictPrice(&arr, futureDate);
                printf("Predicted price for %s: %.2f\n", futureDate, predictedPrice);
                break;
            }
            case 'Q':
            case 'q':
                printf("Quitting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 'Q' && choice != 'q');

    fclose(file);
    freeNodeArray(&arr);

    return 0;
}
