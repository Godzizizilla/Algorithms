#include <iostream>

using namespace std;

int binarySearchIterative(const int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;  // 计算中间元素的索引

        if (arr[mid] == target) {
            return mid;  // 找到目标元素，返回索引
        } else if (arr[mid] < target) {
            left = mid + 1;  // 目标元素在右半部分，更新左边界
        } else {
            right = mid - 1;  // 目标元素在左半部分，更新右边界
        }
    }

    return -1;  // 未找到目标元素，返回-1
}

int binarySearchRecursive(int arr[], int left, int right, int target) {
    if (left <= right) {
        int mid = left + (right - left) / 2;  // 计算中间元素的索引

        if (arr[mid] == target) {
            return mid;  // 找到目标元素，返回索引
        } else if (arr[mid] < target) {
            return binarySearchRecursive(arr, mid + 1, right, target);  // 在右半部分递归查找
        } else {
            return binarySearchRecursive(arr, left, mid - 1, target);  // 在左半部分递归查找
        }
    }

    return -1;  // 未找到目标元素，返回-1
}

int main() {
    int arr[] = {2, 5, 7, 9, 13, 17, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 9;

    int index = binarySearchIterative(arr, 0, n - 1, target);

    if (index != -1) {
        cout << "Element found at index " << index << endl;
    } else {
        cout << "Element not found" << endl;
    }

    return 0;
}

