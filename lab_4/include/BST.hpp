#ifndef BST_HPP
#define BST_HPP

#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include "Errors.hpp"
#include "Complex.hpp"

template <typename T>
struct Node {
    T data;
    Node* left;
    Node* right;
};

template <typename T>
class BST {
    private:
        Node<T>* root;
        size_t nodeCount;

        void Clear(Node<T>* node)
        {
            if(node) {
                Clear(node->left);
                Clear(node->right);
                delete node;
            }
        }

        Node<T>* Insert(Node<T>* node, const T& value)
        {
            if(!node) {
                Node<T>* newNode = new Node<T>;
                newNode->data = value;
                newNode->left = nullptr;
                newNode->right = nullptr;
                nodeCount++;
                return newNode;
            }
            if(value < node->data) {
                node->left = Insert(node->left, value);
            } else if(value > node->data) {
                node->right = Insert(node->right, value);
            }
            return node;
        }

        Node<T>* FindMin(Node<T>* node)
        {
            while (node && node->left) {
                node = node->left;
            }
            return node;
        }
    
        Node<T>* Remove(Node<T>* node, const T& value)
        {
            if (!node) return nullptr;
    
            if (value < node->data) {
                node->left = Remove(node->left, value);
            } else if (value > node->data) {
                node->right = Remove(node->right, value);
            } else {
                if (!node->left) {
                    Node<T>* temp = node->right;
                    delete node;
                    nodeCount--;
                    return temp;
                } else if (!node->right) {
                    Node<T>* temp = node->left;
                    delete node;
                    nodeCount--;
                    return temp;
                }

                Node<T>* temp = FindMin(node->right);
                node->data = temp->data;
                node->right = Remove(node->right, temp->data);
            }
            return node;
        }

        bool IsContains(Node<T>* node, const T& value) const
        {
            if (!node) return false;
            if (value == node->data) return true;
            return (value < node->data) ? IsContains(node->left, value) : IsContains(node->right, value);
        }

        void Inorder(Node<T>* node) const
        {
            if (!node) return;
            Inorder(node->left);
            std::cout << node->data << " ";
            Inorder(node->right);
        }
    
        void Preorder(Node<T>* node) const
        {
            if (!node) return;
            std::cout << node->data << " ";
            Preorder(node->left);
            Preorder(node->right);
        }
    
        void Postorder(Node<T>* node) const
        {
            if (!node) return;
            Postorder(node->left);
            Postorder(node->right);
            std::cout << node->data << " ";
        }

        Node<T>* FindNode(Node<T>* node, const T& value) const
        {
            if (!node) return nullptr;
            if (value == node->data) return node;
            if (value < node->data) return FindNode(node->left, value);
            return FindNode(node->right, value);
        }

        bool IsPathValid(const std::string& path) const
        {
            for (char c : path) {
                if (c != 'l' && c != 'r' && c != 'L' && c != 'R') {
                    return false;
                }
            }
            return true;
        }

        void CopySubtree(Node<T>* source, Node<T>*& destination) const
        {
            if (!source) return;
            destination = new Node<T>{source->data, nullptr, nullptr};
            CopySubtree(source->left, destination->left);
            CopySubtree(source->right, destination->right);
        }

        size_t CountNodes(Node<T>* node) const {
            if (!node) return 0;
            return 1 + CountNodes(node->left) + CountNodes(node->right);
        }

        Node<T>* BuildFromInorder(const std::vector<T>& arr, int start, int end)
        {
            if (start > end) return nullptr;
            
            int mid = start + (end - start) / 2;
            Node<T>* node = new Node<T>;
            node->data = arr[mid];
            node->left = BuildFromInorder(arr, start, mid - 1);
            node->right = BuildFromInorder(arr, mid + 1, end);
            
            return node;
        }
    
        Node<T>* BuildFromPreorder(const std::vector<T>& arr, int& index, T min, T max)
        {
            if (index >= arr.size()) return nullptr;
            
            T val = arr[index];
            if (val < min || val > max) return nullptr;
            
            Node<T>* node = new Node<T>;
            node->data = val;
            index++;
            
            node->left = BuildFromPreorder(arr, index, min, val);
            node->right = BuildFromPreorder(arr, index, val, max);
            
            return node;
        }
    
        Node<T>* BuildFromPostorder(const std::vector<T>& arr, int& index, T min, T max)
        {
            if (index < 0) return nullptr;
            
            T val = arr[index];
            if (val < min || val > max) return nullptr;
            
            Node<T>* node = new Node<T>;
            node->data = val;
            index--;
            
            node->right = BuildFromPostorder(arr, index, val, max);
            node->left = BuildFromPostorder(arr, index, min, val);
            
            return node;
        }

    public:
        BST() : root(nullptr), nodeCount(0) {}

        BST(const std::vector<T>& elements, size_t Type) : root(nullptr), nodeCount(elements.size())
        {
            if (elements.empty()) return;
            
            switch(Type) {
                case 1: {
                    root = BuildFromInorder(elements, 0, elements.size() - 1);
                    break; }
                case 2: {
                    int index = 0;
                    root = BuildFromPreorder(elements, index, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
                    break; }
                case 3: {
                    int index = elements.size() - 1;
                    root = BuildFromPostorder(elements, index, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
                    break; }
                default:
                    throwError(INVALID_ARGUMENT);
            }
        }

        ~BST() { Clear(root); }

        void Insert(const T& val) { root = Insert(root, val); }
        void Remove(const T& val) { root = Remove(root, val); }
        bool IsContains(const T& val) const { return IsContains(root, val); }

        Node<T>* FindByPath(const std::string& path) {

            if (path.empty()) {
                if (!root) throwError(INVALID_ARGUMENT);
                return root;
            }

            if (!IsPathValid(path)) throwError(INVALID_ARGUMENT);
    
            Node<T>* current = root;
            if (!current) throwError(INVALID_ARGUMENT);

            std::string pathCopied = path;

            while (!pathCopied.empty()) {
                char direction = pathCopied[0];
                pathCopied.erase(0, 1);
                if (direction == 'l' || direction == 'L') {
                    current = current->left;
                } else if (direction == 'r' || direction == 'R') {
                    current = current->right;
                }
                if (!current) throwError(INVALID_ARGUMENT);
            }
            return current;
        }

        BST<T> GetSubtree(const T& value) const
        {
            BST<T> subtree;
            Node<T>* startNode = FindNode(root, value);
            if (startNode) {
                CopySubtree(startNode, subtree.root);
                subtree.nodeCount = CountNodes(subtree.root);
            }
            return subtree;
        }

        size_t size() const {return nodeCount;}

        void printInorder() const
        {
            Inorder(root);
            std::cout << "\n";
        }

        void printPreorder() const
        {
            Preorder(root);
            std::cout << "\n";
        }
    
        void printPostorder() const
        {
            Postorder(root);
            std::cout << "\n";
        }

        void printTree(Node<T>* node) const
        {
            int space = 0;
            if (!node) return;
            space += 4;
            printTree(node->right);
            std::cout << std::string(space - 4, ' ') << node->data << "\n";
            printTree(node->left);
        }
    
        void printTree() const { printTree(root); }
};
#endif