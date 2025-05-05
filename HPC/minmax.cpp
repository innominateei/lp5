// g++ -fopenmp example.cpp -o example
// ./example

#include <iostream>
#include <omp.h>
#include <climits>

using namespace std;

// Function to find the minimum value in an array using OpenMP reduction
void min_reduction(int arr[], int n) {
    int min_value = INT_MAX; // Initialize min_value to the maximum possible integer value

    // OpenMP parallel for loop with reduction clause (min)
    #pragma omp parallel for reduction(min: min_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i]; // Update min_value if the current element is smaller
        }
    }

    cout << "Minimum value: " << min_value << endl; // Output the minimum value
}

// Function to find the maximum value in an array using OpenMP reduction
void max_reduction(int arr[], int n) {
    int max_value = INT_MIN; // Initialize max_value to the minimum possible integer value

    // OpenMP parallel for loop with reduction clause (max)
    #pragma omp parallel for reduction(max: max_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_value) {
          max_value = arr[i]; // Update max_value if the current element is larger
        }
    }

    cout << "Maximum value: " << max_value << endl; // Output the maximum value
}

// Function to find the sum of all elements in an array using OpenMP reduction
void sum_reduction(int arr[], int n) {
    int sum = 0; // Initialize sum to zero

    // OpenMP parallel for loop with reduction clause (sum)
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i]; // Add each element to sum
    }

    cout << "Sum: " << sum << endl; // Output the sum
}

// Function to find the average of all elements in an array using OpenMP reduction
void average_reduction(int arr[], int n) {
    int sum = 0; // Initialize sum to zero

    // OpenMP parallel for loop with reduction clause (sum)
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
      sum += arr[i]; // Add each element to sum
    }

    cout << "Average: " << (double)sum / n << endl; // Output the average (casting sum to double for accurate division)
}

int main() {
    int *arr, n;
    cout << "\nEnter the total number of elements: ";
    cin >> n;

    arr = new int[n]; // Dynamically allocate memory for the array
    cout << "\nEnter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i]; // Input the elements of the array
    }

    min_reduction(arr, n); // Find the minimum value in the array
    max_reduction(arr, n); // Find the maximum value in the array
    sum_reduction(arr, n); // Find the sum of all elements in the array
    average_reduction(arr, n); // Find the average of all elements in the array

    delete[] arr; // Deallocate memory for the array
    return 0;
}