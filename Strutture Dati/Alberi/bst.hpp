//
//  bst.hpp
//  alberi binari di ricerca

#ifndef bst_hpp
#define bst_hpp

#include <iostream>
using namespace std;

template<typename T>
class BST;

template<typename T>
class BSTNode;

template<typename T>
ostream& operator<<(ostream& os, const BST<T>& bst);

template <typename T>
class BSTNode
{
public:
    T GetValue() { return val; }
private:
    BSTNode(T _val) : val(_val), left(NULL), right(NULL), parent(NULL) {}
    T val;
    BSTNode<T>* left;
    BSTNode<T>* right;
    BSTNode<T>* parent;

    friend class BST<T>;
};

template <typename T>
class BST
{
public:
    BST() : root(NULL) {}
    ~BST() { Delete(root); }
    BST& Insert(T val);
    BSTNode<T>* Search(T val);
    BSTNode<T>* Min(BSTNode<T>* p = NULL);
    BSTNode<T>* Next(BSTNode<T>* p);
    void Remove(BSTNode<T>* p);

private:
    void print(ostream& os, BSTNode<T>* node) const;
    void printPreorder(ostream& os, BSTNode<T>* node) const;
    BSTNode<T>* Search(T val, BSTNode<T>* node);
    BSTNode<T>* Trapianta(BSTNode<T>* dest, BSTNode<T>* src);
    void Delete(BSTNode<T>* p);

    BSTNode<T>* root;

    // Corretto friend operator
    friend ostream& operator<< <>(ostream& os, const BST<T>& bst);
};

// Definizione dell'operatore<< (MUST in header)
template <typename T>
ostream& operator<<(ostream& os, const BST<T>& bst)
{
    bst.print(os, bst.root);
    return os;
}

#include "bst.cpp"

#endif /* bst_hpp */
