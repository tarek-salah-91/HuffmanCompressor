/**
 *	Author : Tarek Salah
 */
#include "Node.h"
#include "BinaryTree.h"
#include <string>
#include <map>

// constructor for binary tree
template <class T>
        BinaryTree<T>::BinaryTree(){};
//==================================================================
// check if the current node is leaf node or not
template <class T>
        bool BinaryTree<T>:: isLeaf(Node<T>*node)
        {
            if(node->getLeftChild()==NULL&&node->getRightChild()==NULL)
                return true;
            else
                return false;
        }
//=================================================================
/**
  *build() method used to build atree using priority queue
  *as it takes the first two node sinn the priority queue and
  *add their keys then put it in new node that will be its parent
  *finally we put the new node i the priority queue and repete again
  */
template <class T>
        void BinaryTree<T>:: build(Priority_Queue< Node <T>* > *pq)
        {
            if(pq->getSize()==1)
            {
                Node<T> *rootI=new Node<T>();
                rootI->setLeftChild(pq->removeMinmumKey());
                root=rootI;
            }
            else
            {
                while(pq->getSize()!=1){
                    Node<T> *n1;
                    double k1=pq->getMinKey();
                    if(!pq->isEmpty())
                    {
                        n1=pq->removeMinmumKey();
                    }
                    double k2=pq->getMinKey();
                    Node<T> *n2;
                    if(!pq->isEmpty())
                    {
                        n2=pq->removeMinmumKey();
                    }
                    double newK=k1+k2;
                    Node<T> *n=new Node<T>();
                    n->setLeftChild(n1);
                    n->setRightChild(n2);
                    pq->insert(n,newK);
                }
                root=pq->removeMinmumKey();
            }
        }
//===============================================================================
/**
  *traverse method used to consruct huffman code throw tarversing the tree
  *and set code attribute to the new code according to the current position
  *if the child is left add "0" and if the child is right add "1"
  */
template <class T>
        map< int,string > BinaryTree<T>:: traverse(Node<T>*rt, list< Node<T>* >&myCode)
        {
            map<int,string>traverse;
            rt->setCode("");
            myCode.push_back(rt);
            while(!myCode.empty()){
                Node<T>*r = myCode.front();
                if(r->getLeftChild() != NULL){
                    r -> getLeftChild() -> setCode(r->getCode()+"0");
                   myCode.push_back(r -> getLeftChild());
                   if(isLeaf(r -> getLeftChild())){
                    traverse[r -> getLeftChild()->get()] = r->getLeftChild()->getCode();
                    //traverse.push_back(r -> getLeftChild());
                   }
               }
                   if( r->getRightChild() != NULL){
                   r -> getRightChild() -> setCode(r->getCode()+"1");
                   myCode.push_back(r -> getRightChild());
                   if(isLeaf(r -> getRightChild())){
                    traverse[r -> getRightChild()->get()] = r->getRightChild()->getCode();
                    //traverse.push_back(r -> getRightChild());
                   }
                }
                myCode.pop_front();;
            }
            return traverse;
        }
//====================================================================
// get the root of the tree to travers it
template <class T>
        Node<T>* BinaryTree<T>:: getRoot()
        {
            return root;
        }
//===================================================================

