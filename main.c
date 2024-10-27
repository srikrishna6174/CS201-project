#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splay_tree.h"
#include "plot.h"

int main() {
    printf("This code is the Splay Tree implementation for Optimized stock price retrieval and prediction.\n");
    
    FILE *file = fopen("Project.txt", "r");
    int counts = 0;
    
    
    char choice;
    do {
        printf("Choose from the following functions: \n");
        printf("Insertion : I \n");
        printf("Deletion : D \n");
        printf("Search : S \n");
        printf("Date wise Inorder traversal : T \n");
        printf("Predict : P \n");
        printf("Quit : Q \n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);  // Note the space before %c to consume any leftover newline

        switch (choice) {
            case 'I':
            case 'i':
                
                char option;
                do {
                    printf("Do you want Insert Data Manually or Extract Data from the file Project.txt \n");
                    printf("Manual Insertion : M \n");
                    printf("Automatic Insertion : A \n");
                    printf("Enter your choice: ");
                    scanf(" %c", &option);  // Note the space before %c to consume any leftover newline
                    switch (option){
                        case 'A':
                        case 'a':{
                            int n;
                            printf("Enter the number of day's data to be inserted \n");
                            scanf("%d", &n);

                            char date[n][11];
                            float price[n];
                            int volume[n];
                            int count = 0;
                            while (count < n && fscanf(file, "%10s %f %d", date[counts], &price[counts], &volume[counts]) == 3) {
                                count++;
                                counts++;
                            }
                            // Batch insert
                            batchInsert(&root, date, price, n);
                            break;
                        }
                        case 'M':
                        case 'm':{
                            int n;
                            printf("Enter the number of day's data to be inserted \n");
                            scanf("%d", &n);

                            char date[n][11];
                            float price[n];
                            int volume[n];
                            int count = 0;
                            while (count < n && fscanf(file, "%10s %f %d", date[counts], &price[counts], &volume[counts]) == 3) {
                                count++;
                                counts++;
                            }
                            // Batch insert
                            batchInsert(&root, date, price, n);
                            break;
                            
                            
                        }
                        
                        
                    }
                }
                // Handle insertion (you might want to prompt for new data here)
                // Example: insert(&root, new_date, new_price, new_volume);
                printf("Insertion function called.\n");
                break;
            case 'D':
            case 'd':
                // Handle deletion (you might want to prompt for a date to delete)
                // Example: deleteByDate(&root, date_to_delete);
                printf("Deletion function called.\n");
                break;
            case 'S':
            case 's': {
                char searchDate[11];
                printf("Enter date to search (YYYY-MM-DD): ");
                scanf("%10s", searchDate);
                float searchPrice = searchByDate(&root, searchDate);
                if (searchPrice != -1) {
                    printf("The price is %.2f on %s\n", searchPrice, searchDate);
                } else {
                    printf("Date %s not found in the splay tree.\n", searchDate);
                }
                break;
            }
            case 'T':
            case 't':
                // Date wise Inorder traversal
                NodeArray arr;
                initNodeArray(&arr, 10); // Initial capacity of 10
                inOrder(root, &arr);
                printNodes(&arr);
                freeNodeArray(&arr);
                break;
            case 'P':
            case 'p':
                // Call the prediction function
                printf("Prediction function called.\n");
                break;
            case 'Q':
            case 'q':
                printf("Quitting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 'Q' && choice != 'q');
    fclose(file);

    return 0;
}
