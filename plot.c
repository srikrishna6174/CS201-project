#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plot.h"

void plotPrices(char date[][11], float* prices, size_t size) {
    // Use "gnuplot" command on Windows
    FILE *gnuplot_pipe = popen("gnuplot -persistent", "w");
    if (!gnuplot_pipe) {
        perror("Could not open gnuplot");
        exit(EXIT_FAILURE);
    }

    // Gnuplot configuration
    fprintf(gnuplot_pipe, "set terminal wxt size 1000, 400\n");
    fprintf(gnuplot_pipe, "set title 'Stock Prices Over Time'\n");
    fprintf(gnuplot_pipe, "set title 'Price Data'\n");
    fprintf(gnuplot_pipe, "set xlabel 'Date'\n");
    fprintf(gnuplot_pipe, "set ylabel 'Price'\n");
    fprintf(gnuplot_pipe, "set xdata time\n");
    fprintf(gnuplot_pipe, "set timefmt '\"%%m/%%d/%%Y\"'\n");
    fprintf(gnuplot_pipe, "set format x '%%m/%%d/%%Y'\n");
    fprintf(gnuplot_pipe, "set datafile separator whitespace\n");
    fprintf(gnuplot_pipe, "set grid\n");
    fprintf(gnuplot_pipe, "set xtics rotate by -45\n");
    fprintf(gnuplot_pipe, "set style line 1 lc rgb '#0060ad' lw 2 pt 7 ps 1.5\n");

    // Plot command
    fprintf(gnuplot_pipe, "plot '-' using 1:2 with linespoints linestyle 1 title 'Price Data'\n");

    // Pass data to Gnuplot
    for (size_t i = 0; i < size; i++) {
        fprintf(gnuplot_pipe, "\"%s\" %f\n", date[i], prices[i]);
    }

    fprintf(gnuplot_pipe, "e\n");
    pclose(gnuplot_pipe);
}
