#ifndef BSTREE_CPP
#define BSTREE_CPP

#include "BSTree.h"
#include <sstream>  // Добавлено для std::istringstream

namespace BST {

// Constructor
    template <typename T>
    BSTree<T>::BSTree() : root(nullptr) {}

// Copy constructor
    template <typename T>
    BSTree<T>::BSTree(const BSTree& other) : root(nullptr) {
        copyTree(root, other.root);
    }

// Move constructor
    template <typename T>
    BSTree<T>::BSTree(BSTree&& other) noexcept : root(nullptr) {
        moveTree(root, std::move(other.root));
    }

// Destructor
    template <typename T>
    BSTree<T>::~BSTree() {
        deleteTree(root);
    }

// Copy assignment
    template <typename T>
    BSTree<T>& BSTree<T>::operator=(const BSTree& other) {
        if (this != &other) {
            deleteTree(root);
            copyTree(root, other.root);
        }
        return *this;
    }

// Move assignment
    template <typename T>
    BSTree<T>& BSTree<T>::operator=(BSTree&& other) noexcept {
        if (this != &other) {
            deleteTree(root);
            moveTree(root, std::move(other.root));
        }
        return *this;
    }

// Helper: copy tree
    template <typename T>
    void BSTree<T>::copyTree(typename BSTree<T>::Node*& dest, typename BSTree<T>::Node* src) {
        if (!src) {
            dest = nullptr;
            return;
        }
        dest = new Node(src->data);
        copyTree(dest->left, src->left);
        copyTree(dest->right, src->right);
    }

// Helper: move tree
    template <typename T>
    void BSTree<T>::moveTree(typename BSTree<T>::Node*& dest, typename BSTree<T>::Node*&& src) {
        dest = src;
        src = nullptr;
    }

// Helper: delete entire tree
    template <typename T>
    void BSTree<T>::deleteTree(typename BSTree<T>::Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

// Insert (lvalue)
    template <typename T>
    typename BSTree<T>::Node* BSTree<T>::insertNode(typename BSTree<T>::Node* node, const T& value) {
        if (!node) return new Node(value);
        if (value < node->data)
            node->left = insertNode(node->left, value);
        else if (value > node->data)
            node->right = insertNode(node->right, value);
        return node;
    }

    template <typename T>
    void BSTree<T>::insert(const T& value) {
        root = insertNode(root, value);
    }

// Insert (rvalue)
    template <typename T>
    typename BSTree<T>::Node* BSTree<T>::insertNode(typename BSTree<T>::Node* node, T&& value) {
        if (!node) return new Node(std::move(value));
        if (value < node->data)
            node->left = insertNode(node->left, std::move(value));
        else if (value > node->data)
            node->right = insertNode(node->right, std::move(value));
        return node;
    }

    template <typename T>
    void BSTree<T>::insert(T&& value) {
        root = insertNode(root, std::move(value));
    }

// Find minimum node
    template <typename T>
    typename BSTree<T>::Node* BSTree<T>::findMin(typename BSTree<T>::Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

// Delete node
    template <typename T>
    typename BSTree<T>::Node* BSTree<T>::deleteNode(typename BSTree<T>::Node* node, const T& value) {
        if (!node) return nullptr;

        if (value < node->data)
            node->left = deleteNode(node->left, value);
        else if (value > node->data)
            node->right = deleteNode(node->right, value);
        else {
            if (!node->left) {
                typename BSTree<T>::Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                typename BSTree<T>::Node* temp = node->left;
                delete node;
                return temp;
            }

            typename BSTree<T>::Node* minNode = findMin(node->right);
            node->data = minNode->data;
            node->right = deleteNode(node->right, minNode->data);
        }
        return node;
    }

    template <typename T>
    void BSTree<T>::remove(const T& value) {
        root = deleteNode(root, value);
    }

// Clear tree
    template <typename T>
    void BSTree<T>::clear() {
        deleteTree(root);
        root = nullptr;
    }

// Search
    template <typename T>
    bool BSTree<T>::searchNode(typename BSTree<T>::Node* node, const T& value) const {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return searchNode(node->left, value);
        return searchNode(node->right, value);
    }

    template <typename T>
    bool BSTree<T>::search(const T& value) const {
        return searchNode(root, value);
    }

// Traversals
    template <typename T>
    void BSTree<T>::preOrder(typename BSTree<T>::Node* node, std::ostream& os) const {
        if (node) {
            os << node->data << " ";
            preOrder(node->left, os);
            preOrder(node->right, os);
        }
    }

    template <typename T>
    void BSTree<T>::inOrder(typename BSTree<T>::Node* node, std::ostream& os) const {
        if (node) {
            inOrder(node->left, os);
            os << node->data << " ";
            inOrder(node->right, os);
        }
    }

    template <typename T>
    void BSTree<T>::postOrder(typename BSTree<T>::Node* node, std::ostream& os) const {
        if (node) {
            postOrder(node->left, os);
            postOrder(node->right, os);
            os << node->data << " ";
        }
    }

    template <typename T>
    void BSTree<T>::printPreOrder(std::ostream& os) const {
        preOrder(root, os);
        os << std::endl;
    }

    template <typename T>
    void BSTree<T>::printInOrder(std::ostream& os) const {
        inOrder(root, os);
        os << std::endl;
    }

    template <typename T>
    void BSTree<T>::printPostOrder(std::ostream& os) const {
        postOrder(root, os);
        os << std::endl;
    }

// Save to file
    template <typename T>
    void BSTree<T>::saveToFile(typename BSTree<T>::Node* node, std::ofstream& file) const {
        if (!node) {
            file << "# ";
            return;
        }
        file << node->data << " ";
        saveToFile(node->left, file);
        saveToFile(node->right, file);
    }

    template <typename T>
    void BSTree<T>::save(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file for writing");
        }
        saveToFile(root, file);
        file.close();
    }

// Load from file
    template <typename T>
    typename BSTree<T>::Node* BSTree<T>::loadFromFile(std::ifstream& file) {
        std::string token;
        file >> token;
        if (token == "#") return nullptr;

        T value;
        std::istringstream iss(token);
        iss >> value;

        typename BSTree<T>::Node* node = new Node(value);
        node->left = loadFromFile(file);
        node->right = loadFromFile(file);
        return node;
    }

    template <typename T>
    void BSTree<T>::load(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file for reading");
        }
        clear();
        root = loadFromFile(file);
        file.close();
    }

}
#endif