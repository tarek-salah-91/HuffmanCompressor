/**
 *	Author : Tarek Salah
 */
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "Node.h"
#include "Priority_Queue.h"
#include <map>
#include <list>

using namespace std;

template <class T>

class BinaryTree{

    private:
        Node<T> *root;

    public:
        BinaryTree();

        bool isLeaf(Node<T>*node);

        void build(Priority_Queue< Node <T>* > *pq);

        map< int,string > traverse(Node<T>*rt, list< Node<T>* >&myCode);

        Node<T>* getRoot();

};
#include "BinaryTree.cpp"
#endif // BINARYTREE_H
