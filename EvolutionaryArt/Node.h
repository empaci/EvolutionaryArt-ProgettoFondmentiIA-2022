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
        void setOperation(std::string operation);
        void setVar(bool var);
        void setValue(int value);
        bool isLeaf();
        void setLeftChildren(Node* n);
        void setRightChildren(Node* n);
        std::string toString();
};

#endif
