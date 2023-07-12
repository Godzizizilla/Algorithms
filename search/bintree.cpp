#include <iostream>
using namespace std;

struct TreeNode {
    int key;
    int value;
    TreeNode* left;
    TreeNode* right;
};

// 创建新节点
TreeNode* createNode(int key, int value) {
    TreeNode* newNode = new TreeNode();
    newNode->key = key;
    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// 插入节点
TreeNode* insertNode(TreeNode* root, int key, int value) {
    // 如果根节点为空，创建新节点作为根节点
    if (root == nullptr) {
        return createNode(key, value);
    }

    // 如果待插入的键值小于根节点的键值，递归地插入到左子树
    if (key < root->key) {
        root->left = insertNode(root->left, key, value);
    }
    // 如果待插入的键值大于等于根节点的键值，递归地插入到右子树
    else {
        root->right = insertNode(root->right, key, value);
    }

    return root;
}

// 查找节点
TreeNode* searchNode(TreeNode* root, int key) {
    // 如果根节点为空或者根节点的键值等于目标键值，返回根节点
    if (root == nullptr || root->key == key) {
        return root;
    }

    // 如果目标键值小于根节点的键值，递归地查找左子树
    if (key < root->key) {
        return searchNode(root->left, key);
    }
        // 如果目标键值大于根节点的键值，递归地查找右子树
    else {
        return searchNode(root->right, key);
    }
}

// 找到最小键值节点
TreeNode* findMinNode(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// 删除节点
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) {
        return root;
    }

    // 如果待删除的键值小于根节点的键值，递归地删除左子树中的节点
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    // 如果待删除的键值大于根节点的键值，递归地删除右子树中的节点
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    // 找到待删除的节点
    else {
        // 情况1：待删除的节点没有子节点或只有一个子节点
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // 情况2：待删除的节点有两个子节点
        TreeNode* minNode = findMinNode(root->right); // 找到右子树中的最小节点
        root->key = minNode->key; // 用最小节点的键值替换待删除节点的键值
        root->value = minNode->value; // 用最小节点的值替换待删除节点的值
        root->right = deleteNode(root->right, minNode->key); // 递归地删除右子树中的最小节点
    }

    return root;
}

// 中序遍历打印二叉查找树
void inorderTraversal(TreeNode* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << "Key: " << root->key << ", Value: " << root->value << endl;
        inorderTraversal(root->right);
    }
}

int main() {
    TreeNode* root = nullptr;

    // 插入节点
    root = insertNode(root, 10, 100);
    root = insertNode(root, 5, 50);
    root = insertNode(root, 15, 150);
    root = insertNode(root, 3, 30);
    root = insertNode(root, 7, 70);
    root = insertNode(root, 12, 120);
    root = insertNode(root, 17, 170);

    // 查找节点
    TreeNode* node = searchNode(root, 7);
    if (node != nullptr) {
        cout << "Node found: Key: " << node->key << ", Value: " << node->value << endl;
    } else {
        cout << "Node not found." << endl;
    }

    // 删除节点
    root = deleteNode(root, 15);

    // 打印二叉查找树
    inorderTraversal(root);

    return 0;
}
