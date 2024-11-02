#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plot.h"

void plotPrices(const NodeArray* arr) {
    FILE *gnuplot_pipe = popen("gnuplot -persistent", "w");
    if (!gnuplot_pipe) {
        perror("Could not open gnuplot");
        exit(EXIT_FAILURE);
    }

    // Gnuplot configuration
    fprintf(gnuplot_pipe, "set terminal wxt size 1000, 400\n");
    fprintf(gnuplot_pipe, "set title 'Stock Prices Over Time'\n");
    fprintf(gnuplot_pipe, "set xlabel 'Date'\n");
    fprintf(gnuplot_pipe, "set ylabel 'Price'\n");
    fprintf(gnuplot_pipe, "set xdata time\n");
    fprintf(gnuplot_pipe, "set timefmt '\"%%m/%%d/%%Y\"'\n");
    fprintf(gnuplot_pipe, "set format x '%%m/%%d/%%Y'\n");
    fprintf(gnuplot_pipe, "set grid\n");
    fprintf(gnuplot_pipe, "set xtics rotate by -45\n");
    fprintf(gnuplot_pipe, "set style line 1 lc rgb '#0060ad' lw 2 pt 7 ps 1.5\n");

    // Plot command
    fprintf(gnuplot_pipe, "plot '-' using 1:2 with linespoints linestyle 1 title 'Price Data'\n");

    // Pass data to Gnuplot from NodeArray
    for (size_t i = 0; i < arr->size; i++) {
        fprintf(gnuplot_pipe, "\"%s\" %f\n", arr->nodes[i]->date, arr->nodes[i]->price);
    }

    fprintf(gnuplot_pipe, "e\n");
    pclose(gnuplot_pipe);
}

void plotVolume(const NodeArray* arr) {
    FILE *gnuplot_pipe = popen("gnuplot -persistent", "w");
    if (!gnuplot_pipe) {
        perror("Could not open gnuplot");
        exit(EXIT_FAILURE);
    }

    // Gnuplot configuration
    fprintf(gnuplot_pipe, "set terminal wxt size 1000, 400\n");
    fprintf(gnuplot_pipe, "set title 'Stock Volume Over Time'\n");
    fprintf(gnuplot_pipe, "set xlabel 'Date'\n");
    fprintf(gnuplot_pipe, "set ylabel 'Volume'\n");
    fprintf(gnuplot_pipe, "set xdata time\n");
    fprintf(gnuplot_pipe, "set timefmt '\"%%m/%%d/%%Y\"'\n");
    fprintf(gnuplot_pipe, "set format x '%%m/%%d/%%Y'\n");
    fprintf(gnuplot_pipe, "set grid\n");
    fprintf(gnuplot_pipe, "set xtics rotate by -45\n");
    fprintf(gnuplot_pipe, "set style line 1 lc rgb '#0060ad' lw 2 pt 7 ps 1.5\n");

    // Plot command
    fprintf(gnuplot_pipe, "plot '-' using 1:2 with linespoints linestyle 1 title 'Volume Data'\n");

    // Pass data to Gnuplot from NodeArray
    for (size_t i = 0; i < arr->size; i++) {
        fprintf(gnuplot_pipe, "\"%s\" %d\n", arr->nodes[i]->date, arr->nodes[i]->volume);  // Use %d for integer volume
    }

    fprintf(gnuplot_pipe, "e\n");
    pclose(gnuplot_pipe);
}
