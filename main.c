#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splay_tree.h"
#include "plot.h"

int main() {
    int n;
    printf("Enter the number of days data is to be analysed : \n");
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
    while (count < n && fscanf(file, "%10s %f %d", date[count], &price[count], &volume[count]) == 3){
	    count++;
    }
    
    fclose(file);
        
    // Batch insert
    batchInsert(date, price, n);
    
	NodeArray arr;
    initNodeArray(&arr, 10); // Initial capacity of 10
    inOrder(root, &arr);
    printNodes(&arr);
    
    // Plot the prices
    plotPrices(&arr);
    
    // Clean up
    freeNodeArray(&arr);

    //printf("Stock prices:\n");
    //inOrder(root);

    // Searching for a specific date
    float search;
    // Searching for a specific date
    for (int i = 0;i<n;i++){
    	char searchDate[11] ;
	strcpy(searchDate, date[i]);
	char earchDate[11] = "10/27/2010 "; 
    	search = searchByDate(&root,earchDate);
	printf("The price is %f on %10s\n",search,earchDate); 
    }
    return 0;
}