#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortParallel(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
#pragma omp parallel sections
        {
#pragma omp section
            quickSortParallel(arr, low, pi - 1);
#pragma omp section
            quickSortParallel(arr, pi + 1, high);
        }
    }
}

int main() {
    const int size = 100000;
    vector<int> arr(size);

    srand(time(0));
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 10000;
    }

    auto start = high_resolution_clock::now();
    quickSortParallel(arr, 0, arr.size() - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by parallel QuickSort for an array of size " << size << ": "
         << duration.count() << " microseconds" << endl;

    return 0;
}