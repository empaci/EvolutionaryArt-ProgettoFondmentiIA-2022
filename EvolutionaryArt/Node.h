#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <iterator>
#include <string>

class Node{ 
    private:
        std::string operation;
        bool var;
        int value;
        Node* left;
        Node* right;

    public:
        Node();
        //Node(Node*);
        void setOperation(std::string);
        void setVar(bool);
        void setValue(int);
        bool isLeaf();

        void setLeftChildren(Node*);
        Node* getLeftChild();
        Node* getRightChild();
        void setRightChildren(Node*);
        
        std::string toString();
        
        int getNumberOfParents(Node*, int*);
        int getNumberOfParentsAux(Node*, int*);
        int getNode(Node*, int*, Node*);
        void getRandomChild(Node*, Node*);
};

#endif
