// Merge Sort Vs Insertion Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

static void insertionSort(vector<int>& arr, int right, int left = 0)
{
    for (int i = left + 1; i < right; ++i) {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

static void merge(vector<int>& arr, int left,
    int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back 
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], 
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], 
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
static void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

static void timSort(vector<int>& arr, int left, int right, int k)
{
    if (left >= right)
        return;
    
    if ((right - left) <= k) {
        insertionSort(arr, right + 1, left);
        return;
    }

    int mid = left + (right - left) / 2;
    timSort(arr, left, mid, k);
    timSort(arr, mid + 1, right, k);
    merge(arr, left, mid, right);
}

int main()
{
    vector<int> test;
    vector<int> starting_test;

    int n = 100000;
    int x;
    int k = 100000;

    for (int i = 0; i < n; i++) {
        x = rand();
        test.push_back(x);
    }

    starting_test = test;
    
    clock_t merge_start_time = clock();
    for (int i = 0; i < 100; i++) {
        test = starting_test;
        mergeSort(test, 0, n - 1);
    }
    clock_t merge_tot_time = clock() - merge_start_time;
    cout << "Merge Time: " << ((double)merge_tot_time) / (double)CLOCKS_PER_SEC << " seconds" << endl;

    test = starting_test;

    clock_t insertion_start_time = clock();
    for (int i = 0; i < 100; i++) {
        test = starting_test;
        insertionSort(test, n);
    }
    clock_t insertion_tot_time = clock() - insertion_start_time;
    cout << "Insertion Time: " << ((double)insertion_tot_time) / (double)CLOCKS_PER_SEC << " seconds" << endl;
    
    test = starting_test;

    clock_t tim_start_time = clock();
    for (int i = 0; i < 100; i++) {
        test = starting_test;
        timSort(test, 0, n - 1, k);
    }
    clock_t tim_tot_time = clock() - tim_start_time;
    cout << "Tim Time: " << ((double)tim_tot_time) / (double)CLOCKS_PER_SEC << " seconds" << endl;

}
