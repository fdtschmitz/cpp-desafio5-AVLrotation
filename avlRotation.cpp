#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node* node) {
    if (node == NULL) return 0;
    return node->height;
}

struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node is initially added at leaf
    return node;
}

struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

struct Node* leftRightRotate(struct Node* node) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

struct Node* rightLeftRotate(struct Node* node) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
}

int getBalance(struct Node* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

struct Node* insert(struct Node* node, int key) {
    // Perform the normal BST insertion
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Duplicate keys not allowed in AVL, do nothing
        return node;

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node to check if it became unbalanced
    int balance = getBalance(node);

    // Left-Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right-Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left-Right Case
    if (balance > 1 && key > node->left->key) {
        return leftRightRotate(node);
    }

    // Right-Left Case
    if (balance < -1 && key < node->right->key) {
        return rightLeftRotate(node);
    }

    // Return the unchanged node pointer
    return node;
}

void preOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    struct Node* root = NULL;

    // Insert nodes into the AVL tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Preorder traversal of the constructed AVL tree:\n");
    preOrder(root);

    return 0;
}
