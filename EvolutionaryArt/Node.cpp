#include "Node.h"
#include <iostream>


Node::Node() {
}

void Node::setOperation(char* operation) {
    if (!isLeaf()) {
        std::copy(this->operation, this->operation + 4, operation);
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
    else {
        this->value = 100;
    }
}

bool Node::isLeaf() {
    if (right == NULL && left == NULL) {
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
    return "Node value: " + std::to_string(value);
}