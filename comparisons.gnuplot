set terminal png size 900,600
set output 'comparisons.png'
set title 'Quick Sort: Input Size vs Number of Comparisons'
set xlabel 'Input Size'
set ylabel 'Number of Comparisons'
set grid
plot 'quicksort_data.dat' using 1:5 with linespoints title 'First Pivot', 'quicksort_data.dat' using 1:6 with linespoints title 'Middle Pivot', 'quicksort_data.dat' using 1:7 with linespoints title 'Last Pivot'
