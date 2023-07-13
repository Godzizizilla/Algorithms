#include <iostream>

using namespace std;

struct TreeNode {
    int key;
    int height;
    TreeNode *left;
    TreeNode *right;
};

// 获取节点高度
int getHeight(TreeNode *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// 更新节点的高度
void updateHeight(TreeNode *node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    node->height = max(leftHeight, rightHeight) + 1;
}

// 计算节点的平衡因子
int getBalanceFactor(TreeNode *node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// 创建新节点
TreeNode *createNode(int key) {
    TreeNode *newNode = new TreeNode();
    newNode->key = key;
    newNode->height = 1;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

/*
 * in: 需要进行左旋的节点(根节点)
 * out: 左旋后的根节点
 * */

// 左旋操作
TreeNode *leftRotate(TreeNode *node) {
    TreeNode *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// 右旋操作
TreeNode *rightRotate(TreeNode *node) {
    TreeNode *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

/*
 * 1. 不管平不平衡, 先将节点插入正确的位置(向下递归)
 * 2. 再调整以保持平衡(向上递归)
 *
 * in:
 * out: 因为需要递归地找叶子结点插入, 因此最后一次递归返回的是新建节点的指针, 而其他情况则root本身即可
 */

// 插入节点
TreeNode *insertNode(TreeNode *root, int key) {
    if (root == nullptr) {
        return createNode(key);
    }

    // 递归地找到叶子节点插入
    if (key < root->key) {
        root->left = insertNode(root->left, key);
    } else if (key > root->key) {
        root->right = insertNode(root->right, key);
    } else {
        return root; // 不允许插入相同的键值
    }

    // 更新节点高度
    updateHeight(root);

    // 计算平衡因子
    int balanceFactor = getBalanceFactor(root);

    // 判断是否失衡

    //  左子树的高度大于右子树的高度，不平衡发生在左子树
    if (balanceFactor > 1) {
        if (key < root->left->key) {
            // 左-左情况, 进行右旋操作
            return rightRotate(root);
        } else if (key > root->left->key) {
            // 左-右情况，先对左子树进行左旋操作，再对根节点进行右旋操作
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
        // 右子树的高度大于左子树的高度，不平衡发生在右子树
    else if (balanceFactor < -1) {
        if (key > root->right->key) {
            // 右-右情况, 进行左旋操作
            return leftRotate(root);
        } else if (key < root->right->key) {
            // 右-左情况，先对右子树进行右旋操作，再对根节点进行左旋操作
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

// 找到最小键值节点
TreeNode *findMinNode(TreeNode *root) {
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

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // 找到待删除的节点

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
        root->right = deleteNode(root->right, minNode->key); // 递归地删除右子树中的最小节点
    }

    updateHeight(root);

    int balanceFactor = getBalanceFactor(root);

    // 左子树的高度大于右子树的高度，不平衡发生在左子树
    if (balanceFactor > 1) {
        int leftBalanceFactor = getBalanceFactor(root->left);
        if (leftBalanceFactor >= 0) {
            // 左-左情况，进行右旋操作
            return rightRotate(root);
        } else if (leftBalanceFactor < 0) {
            // 左-右情况，先对左子树进行左旋操作，再对根节点进行右旋操作
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
        // 右子树的高度大于左子树的高度，不平衡发生在右子树
    else if (balanceFactor < -1) {
        int rightBalanceFactor = getBalanceFactor(root->right);
        if (rightBalanceFactor <= 0) {
            // 右-右情况，进行左旋操作
            return leftRotate(root);
        } else if (rightBalanceFactor > 0) {
            // 右-左情况，先对右子树进行右旋操作，再对根节点进行左旋操作
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

// 中序遍历打印二叉树
void inorderTraversal(TreeNode* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << "Key: " << root->key << endl;
        inorderTraversal(root->right);
    }
}

int main() {
    TreeNode* root = nullptr;

    // 插入节点
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);

    // 删除节点
    root = deleteNode(root, 30);

    // 打印二叉树
    inorderTraversal(root);

    return 0;
}