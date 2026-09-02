set terminal png size 900,600
set output 'execution_time.png'
set title 'Quick Sort: Input Size vs Execution Time'
set xlabel 'Input Size'
set ylabel 'Execution Time (microseconds)'
set grid
plot 'quicksort_data.dat' using 1:2 with linespoints title 'First Pivot', 'quicksort_data.dat' using 1:3 with linespoints title 'Middle Pivot', 'quicksort_data.dat' using 1:4 with linespoints title 'Last Pivot'
