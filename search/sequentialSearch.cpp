#include <iostream>
using namespace std;

int sequentialSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;  // 找到目标元素，返回索引
        }
    }
    return -1;  // 未找到目标元素，返回-1
}

int main() {
    int arr[] = {5, 8, 2, 13, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 13;

    int index = sequentialSearch(arr, n, target);

    if (index != -1) {
        cout << "Element found at index " << index << endl;
    } else {
        cout << "Element not found" << endl;
    }

    return 0;
}
