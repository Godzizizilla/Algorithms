#include <iostream>
#include <vector>
using namespace std;

class HashTable {
private:
    vector<int> table;
    int capacity;
public:
    HashTable(int size) {
        capacity = size;
        table.resize(capacity, -1);
    }

    // 哈希函数
    int hashFunction(int key) {
        return key % capacity;
    }

    // 插入元素
    void insert(int key) {
        int index = hashFunction(key);
        while (table[index] != -1) {
            index = (index + 1) % capacity; // 线性探测解决冲突
        }
        table[index] = key;
    }

    // 查找元素
    bool search(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        while (table[index] != -1) {
            if (table[index] == key) {
                return true;
            }
            index = (index + 1) % capacity; // 线性探测
            if (index == originalIndex) {
                break; // 遍历了整个哈希表，未找到匹配元素
            }
        }
        return false;
    }

    // 删除元素
    void remove(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        while (table[index] != -1) {
            if (table[index] == key) {
                table[index] = -1; // 删除元素
                return;
            }
            index = (index + 1) % capacity; // 线性探测
            if (index == originalIndex) {
                break; // 遍历了整个哈希表，未找到匹配元素
            }
        }
    }

    // 打印哈希表
    void printHashTable() {
        for (int i = 0; i < capacity; i++) {
            cout << "Index " << i << ": ";
            if (table[i] != -1) {
                cout << table[i];
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable hashTable(10);

    hashTable.insert(5);
    hashTable.insert(2);
    hashTable.insert(15);
    hashTable.insert(7);
    hashTable.insert(12);

    hashTable.printHashTable();

    cout << "Search 7: " << (hashTable.search(7) ? "Found" : "Not Found") << endl;
    cout << "Search 10: " << (hashTable.search(10) ? "Found" : "Not Found") << endl;

    hashTable.remove(2);
    hashTable.remove(15);

    hashTable.printHashTable();

    return 0;
}
