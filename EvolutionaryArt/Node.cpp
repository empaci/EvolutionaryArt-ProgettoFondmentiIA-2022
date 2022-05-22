#include "Node.h"
#include <iostream>


Node::Node() {
    this->value = -1;
    this->right = nullptr;
    this->left = nullptr;
}

void Node::setOperation(std::string operation) {
    //this->operation = operation; NOT WORKING
    this->operation = operation;
    //this->operation = std::string(operation.length(), '\0');
    //std::copy(operation.rbegin(), operation.rend(), this->operation.rbegin()); //NOT WORKING
    //this->operation = std::string(operation);
}

void Node::setVar(bool var) {
    if (isLeaf()) {
        this->var = var;
    }
}

void Node::setValue(int value) {
    if (isLeaf()) {
        this->value = value;
    }
}

bool Node::isLeaf() {
    if (!left) {
        return true;
    }
    else {
        return false;
    }
}

void Node::setLeftChildren(Node* n) {
    this->left = n;
}

void Node::setRightChildren(Node* n) {
    this->right = n;
}

std::string Node::toString() {
    if (!isLeaf()) {
        std::string op = this->operation + "(";
        if (left) {
            op.append(this->left->toString());
            op.append(")");
        }
        if (right) {
            op.append(this->right->toString());
            op.append(")");
        }
        return op;
    }
    else {
        if (this->value != -1) {
            return std::to_string(value) + ",";
        }
        else {
            if (this->var) {
                return "x,";
            } else {
                return "y,";
            }
        }
    }
}