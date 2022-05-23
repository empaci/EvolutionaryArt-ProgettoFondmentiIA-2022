#include "Node.h"
#include <iostream>


Node::Node() {
    this->value = -1;
    this->right = nullptr;
    this->left = nullptr;
}

void Node::setOperation(std::string operation) {
    this->operation = operation;
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

Node* Node::getLeftChild() {
    return this->left;
}

void Node::setRightChildren(Node* n) {
    this->right = n;
}

Node* Node::getRightChild() {
    return this->right;
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

//return the pointer from a parent to a random child. No head.
void Node::getRandomChild(Node* head, Node* randomChild) {
    
    //int depth = treeDepth(head);
    //int n_children = nChildrenAtDepth(head, depth);
    int* n_node = new int();
    getNumberOfParents(head, n_node);
    int r = (std::rand() % (*n_node));
    Node* n = new Node();
    getNode(head, &r, n);
    
    int l_or_r = 0;

    if (n->getRightChild()) {
        l_or_r = (std::rand() % 2);
    }
    if (l_or_r == 0) {
        *randomChild = *(n->getLeftChild());
    } else {
        *randomChild = *(n->getRightChild());
    }
    
    return;
}

//given a tree, returns the number of parents (n of nodes - n of leaves)
int Node::getNumberOfParents(Node* head, int* n) {
    *n = 0;
    if (!head->isLeaf()) {
        getNumberOfParentsAux(head, n);
        return 1;
    }
    else {
        return 0;
    }
}

int Node::getNumberOfParentsAux(Node* head, int* n) {
    if (!head->isLeaf()) {
        if (head->getLeftChild() && !head->getRightChild()) {
            *n = *n + 1;
            return getNumberOfParentsAux(head->getLeftChild(), n);
        }
        if (head->getRightChild()) {
            *n = *n + 1;
            return getNumberOfParentsAux(head->getRightChild(), n) + getNumberOfParentsAux(head->getLeftChild(), n);
        }
    }
    else {
        return 0;
    }
}

int Node::getNode(Node* head, int* n, Node* child) {
    if (!head->isLeaf()) {
        
        *n = *n - 1;
        if (*n == 0) {
            *child = *head;
            return -1;
        }

        if (head->getLeftChild() && !head->getRightChild()) {
            return *n + getNode(head->getLeftChild(), n, child);
        }
        else {
            return *n + getNode(head->getLeftChild(), n, child) + getNode(head->getRightChild(), n, child);
        }
    }
    if(n==0) {
        return 0;
    }
    /*
    if (*n == 0) {
        return head;
    }
    else {
        if (head->getLeftChild()) {
            *n = *n - 1;
            return getNode(head->getLeftChild(), n);
        }
        if (head->getRightChild()) {
            return getNode(head->getRightChild(), n);
        }
    }
    */
}