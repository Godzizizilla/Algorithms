#include <iostream>
using namespace std;

void merge(int arr[], int lo, int mid, int hi) {
    int i = lo;
    int j = mid + 1;

    int aux[hi - lo + 1];
    for (int k = lo; k <= hi; k++) {
        aux[k] = arr[k];
    }

    for (int k = lo; k <= hi; k++) {
        if (i > mid) {
            arr[k] = aux[j++];
        } else if (j > hi) {
            arr[k] = aux[i++];
        } else if (aux[i] < aux[j]) {
            arr[k] = aux[i++];
        } else {
            arr[k] = aux[j++];
        }
    }
}

void mergeSort(int arr[], int lo, int hi) {
    if (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        mergeSort(arr, lo, mid);
        mergeSort(arr, mid + 1, hi);

        merge(arr, lo, mid, hi);
    }
}

void buMergeSort(int arr[], int n) {
    int subarraySize = 1;  // 子数组的大小

    while (subarraySize < n) {
        int lo = 0;
        while (lo < n - 1) {
            int mid = lo + subarraySize - 1;
            int hi = min(mid * 2 + 1, n - 1);
            merge(arr, lo, mid, hi);

            lo += subarraySize * 2;
        }
        subarraySize *= 2;
    }
}

int main() {
    int arr[] = {9, 5, 2, 7, 1, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "----mergeSort----\n";
    cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    mergeSort(arr, 0, n - 1);

    cout << "\nSorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    int arr2[] = {9, 5, 2, 7, 1, 8};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    cout << "\n----buMergeSort----\n";
    cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    buMergeSort(arr2,n2);

    cout << "\nSorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}