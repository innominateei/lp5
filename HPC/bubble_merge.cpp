#include <algorithm>
#include <omp.h>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

void displayArray(const vector<int>& arr) {
    for(int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void merge(vector<int> &arr, int low, int mid, int high){
    vector<int> temp;
    int left = low;
    int right = mid + 1;

    while(left <= mid && right <= high){
        if(arr[left] <= arr[right]){
            temp.push_back(arr[left]);
            left++;
        } else{
            temp.push_back(arr[right]);
            right++;
        }
    }
    while(left <= mid){
        temp.push_back(arr[left]);
        left++;
    }
    while(right <= high){
        temp.push_back(arr[right]);
        right++;
    }
    for(int i = low; i <= high; i++){
        arr[i] = temp[i-low];
    }
}

void mergeSort(vector<int> &arr, int low, int high){
    if(low >= high) return;
    int mid = (low + high)/2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid+1, high);
    merge(arr, low, mid, high);
}
void mergeSort_parallel(vector<int> &arr, int low, int high){
    if(low >= high) return;
    int mid = (low + high)/2;
    #pragma omp parallel sections
    {
        #pragma omp section
        mergeSort(arr, low, mid);
        #pragma omp section
        mergeSort(arr, mid+1, high);
    }
    
    merge(arr, low, mid, high);
}
void bubbleSort(vector<int> &arr, int length){
    for(int i = length - 1; i >= 0; i--){
        for(int j = 0; j <= i - 1; j++){
            if(arr[j] > arr[j+1]) swap(arr[j], arr[j+1]);
        }
    }
}
void bubbleSort_parallel(vector<int> &arr, int length){
    for(int i = 0; i < length; i++){
        int phase = i % 2;
        #pragma omp parallel for shared(arr, phase)
        for(int j = phase; j < length - 1; j += 2){
            if(arr[j] > arr[j + 1]) swap(arr[j], arr[j+1]);
        }
    }
}


int main() {
    const int SIZE = 100;
    vector<int> original(SIZE);
    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        original[i] = rand() % 100;
    }

    // Bubble Sort
    vector<int> bubble = original;
    cout << "\n[Bubble Sort]" << endl;
    cout << "Before: ";
    displayArray(bubble);

    auto start = high_resolution_clock::now();
    bubbleSort(bubble, bubble.size());
    auto end = high_resolution_clock::now();

    cout << "After: ";
    displayArray(bubble);
    cout << "Time: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // Parallel Bubble Sort
    vector<int> bubble_parallel = original;
    cout << "\n[Parallel Bubble Sort]" << endl;
    cout << "Before: ";
    displayArray(bubble_parallel);

    start = high_resolution_clock::now();
    bubbleSort_parallel(bubble_parallel, bubble_parallel.size());
    end = high_resolution_clock::now();

    cout << "After: ";
    displayArray(bubble_parallel);
    cout << "Time: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // Merge Sort
    vector<int> merge = original;
    cout << "\n[Merge Sort]" << endl;
    cout << "Before: ";
    displayArray(merge);

    start = high_resolution_clock::now();
    mergeSort(merge, 0, merge.size() - 1);
    end = high_resolution_clock::now();

    cout << "After: ";
    displayArray(merge);
    cout << "Time: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // Parallel Merge Sort
    vector<int> merge_parallel = original;
    cout << "\n[Parallel Merge Sort]" << endl;
    cout << "Before: ";
    displayArray(merge_parallel);

    start = high_resolution_clock::now();
    mergeSort_parallel(merge_parallel, 0, merge_parallel.size() - 1);
    end = high_resolution_clock::now();

    cout << "After: ";
    displayArray(merge_parallel);
    cout << "Time: " << duration_cast<microseconds>(end - start).count() << " us\n";

    return 0;
}
