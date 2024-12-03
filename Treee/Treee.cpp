#include <iostream>
using namespace std;

class Tree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* copy(Node* node) {
        if (!node) return nullptr;
        Node* newNode = new Node(node->key);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    Node* erase(Node* node, int key) {
        if (!node) return nullptr;
        if (key < node->key) {
            node->left = erase(node->left, key);
        }
        else if (key > node->key) {
            node->right = erase(node->right, key);
        }
        else {
            if (!node->left) {
                Node* rightChild = node->right;
                delete node;
                return rightChild;
            }
            else if (!node->right) {
                Node* leftChild = node->left;
                delete node;
                return leftChild;
            }
            else {
                Node* successor = node->right;
                while (successor->left) successor = successor->left;
                node->key = successor->key;
                node->right = erase(node->right, successor->key);
            }
        }
        return node;
    }

    void print(Node* node) const {
        if (node) {
            print(node->left);
            cout << node->key << " ";
            print(node->right);
        }
    }

public:
    Tree() : root(nullptr) {}
    Tree(const Tree& other) : root(copy(other.root)) {}
    ~Tree() { clear(root); }

    Tree& operator=(const Tree& other) {
        if (this != &other) {
            clear(root);
            root = copy(other.root);
        }
        return *this;
    }

    void insert(int key) {
        Node** current = &root;
        while (*current) {
            if (key < (*current)->key) current = &((*current)->left);
            else if (key > (*current)->key) current = &((*current)->right);
            else return;
        }
        *current = new Node(key);
    }

    void erase(int key) {
        root = erase(root, key);
    }

    void print() const {
        print(root);
        cout << endl;
    }
};

int main() {
    Tree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(15);
    tree.insert(25);

    cout << "Initial tree: ";
    tree.print();

    tree.erase(20);
    cout << "After erasing 20: ";
    tree.print();

    Tree treeCopy = tree;
    cout << "Copied tree: ";
    treeCopy.print();

}
