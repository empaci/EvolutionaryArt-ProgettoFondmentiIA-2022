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
        void setOperation(std::string);
        void setVar(bool);
        void setValue(int);
        bool isLeaf();
        void setLeftChildren(Node*);
        void setRightChildren(Node*);
        std::string toString();
};

#endif
