/**
 *	Author : Tarek Salah
 */
#include "NodePQ.h"


//default constructor
template <class T>
        NodePQ<T>::NodePQ(){}
//===================================================
//constructor with parameter object and key
template <class T>
        NodePQ<T>::NodePQ(T object,double key)
        {
            this -> object = object;
            this -> key = key;
        }
//===================================================
// getting object of the node
template <class T>
        T NodePQ<T>::getObject( )
        {
            return object;
        }
//====================================================
// setting object in the node
template <class T>
        void NodePQ<T>:: setObject(T object)
        {
            this -> object = object;
        }
//====================================================
//getting key of the node
template <class T>
        double NodePQ<T>:: getKey( )
        {
            return key;
        }
//====================================================
//setting key of node
template <class T>
        void NodePQ<T>:: setKey(double key)
        {
            this -> key = key;
        }
//===================================================
//getting next node in the priority queue
template <class T>
        NodePQ<T> * NodePQ<T>::getNext()
        {
            return nextNode;
        }
//===================================================
//setting next node in the priority queue
template <class T>
        void NodePQ<T>:: setNext(NodePQ *nextNode)
        {
            this -> nextNode = nextNode;
        }
//===================================================
// getting previous node in the priority queue
template <class T>
        NodePQ<T> * NodePQ<T>::getPrev( )
        {
            return prevNode;
        }
//===================================================
//setting previous node in the priority queue
template <class T>
        void NodePQ<T>:: setPrev(NodePQ *prevNode)
        {
            this -> prevNode = prevNode;
        }
//===================================================
