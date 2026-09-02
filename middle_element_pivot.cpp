#include <iostream>
using namespace std;

int comparisons = 0;
int swaps = 0;
int calls = 0;

int partitionMiddle(int a[], int low, int high)
{
    int mid = (low + high) / 2;

    int pivot = a[mid];

    swap(a[mid], a[high]);
    swaps++;

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        comparisons++; // Count comparison

        if (a[j] < pivot)
        {
            i++;

            swap(a[i], a[j]); // Swap
            swaps++;
        }
    }

    swap(a[i + 1], a[high]); // Put pivot correctly
    swaps++;

    return i + 1;
}

void quickSortMiddle(int a[], int low, int high)
{
    calls++; // Count recursive call

    if (low < high)
    {
        int p = partitionMiddle(a, low, high);

        quickSortMiddle(a, low, p - 1);  // Sort left
        quickSortMiddle(a, p + 1, high); // Sort right
    }
}

int main()
{
    int a[100] = {52, 10, 36, 60, 31, 68, 92, 34, 34, 50, 85, 21, 89, 27, 15, 65, 34, 85, 61, 7, 38, 82, 34, 2, 30, 5, 91, 14, 8, 23, 96, 41, 35, 87, 95, 50, 81, 23, 46, 4, 26, 98, 85, 35, 25, 36, 55, 35, 77, 41, 51, 91, 88, 45, 50, 38, 63, 39, 88, 54, 18, 57, 84, 90, 97, 32, 69, 53, 6, 82, 46, 13, 2, 32, 81, 56, 54, 59, 4, 42, 22, 59, 50, 53, 68, 6, 10, 78, 97, 12, 22, 14, 93, 9, 75, 25, 57, 69, 69, 39}; // RANDOM ARRAY

    int b[100] = {2, 2, 4, 4, 5, 6, 6, 7, 8, 9, 10, 10, 12, 13, 14, 14, 15, 18, 21, 22, 22, 23, 23, 25, 25, 26, 27, 30, 31, 32, 32, 34, 34, 34, 34, 35, 35, 35, 36, 36, 38, 38, 39, 39, 41, 41, 42, 45, 46, 46, 50, 50, 50, 50, 51, 52, 53, 53, 54, 54, 55, 56, 57, 57, 59, 59, 60, 61, 63, 65, 68, 68, 69, 69, 69, 75, 77, 78, 81, 81, 82, 82, 84, 85, 85, 85, 87, 88, 88, 89, 90, 91, 91, 92, 93, 95, 96, 97, 97, 98}; // SORTED ARRAY

    int c[100] = {98, 97, 97, 96, 95, 93, 92, 91, 91, 90, 89, 88, 88, 87, 85, 85, 85, 84, 82, 82, 81, 81, 78, 77, 75, 69, 69, 69, 68, 68, 65, 63, 61, 60, 59, 59, 57, 57, 56, 55, 54, 54, 53, 53, 52, 51, 50, 50, 50, 50, 46, 46, 45, 42, 41, 41, 39, 39, 38, 38, 36, 36, 35, 35, 35, 34, 34, 34, 34, 32, 32, 31, 30, 27, 26, 25, 25, 23, 23, 22, 22, 21, 18, 15, 14, 14, 13, 12, 10, 10, 9, 8, 7, 6, 6, 5, 4, 4, 2, 2}; // REVERSE-SORTED ARRAY

    int n = 100;

    comparisons = 0;
    swaps = 0;
    calls = 0;

    clock_t start1 = clock();
    quickSortMiddle(a, 0, n - 1);
    clock_t end1 = clock();
    double time1 = double(end1 - start1) / CLOCKS_PER_SEC * 1000000;

    cout << "MIDDLE PIVOT for RANDOM ARRAY" << endl;
    cout << "Comparisons = " << comparisons << endl;
    cout << "Swaps = " << swaps << endl;
    cout << "Calls = " << calls << endl;
    cout << "Time= " << time << " microseconds" << endl;
    cout << " " << endl;

    clock_t start2 = clock();
    quickSortMiddle(b, 0, n - 1);
    clock_t end2 = clock();
    double time2 = double(end2 - start2) / CLOCKS_PER_SEC * 1000000;

    cout << "MIDDLE PIVOT for SORTED ARRAY" << endl;
    cout << "Comparisons = " << comparisons << endl;
    cout << "Swaps = " << swaps << endl;
    cout << "Calls = " << calls << endl;
    cout << "Time = " << time << " microsenconds" << endl;
    cout << " " << endl;

    clock_t start3 = clock();
    quickSortMiddle(c, 0, n - 1);
    clock_t end3 = clock();
    double time3 = double(end3 - start3) / CLOCKS_PER_SEC * 1000000;

    cout << "MIDDLE PIVOT for REVERSE-SORTED ARRAY" << endl;
    cout << "Comparisons = " << comparisons << endl;
    cout << "Swaps = " << swaps << endl;
    cout << "Calls = " << calls << endl;
    cout << "Time = " << time << " microsenconds" << endl;
    return 0;
}
