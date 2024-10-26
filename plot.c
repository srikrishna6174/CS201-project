#include <stdio.h>
#include <stdlib.h>
#include "plot.h" 

// Function to plot the prices using gnuplot
void plotPrices(const NodeArray* arr) {
    FILE *gnuplot_pipe = popen("gnuplot -persistent", "w");
    if (!gnuplot_pipe) {
        perror("Could not open gnuplot");
        exit(EXIT_FAILURE);
    }

    // Gnuplot commands
    fprintf(gnuplot_pipe, "set title 'Prices Over Time'\n");
    fprintf(gnuplot_pipe, "set xlabel 'Date'\n");
    fprintf(gnuplot_pipe, "set ylabel 'Price'\n");
    fprintf(gnuplot_pipe, "set xtics rotate by -45\n"); // Rotate x-axis labels
    fprintf(gnuplot_pipe, "plot '-' with linespoints title 'Price Data'\n");

    // Write data directly to gnuplot
    for (size_t i = 0; i < arr->size; i++) {
        fprintf(gnuplot_pipe, "%s %f\n", arr->nodes[i]->date, arr->nodes[i]->price);
    }

    // End of data
    fprintf(gnuplot_pipe, "e\n");
    pclose(gnuplot_pipe);
}