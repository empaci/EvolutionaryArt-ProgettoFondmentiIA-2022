#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <iterator>
#include <string>

class Node{ 
    private:
        char operation[4];
        bool var;
        int value;
        Node* left;
        Node* right;

    public:
        Node();
        void setOperation(char* operation);
        void setVar(bool var);
        void setValue(int value);
        bool isLeaf();
        void setLeftChildren(Node* n);
        void setRightChildren(Node* n);
        std::string toString();
};

#endif
