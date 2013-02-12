/**
 *	Author : Tarek Salah
 */
#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

template <class T>

class Node{
              private:
                      T object;

                      string code;

                      Node *parent;

                      Node *leftChild;

                      Node *rightChild;
              public:
                      T get();

                      void set(T object);

                      Node *getParent();

                      void setParent(Node *Parent);

                      Node *getLeftChild();

                      void setLeftChild(Node *left);

                      Node *getRightChild();

                      void setRightChild(Node *right);

                      string getCode();

                      void setCode(string code);
          };
#include "Node.cpp"
#endif // NODE_H
