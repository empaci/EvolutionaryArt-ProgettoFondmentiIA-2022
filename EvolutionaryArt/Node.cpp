#include "Node.h"
#include <iostream>


Node::Node() {
    this->value = -1;
    this->right = nullptr;
    this->left = nullptr;
}

void Node::setOperation(std::string operation) {
    if (!isLeaf()) {
        this->operation = operation;
    }
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
    if (right && left) {
        return true;
    }
    else {
        return false;
    }
}

void Node::setLeftChildren(Node* n) {
    left = n;
}

void Node::setRightChildren(Node* n) {
    right = n;
}

std::string Node::toString() {
    if (!isLeaf()) {
        return "Op: " + this->operation + " " + toString();
    }
    else {
        if (this->value != -1) {
            return "Node value: " + std::to_string(value);
        }
        else {
            if (this->var) {
                return "x";
            } else {
                return "y";
            }
        }
    }
}