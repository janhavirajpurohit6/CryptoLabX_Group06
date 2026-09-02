#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

long long comparisons = 0;
long long swaps = 0;
long long calls = 0;



int partitionFirst(vector<int>& a, int low, int high)
{
    int pivot = a[low];
    int i = low + 1;
    int j = high;

    while (i <= j)
    {
        while (i <= high && a[i] <= pivot)
        {
            comparisons++;
            i++;
        }

        while (j >= low && a[j] > pivot)
        {
            comparisons++;
            j--;
        }

        if (i < j)
        {
            swap(a[i], a[j]);
            swaps++;
        }
    }

    swap(a[low], a[j]);
    swaps++;

    return j;
}

void quickSortFirst(vector<int>& a, int low, int high)
{
    calls++;

    if (low < high)
    {
        int p = partitionFirst(a, low, high);

        quickSortFirst(a, low, p - 1);
        quickSortFirst(a, p + 1, high);
    }
}



int partitionMiddle(vector<int>& a, int low, int high)
{
    int mid = (low + high) / 2;
    int pivot = a[mid];

    swap(a[mid], a[high]);
    swaps++;

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        comparisons++;

        if (a[j] < pivot)
        {
            i++;
            swap(a[i], a[j]);
            swaps++;
        }
    }

    swap(a[i + 1], a[high]);
    swaps++;

    return i + 1;
}

void quickSortMiddle(vector<int>& a, int low, int high)
{
    calls++;

    if (low < high)
    {
        int p = partitionMiddle(a, low, high);

        quickSortMiddle(a, low, p - 1);
        quickSortMiddle(a, p + 1, high);
    }
}




int partitionLast(vector<int>& a, int low, int high)
{
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        comparisons++;

        if (a[j] < pivot)
        {
            i++;
            swap(a[i], a[j]);
            swaps++;
        }
    }

    swap(a[i + 1], a[high]);
    swaps++;

    return i + 1;
}

void quickSortLast(vector<int>& a, int low, int high)
{
    calls++;

    if (low < high)
    {
        int p = partitionLast(a, low, high);

        quickSortLast(a, low, p - 1);
        quickSortLast(a, p + 1, high);
    }
}




int main()
{
    ofstream file("quicksort_data.dat");

    file << "# InputSize FirstTime MiddleTime LastTime "
         << "FirstComparisons MiddleComparisons LastComparisons\n";

    cout << "QUICK SORT PERFORMANCE ANALYSIS\n";
    cout << "========================================\n\n";

    for (int n = 100; n <= 1000; n += 100)
    {
        // Create same random array for all three methods
        vector<int> original(n);

        srand(n);

        for (int i = 0; i < n; i++)
        {
            original[i] = rand() % 10000;
        }


     

        vector<int> a = original;

        comparisons = 0;
        swaps = 0;
        calls = 0;

        clock_t start1 = clock();

        quickSortFirst(a, 0, n - 1);

        clock_t end1 = clock();

        double time1 =
            double(end1 - start1) / CLOCKS_PER_SEC * 1000000;

        long long comparisons1 = comparisons;



        a = original;

        comparisons = 0;
        swaps = 0;
        calls = 0;

        clock_t start2 = clock();

        quickSortMiddle(a, 0, n - 1);

        clock_t end2 = clock();

        double time2 =
            double(end2 - start2) / CLOCKS_PER_SEC * 1000000;

        long long comparisons2 = comparisons;


    

        a = original;

        comparisons = 0;
        swaps = 0;
        calls = 0;

        clock_t start3 = clock();

        quickSortLast(a, 0, n - 1);

        clock_t end3 = clock();

        double time3 =
            double(end3 - start3) / CLOCKS_PER_SEC * 1000000;

        long long comparisons3 = comparisons;


        // ---------------- DISPLAY RESULTS ----------------

        cout << "Input Size: " << n << endl;

        cout << "First Pivot  -> Time: "
             << time1
             << " us, Comparisons: "
             << comparisons1 << endl;

        cout << "Middle Pivot -> Time: "
             << time2
             << " us, Comparisons: "
             << comparisons2 << endl;

        cout << "Last Pivot   -> Time: "
             << time3
             << " us, Comparisons: "
             << comparisons3 << endl;

        cout << "----------------------------------------\n";


        // Save data for graph
        file << n << " "
             << time1 << " "
             << time2 << " "
             << time3 << " "
             << comparisons1 << " "
             << comparisons2 << " "
             << comparisons3 << endl;
    }

    file.close();


    // ==================================================
    // CREATE GRAPH 1: EXECUTION TIME
    // ==================================================

    ofstream graph1("execution_time.gnuplot");

    graph1 << "set terminal png size 900,600\n";
    graph1 << "set output 'execution_time.png'\n";

    graph1 << "set title 'Quick Sort: Input Size vs Execution Time'\n";
    graph1 << "set xlabel 'Input Size'\n";
    graph1 << "set ylabel 'Execution Time (microseconds)'\n";
    graph1 << "set grid\n";

    graph1 << "plot "
           << "'quicksort_data.dat' using 1:2 "
           << "with linespoints title 'First Pivot', "
           << "'quicksort_data.dat' using 1:3 "
           << "with linespoints title 'Middle Pivot', "
           << "'quicksort_data.dat' using 1:4 "
           << "with linespoints title 'Last Pivot'\n";

    graph1.close();


    // ==================================================
    // CREATE GRAPH 2: NUMBER OF COMPARISONS
    // ==================================================

    ofstream graph2("comparisons.gnuplot");

    graph2 << "set terminal png size 900,600\n";
    graph2 << "set output 'comparisons.png'\n";

    graph2 << "set title 'Quick Sort: Input Size vs Number of Comparisons'\n";
    graph2 << "set xlabel 'Input Size'\n";
    graph2 << "set ylabel 'Number of Comparisons'\n";
    graph2 << "set grid\n";

    graph2 << "plot "
           << "'quicksort_data.dat' using 1:5 "
           << "with linespoints title 'First Pivot', "
           << "'quicksort_data.dat' using 1:6 "
           << "with linespoints title 'Middle Pivot', "
           << "'quicksort_data.dat' using 1:7 "
           << "with linespoints title 'Last Pivot'\n";

    graph2.close();


    

    system("gnuplot execution_time.gnuplot");
    system("gnuplot comparisons.gnuplot");


    cout << "\n========================================\n";
    cout << "Graphs generated successfully!\n";
    cout << "1. execution_time.png\n";
    cout << "2. comparisons.png\n";
    cout << "========================================\n";

    return 0;
}