#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <fstream>
#include <memory>
#include <queue>

namespace BST {

    template <typename T>
    class BSTree {
    private:
        struct Node {
            T data;
            Node* left;
            Node* right;

            Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
            Node(T&& value) : data(std::move(value)), left(nullptr), right(nullptr) {}
        };

        Node* root;

        void copyTree(Node*& dest, Node* src);
        void moveTree(Node*& dest, Node*&& src);
        void deleteTree(Node* node);
        Node* insertNode(Node* node, const T& value);
        Node* insertNode(Node* node, T&& value);
        Node* deleteNode(Node* node, const T& value);
        Node* findMin(Node* node) const;
        bool searchNode(Node* node, const T& value) const;
        void preOrder(Node* node, std::ostream& os) const;
        void inOrder(Node* node, std::ostream& os) const;
        void postOrder(Node* node, std::ostream& os) const;
        void saveToFile(Node* node, std::ofstream& file) const;
        Node* loadFromFile(std::ifstream& file);

    public:
        BSTree();
        BSTree(const BSTree& other);
        BSTree(BSTree&& other) noexcept;
        ~BSTree();

        BSTree& operator=(const BSTree& other);
        BSTree& operator=(BSTree&& other) noexcept;

        void insert(const T& value);
        void insert(T&& value);
        void remove(const T& value);
        void clear();
        bool search(const T& value) const;

        void printPreOrder(std::ostream& os = std::cout) const;
        void printInOrder(std::ostream& os = std::cout) const;
        void printPostOrder(std::ostream& os = std::cout) const;

        void save(const std::string& filename) const;
        void load(const std::string& filename);

        friend std::ostream& operator<<(std::ostream& os, const BSTree& tree) {
            tree.printInOrder(os);
            return os;
        }
    };

} // namespace BST

#include "BSTree.cpp"
#endif