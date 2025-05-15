#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <iomanip>
#include "DynamicArray.h"

using namespace std;

template<typename T>
class AVLTree {
private:
    struct AVLNode {
        T val;
        AVLNode* left;
        AVLNode* right;
        AVLNode* parent;
        int height;
        AVLNode() : left(nullptr), right(nullptr), parent(nullptr),height(1) {}
    };
    AVLNode* root;
    int nodesCount;

    int getHeight(AVLNode* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    void updateHeight(AVLNode* node) {
        if (node != nullptr) {
            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        }
    }

    void deleteTree(AVLNode* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
    void fillMatrix(AVLNode* node, DynamicArray<DynamicArray<string>>& matrix, int row, int col, int offset, int nodeWidth) {
        if (!node) return;

        string nodeVal = to_string(node->val.getFirst());

        // Center the value in the allocated space
        int padding = nodeWidth - nodeVal.length();
        int leftPad = padding / 2;

        // Place the node value centered in its allocated space
        for (int i = 0; i < nodeVal.length(); i++) {
            matrix[row][col - leftPad + i] = string(1, nodeVal[i]);
        }

        int gap = max(offset / 2, max(nodeWidth,2));

        if (node->left) {
            // Position the slash better
            matrix[row + 1][col - max(gap / 2, 1)] = "/";
            fillMatrix(node->left, matrix, row + 2, col - gap, offset/2, nodeWidth);
        }

        if (node->right) {
            // Position the backslash better
            matrix[row + 1][col + max(gap / 2, 1)] = "\\";
            fillMatrix(node->right, matrix, row + 2, col + gap, offset/2, nodeWidth);
        }
    }
    // Helper function to find the maximum width of any node value
    int findMaxNodeWidth(AVLNode* node) {
        if (!node) return 0;

        int thisWidth = to_string(node->val.getFirst()).length();
        int leftWidth = findMaxNodeWidth(node->left);
        int rightWidth = findMaxNodeWidth(node->right);

        return max(thisWidth, max(leftWidth, rightWidth));
    }
public:
    AVLTree() : root(nullptr), nodesCount(0) {}

    AVLNode* leftRotation(AVLNode* node) {
        AVLNode* tmp = node->right;
        AVLNode* tmp2 = tmp->left;
        tmp->left = node;
        node->right = tmp2;
        tmp->parent = node->parent;
        node->parent = tmp;
        if (tmp2 != nullptr) {
            tmp2->parent = node;
        }
        if (tmp->parent != nullptr) {
            if (tmp->parent->left == node) {
                tmp->parent->left = tmp;
            } else {
                tmp->parent->right = tmp;
            }
        } else {
            root = tmp;
        }
        updateHeight(node);
        updateHeight(tmp);
        return tmp;
    }

    AVLNode* rightRotation(AVLNode* node) {
        AVLNode* tmp = node->left;
        AVLNode* tmp2 = tmp->right;
        tmp->right = node;
        node->left = tmp2;
        tmp->parent = node->parent;
        node->parent = tmp;
        if (tmp2 != nullptr) {
            tmp2->parent = node;
        }
        if (tmp->parent != nullptr) {
            if (tmp->parent->left == node) {
                tmp->parent->left = tmp;
            } else {
                tmp->parent->right = tmp;
            }
        } else {
            root = tmp;
        }
        updateHeight(node);
        updateHeight(tmp);
        return tmp;
    }

    int getBalanceFactor(AVLNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void reBalance(AVLNode* node) {
        AVLNode* tmp = node;
        while (tmp != nullptr) {
            updateHeight(tmp);
            int balanceFactor = getBalanceFactor(tmp);
            if (balanceFactor == 2) {
                if (getBalanceFactor(tmp->left) >= 0) { // LL Rotation
                    tmp = rightRotation(tmp);
                } else { // LR Rotation
                    tmp->left = leftRotation(tmp->left);
                    tmp = rightRotation(tmp);
                }

            }
            else if (balanceFactor == -2) {
                if (getBalanceFactor(tmp->right) <= 0) { // RR Rotation
                    tmp = leftRotation(tmp);
                } else { // RL Rotation
                    tmp->right = rightRotation(tmp->right);
                    tmp = leftRotation(tmp);
                }
            }
            tmp = tmp->parent;
        }
    }

    AVLNode* searchNode(const T& item) {
        AVLNode* tmp = root;
        while (tmp != nullptr) {
            if (tmp->val == item) {
                return tmp;
            }
            if (item > tmp->val) {
                tmp = tmp->right;
            }
            else {
                tmp = tmp->left;
            }
        }
        return nullptr;
    }

    bool getNode(const T& key, T& result) {
        AVLNode* node = searchNode(key);
        if (node) {
            result = node->val;
            return true;
        }
        return false;
    }

    bool insertNode(const T& item) {
        if (root == nullptr) {
            root = new AVLNode();
            root->val = item;
            nodesCount++;
            return true;
        }
        AVLNode* cur = root;
        AVLNode* parent = nullptr;
        while (cur) {
            if (item < cur->val) {
                parent = cur;
                cur = cur->left;
            } else if (item > cur->val) {
                parent = cur;
                cur = cur->right;
            } else {
                return false;
            }
        }
        AVLNode* newNode = new AVLNode();
        newNode->val = item;
        newNode->parent = parent;
        if (item > parent->val) {
            parent->right = newNode;
        } else {
            parent->left = newNode;
        }
        nodesCount++;
        reBalance(newNode);
        return true;
    }

    bool deleteNode(const T& item) {
        AVLNode* check = searchNode(item);
        if (check == nullptr) {
            return false;
        }
        AVLNode* parent = check->parent;
        AVLNode* target = check;
        // Case 1: No children or one child
        if (check->left == nullptr || check->right == nullptr) {
            AVLNode* child = (check->left != nullptr) ? check->left : check->right;
            if (parent == nullptr) {
                root = child;
            } else if (parent->left == check) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            if (child != nullptr) {
                child->parent = parent;
            }
        }
            // Case 2: Two children
        else {
            AVLNode* predParent = check;
            AVLNode* pred = check->left;
            while (pred->right != nullptr) {
                predParent = pred;
                pred = pred->right;
            }
            check->val = pred->val;
            target = pred;
            if (predParent == check) {
                predParent->left = pred->left;
            } else {
                predParent->right = pred->left;
            }
            if (pred->left != nullptr) {
                pred->left->parent = predParent;
            }
            parent = predParent;
        }
        nodesCount--;
        delete target;
        if (parent != nullptr) {
            reBalance(parent);
        }
        return true;
    }

    void inOrder(AVLNode* avlNode) {
        if (avlNode != nullptr) {
            inOrder(avlNode->left);
            cout << avlNode->val << "\n";
            inOrder(avlNode->right);
        }
    }
    AVLNode* getroot(){
        if(isEmpty()){
            throw runtime_error("Tree is Empty!");
        }
        return root;
    }
    int numOfNodes() {
        return nodesCount;
    }
    bool isEmpty() {
        return nodesCount == 0;
    }

    void printTree() {
       

        // Find the node with the longest string representation to determine spacing
        int maxNodeWidth = findMaxNodeWidth(root);
        int height = getHeight(root);

        // Adjust rows and columns based on tree height and node width
        int rows = height * 2 - 1;
        int cols = (1 << height) * maxNodeWidth * 2;

        DynamicArray<DynamicArray<string>> matrix(rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i].push(" ");
            }
        }

        fillMatrix(root, matrix, 0, cols / 2, cols / 4, maxNodeWidth);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j];
            }
            cout << "\n";
        }
    }

    ~AVLTree() {
        deleteTree(root);
    }
};

#endif
