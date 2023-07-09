#include <iostream>
using namespace std;

void shellSort(int arr[], int n) {
    // Knuth 提出的增量序列
    int gap = 1;
    while (gap < n / 3) {
        gap = gap * 3 + 1;
    }

    while (gap >= 1) {
        // 使用插入排序对每一个子序列进行排序
        for (int i = gap; i < n; i++) {
            for (int j = i; j >= gap && arr[j] < arr[j - gap]; j -= gap) {
                int temp = arr[j];
                arr[j] = arr[j - gap];
                arr[j - gap] = temp;
            }
        }
        gap = gap / 3;
    }
}

int main() {
    int arr[] = {9, 5, 2, 7, 1, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    shellSort(arr, n);

    cout << "\nSorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}