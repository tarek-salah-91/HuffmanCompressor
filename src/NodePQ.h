/**
 *	Author : Tarek Salah
 */

#ifndef NODEPQ_H
#define NODEPQ_H

template <class T>

class NodePQ{
              public:
                    NodePQ();

                    NodePQ(T object,double key);

                    T getObject( );

                    void setObject(T object);

                    double getKey( );

                    void setKey(double key);

                    NodePQ *getNext( );

                    void setNext(NodePQ *nextNode);

                    NodePQ *getPrev( );

                    void setPrev(NodePQ *prevNode);

             private:
                      T object;

                      double key;

                      NodePQ *nextNode;

                      NodePQ *prevNode;
          };
#include "NodePQ.cpp"
#endif // NODEPQ_H
