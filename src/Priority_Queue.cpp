/**
 *	Author : Tarek Salah
 */
#include <NodePQ.h>
#include "Priority_Queue.h"
#include <iostream>
using namespace std;

template <class T>
        Priority_Queue<T>::Priority_Queue()
        {
            headNode=new NodePQ<T>();
            tailNode=new NodePQ<T>();
            headNode->setNext(tailNode);
            headNode->setPrev(NULL);
            tailNode->setPrev(headNode);
            tailNode->setNext(NULL);
            size=0;
        }
//===============================
// insertion method
template <class T>
        void Priority_Queue<T>:: insert(T object,double key)
        {
            NodePQ<T> *newNode=new NodePQ<T>(object,key);
            currentNode=headNode->getNext();
            if(currentNode!=tailNode){
               while(currentNode!=tailNode){
                   if(key<currentNode->getKey()){
                       newNode->setNext(currentNode);
                       newNode->setPrev(currentNode->getPrev());
                       currentNode->getPrev()->setNext(newNode);
                       currentNode->setPrev(newNode);
                       break;
                   }
                   else{
                      currentNode=currentNode->getNext();
                      if(currentNode==tailNode){
                          currentNode=currentNode->getPrev();
                          newNode->setNext(tailNode);
                          newNode->setPrev(currentNode);
                          tailNode->setPrev(newNode);
                          currentNode->setNext(newNode);
                          break;
                      }
                   }
               }
           }else{
               headNode->setNext(newNode);
               tailNode->setPrev(newNode);
               newNode->setNext(tailNode);
               newNode->setPrev(headNode);
           }
           size++;
        }
//==================================================
//  GET MINIMUM KEY
template <class T>
        T Priority_Queue<T>:: getMinmumKey()
        {
            return headNode->getNext()->getObject();
        }
//================================================
template <class T>
        double Priority_Queue<T>:: getMinKey()
        {
            return headNode->getNext()->getKey();
        }
//================================================
//  REMOVE MINMUM KEY
template <class T>
        T Priority_Queue<T>:: removeMinmumKey()
        {
            currentNode=headNode->getNext();
            headNode->setNext(currentNode->getNext());
            currentNode->getNext()->setPrev(headNode);
            T ob=currentNode->getObject();
            delete currentNode;
            size--;
            return ob;
        }
//==================================================
//  GET MAXIMUM KEY
template <class T>
        T Priority_Queue<T>:: getMaximumKey()
        {
            return tailNode->getPrev()->getObject();
        }
//===============================================
template <class T>
        T Priority_Queue<T>:: getMaxKey()
        {
            return tailNode->getPrev()->getKey();
        }
//================================================
//  REMOVE MAXIMUM KEY
template <class T>
        T Priority_Queue<T>:: removeMaximumKey()
        {
            currentNode=tailNode->getPrev();
            tailNode->setPrev(currentNode->getPrev());
            currentNode->getPrev()->setNext(tailNode);
            T ob=currentNode->getObject();
            delete currentNode;
            size--;
            return ob;
        }
//================================================
//   VIEW QUEUE
template <class T>
        void Priority_Queue<T>:: view ()
        {
            currentNode=headNode->getNext();
            while(currentNode!=tailNode){
                cout<<currentNode->getKey()<<"==>"<<currentNode->getObject()<<endl;
                currentNode=currentNode->getNext();
            }
        }

//=================================================
//    SIZE
template <class T>
        int Priority_Queue<T>:: getSize(){
            return size;
        }
//================================================
template <class T>
        bool Priority_Queue<T>:: isEmpty(){
            if(size==0)
                return true;
            else
                return false;
        }
