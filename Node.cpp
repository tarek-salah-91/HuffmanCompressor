/**
 *	Author : Tarek Salah
 */
#include "Node.h"
#include <string>

// constructor of node

// get the element of the node
template <class T>
T Node<T>::get( )
{
    return object;
}
//================================
// set the element of the node
template <class T>
void Node<T>::set(T object)
{
    this -> object = object;
}
//=================================
// get the parent of node
template <class T>
    Node<T>* Node<T>::getParent( )
    {
        return parent;
    }
//=================================
// set the parent of node
template <class T>
    void Node<T>::setParent(Node *Parent)
    {
        this -> parent = Parent;
    }
//=================================
// get the left child of node
template <class T>
    Node<T>* Node<T>:: getLeftChild( )
    {
        return leftChild;
    }
//==================================
// set the left child of node
template <class T>
    void Node<T>:: setLeftChild(Node *left)
    {
        this -> leftChild = left;
    }
//===================================
// get the right child of node
template <class T>
    Node<T>* Node<T>::getRightChild( )
    {
        return rightChild;
    }
//==================================
// set the right child of node
template <class T>
    void Node<T>:: setRightChild(Node *right)
    {
        this -> rightChild = right;
    }
//===================================
// get the huffman code on the node
template <class T>
    string Node<T>:: getCode(){
        return code;
    }
//====================================
// set the huffman code on the node
template <class T>
    void Node<T>:: setCode(string code){
        this -> code = code;
    }

