/**
 *	Author : Tarek Salah
 */
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <NodePQ.h>
using namespace std;
template<class T>
        class Priority_Queue{
            private:
                long size;
                NodePQ<T> *headNode;

                NodePQ<T> *currentNode;

                NodePQ<T> *tailNode;
            public:

                Priority_Queue();

                void insert(T object,double key);

                T getMinmumKey();

                double getMinKey();

                T removeMinmumKey();

                T getMaximumKey();

                T getMaxKey();

                T removeMaximumKey();

                void view ();

                int getSize();

                bool isEmpty();
            };
#include "Priority_Queue.cpp"
#endif // PRIORITY_QUEUE_H
