#include <iostream>

using namespace std;

void buMaxHeapify(int arr[], int n, int i) {
    // 自下而上 (下滤)
    // 该父结点是否比两个子结点都小 -> 是: 跟最大的子结点交换
    // 交换之后它还有子结点, 递归地调用
    int largest = i; // 最大元素的结点索引
    int left = 2 * i + 1; // 左子结点索引
    int right = 2 * i + 2; // 右子结点索引

    // 比较父结点与左子结点的值 (先判断是否有左子结点-防止数组下标越界和结束递归)
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // 比较当前最大结点与右子结点的值 (先判断是否有右子结点-防止数组下标越界和结束递归)
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // 此时, largest就是最大值结点的索引(可能是父结点, 左子结点, 右子结点)
    // 如果不是父结点最大, 那么交换位置, 并递归地调用
    if (largest != i) {
        swap(arr[i], arr[largest]);
        buMaxHeapify(arr, n, largest);
    }
}

void buMinHeapify(int arr[], int n, int i) {
    // 自下而上 (下滤)
    // 该父结点是否比两个子结点都大 -> 是: 跟最小的子结点交换
    // 交换之后它还有子结点, 递归地调用
    int minimum = i; // 最小元素的结点索引
    int left = 2 * i + 1; // 左子结点索引
    int right = 2 * i + 2; // 右子结点索引

    // 比较父结点与左子结点的值 (先判断是否有左子结点-防止数组下标越界和结束递归)
    if (left < n && arr[left] < arr[minimum]) {
        minimum = left;
    }

    // 比较当前最小结点与右子结点的值 (先判断是否有右子结点-防止数组下标越界和结束递归)
    if (right < n && arr[right] < arr[minimum]) {
        minimum = right;
    }

    // 此时, minimum就是最小值结点的索引(可能是父结点, 左子结点, 右子结点)
    // 如果不是父结点最小, 那么交换位置, 并递归地调用
    if (minimum != i) {
        swap(arr[i], arr[minimum]);
        buMinHeapify(arr, n, minimum);
    }
}

void tdMaxHeapify(int arr[], int n, int i) {
    // 自顶向下 (上滤)
    int parent = (i - 1) / 2;

    // 该结点是否比父结点大 -> 是: 交换, 并 *递归* 地执行
    /*if (parent >= 0 && arr[i] > arr[parent]) {
        swap(arr[i], arr[parent]);
        tdMaxHeapify(arr, n, parent);
    }*/

    // 该结点是否比父结点大 -> 是: 交换, 并 *迭代* 地执行
    while (parent >= 0 && arr[i] > arr[parent]) {
        swap(arr[i], arr[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void tdMinHeapify(int arr[], int i) {
    // 自顶向下 (上滤)
    int parent = (i - 1) / 2;

    // 该结点是否比父结点小 -> 是: 交换, 并 *递归* 地执行
    /*if (parent >= 0 && arr[i] < arr[parent]) {
        swap(arr[i], arr[parent]);
        tdMinHeapify(arr, parent);
    }*/

    // 该结点是否比父结点小 -> 是: 交换, 并 *迭代* 地执行
    while (parent >= 0 && arr[i] < arr[parent]) {
        swap(arr[i], arr[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void buildHeap(int arr[], int n) {
    // 自底向上: 从最后一个非叶子节点开始进行堆化
    /*for (int i = n / 2 - 1; i >= 0; i--) {
        buMinHeapify(arr, n, i);
    }*/

    // 自顶向下: 从第二个父结点开始进行堆化
    for (int i = 1; i < n; i++) {
        tdMaxHeapify(arr, n, i);
    }
}

void deleteMax(int arr[], int &n) {
    if (n <= 0) {
        return; // 堆为空, 无法删除
    }

    swap(arr[0], arr[n - 1]); // 将堆顶元素与最后一个元素交换位置
    n--; // 堆长度减1
    buMaxHeapify(arr, n, 0); // 对新的堆顶元素进行下滤操作
}

void insert(int arr[], int &n, int key) {
    if (n <= 0) {
        arr[0] = key;
        n++;
        return;
    }

    int i = n++;
    arr[i] = key;

    tdMaxHeapify(arr, n, i);
}

void heapSort(int arr[], int n) {
    buildHeap(arr, n);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        buMaxHeapify(arr, i, 0);
    }
}

/*int main() {
    int arr[] = {1, 5, 2, 7, 9, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    buildHeap(arr, n);

    cout << "\nHeapified array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}*/

/*int main() {
    int arr[] = {9, 5, 2, 7, 1, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    buildHeap(arr, n);

    cout << "Original heap: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    deleteMax(arr, n);

    cout << "\nHeap after deleting max element: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    insert(arr, n, 10);

    cout << "\nHeap after inserting element: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}*/

int main() {
    int arr[] = {9, 5, 2, 7, 1, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    heapSort(arr, n);

    cout << "\nSorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}