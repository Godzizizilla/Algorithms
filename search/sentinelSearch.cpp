#include <iostream>
using namespace std;

int sentinelSearch(int arr[], int n, int target) {
    int last = arr[n - 1];  // 保存最后一个元素
    arr[n - 1] = target;  // 将目标元素设置为哨兵

    int i = 0;
    while (arr[i] != target) {
        i++;
    }

    arr[n - 1] = last;  // 还原数组最后一个元素

    if (i < n - 1 || arr[n - 1] == target) {
        return i;  // 找到目标元素，返回索引
    }

    return -1;  // 未找到目标元素，返回-1
}

int main() {
    int arr[] = {5, 8, 2, 13, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 13;

    int index = sentinelSearch(arr, n, target);

    if (index != -1) {
        cout << "Element found at index " << index << endl;
    } else {
        cout << "Element not found" << endl;
    }

    return 0;
}
