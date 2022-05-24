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
        *randomChild = *(n->getLeftChild()); /***************************/
    } else {
        *randomChild = *(n->getRightChild()); /***************************/
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
            *child = *head; /***************************/
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
}

int Node::sobstitute_branch(Node* head, Node* tree, int* n) {
    if (!head->isLeaf()) {

        *n = *n - 1;
        if (*n == 0) {
            head->setLeftChildren(tree);
            return -1;
        }

        if (head->getLeftChild() && !head->getRightChild()) {
            return *n + sobstitute_branch(head->getLeftChild(), tree, n);
        }
        else {
            return *n + sobstitute_branch(head->getLeftChild(), tree, n) + sobstitute_branch(head->getRightChild(), tree, n);
        }
    }
    if (n == 0) {
        return 0;
    }
}

int Node::insertNode(Node* head, Node* element, int* n) {
    if (!head->isLeaf()) {

        *n = *n - 1;
        if (*n == 0) {
            element->setLeftChildren(head->getLeftChild());
            head->setLeftChildren(element);
            return -1;
        }

        if (head->getLeftChild() && !head->getRightChild()) {
            return *n + insertNode(head->getLeftChild(), element, n);
        }
        else {
            return *n + insertNode(head->getLeftChild(), element, n) + insertNode(head->getRightChild(), element, n);
        }
    }
    if (n == 0) {
        return 0;
    }
}

int Node::deleteNode(Node* head, int* n) {
    if (!head->isLeaf()) {
        return deleteNodeAux(head, nullptr, n, 'l');
    }
    else {
        return 0;
    }
}

int Node::deleteNodeAux(Node* head, Node* parent, int* n, char l_or_r) {
    if (!head->isLeaf()) {

        *n = *n - 1;
        if (*n == 0) {
            //use of a character to know if we need to remove the right or left side of the tree from the parent
            if (l_or_r == 'l') {
                parent->setLeftChildren(head->getLeftChild());
            }
            else if (l_or_r == 'r') {
                parent->setRightChildren(head->getLeftChild());
            }
            return -1;
        }

        if (head->getLeftChild() && !head->getRightChild()) {
            return *n + deleteNodeAux(head->getLeftChild(), head, n, 'l');
        }
        else {
            return *n + deleteNodeAux(head->getLeftChild(), head, n, 'l') + deleteNodeAux(head->getRightChild(), head, n, 'r');
        }
    }
    if (n == 0) {
        return 0;
    }
}

int Node::sobstituteNode(Node* head, Node* unaryElement, Node* binaryElement, int* n) {
    if (!head->isLeaf()) {
        return sobstituteNodeAux(head, unaryElement, binaryElement, n, 'l', nullptr);
    }
    else {
        return 0;
    }
}

int Node::sobstituteNodeAux(Node* head, Node* unaryElement, Node* binaryElement, int* n, char l_or_r, Node* parent) {
    if (!head->isLeaf()) {

        *n = *n - 1;
        if (*n == 0) {
            //use of a character to know if we need to remove the right or left side of the tree from the parent
            if (head->getRightChild()) {
                //is a binary element
                binaryElement->setLeftChildren(head->getLeftChild());
                binaryElement->setRightChildren(head->getRightChild());
                if (l_or_r == 'l') {
                    parent->setLeftChildren(binaryElement);
                }
                else if (l_or_r == 'r') {
                    parent->setRightChildren(binaryElement);
                }
            }
            else {
                //unary element
                unaryElement->setLeftChildren(head->getLeftChild());
                if (l_or_r == 'l') {
                    parent->setLeftChildren(unaryElement);
                }
                else if (l_or_r == 'r') {
                    parent->setRightChildren(unaryElement);
                }
            }
            return -1;
        }

        if (head->getLeftChild() && !head->getRightChild()) {
            return *n + sobstituteNodeAux(head->getLeftChild(), unaryElement, binaryElement, n, 'l', head);
        }
        else {
            return *n + sobstituteNodeAux(head->getLeftChild(), unaryElement, binaryElement, n, 'l', head) + sobstituteNodeAux(head->getRightChild(), unaryElement, binaryElement, n, 'r', head);
        }
    }
    if (n == 0) {
        return 0;
    }
}