#include "Node.h"
#include <iostream>


Node::Node() {
    this->value = { -1, -1, -1 };
    this->var = false;
    this->right = nullptr;
    this->left = nullptr;
}

void Node::setOperation(std::string operation) {
    this->operation = operation;
}

std::string Node::getOperation() {
    return this->operation;
}

void Node::setVar(bool var) {
    if (isLeaf()) {
        this->var = var;
    }
}

bool Node::getVar() {
    return this->var;
}

void Node::setValues(int r, int g, int b) {
    if (isLeaf()) {
        this->value[0] = r;
        this->value[1] = g;
        this->value[2] = b;
    }
}

int Node::getValue() {
    return this->value[0];
}

int Node::getValueAt(int p) {
    return this->value[p];
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
        if (this->value[0] != -1) {
            return std::to_string(value[0]) + ",";
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
            return getNumberOfParentsAux(head->getLeftChild(), n) + getNumberOfParentsAux(head->getRightChild(), n);
        }
    }
    else {
        return 0;
    }
}

//return node in position n; using depth first numbering
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
    else {
        return 0;
    }
}

int Node::sobstituteBranch(Node* head, Node* tree, int* n) {
    if (!head->isLeaf()) {

        *n = *n - 1;
        if (*n == 0) {
            head->setLeftChildren(tree);
            return -1;
        }

        if (head->getLeftChild() && !head->getRightChild()) {
            return *n + sobstituteBranch(head->getLeftChild(), tree, n);
        }
        else {
            return *n + sobstituteBranch(head->getLeftChild(), tree, n) + sobstituteBranch(head->getRightChild(), tree, n);
        }
    }
    if (n == 0) {
        return 0;
    }
}

int Node::crossBranch(Node* head, Node* tree, int* n) {
    if (!head->isLeaf()) {
        return crossBranchAux(head, tree, nullptr, n, 'l');
    }
    else {
        return 0;
    }
}

int Node::crossBranchAux(Node* head, Node* tree, Node* parent, int* n, char l_or_r) {
    if (!head->isLeaf()) {

        *n = *n - 1;
        if (*n == 0) {
            //use of a character to know if we need to remove the right or left side of the tree from the parent
            if (parent) {
                if (l_or_r == 'l') {
                    parent->setLeftChildren(tree);
                }
                else if (l_or_r == 'r') {
                    parent->setRightChildren(tree);
                }
            }
            return -1;
        }

        if (head->getLeftChild() && !head->getRightChild()) {
            return *n + crossBranchAux(head->getLeftChild(), tree, head, n, 'l');
        }
        else {
            return *n + crossBranchAux(head->getLeftChild(), tree, head, n, 'l') + crossBranchAux(head->getRightChild(), tree, head, n, 'r');
        }
    }
    else {
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
    else {
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
            if (parent) {
                if (l_or_r == 'l') {
                    parent->setLeftChildren(head->getLeftChild());
                }
                else if (l_or_r == 'r') {
                    parent->setRightChildren(head->getLeftChild());
                }
                if (head->getRightChild()) {
                    cleanUp(head->getRightChild()); //delete the whole tree on the right
                }
                delete(head);
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
    else {
        return 0;
    }
}

int Node::sobstituteNode(Node* head, Node* unaryElement, Node* binaryElement, int* n) {
    if (!head->isLeaf()) {
        return sobstituteNodeAux(head, unaryElement, binaryElement, n, 'l', head);
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
    else {
        return 0;
    }
}

int Node::swapSubtree(Node* head, int* n1, int* n2) {
    if (!head->isLeaf()) {
        return swapSubtreeAux(head, n1, n2, nullptr, 'l', new char('l'), nullptr, 'l', new char('l'));
    }
    else {
        return 0;
    }
}

//when the node is found in pos n1 or n2 the parent is returned and is "locked" if the searched node is a left or right child
int Node::swapSubtreeAux(Node* head, int* n1, int* n2, Node* parent1, char l_or_r1, char* locked_l_or_r1, Node* parent2, char l_or_r2, char* locked_l_or_r2) {
    if (!head->isLeaf()) {

        *n1 = *n1 - 1;
        if (*n1 == 0) {
            locked_l_or_r1 = new char(l_or_r1);
        }
        else if (*n1 > 0) {
            parent1 = head;
        }
        *n2 = *n2 - 1;
        if (*n2 == 0) {
            locked_l_or_r2 = new char(l_or_r2);
        }
        else if (*n2 > 0) {
            parent2 = head;
        }
        if (*n1 <= 0 && *n2 <= 0) {
            Node temp = *parent1;
            if (*locked_l_or_r1 == 'l' && *locked_l_or_r2 == 'l') {
                parent1->setLeftChildren(parent2->getLeftChild());
            }
            if (*locked_l_or_r1 == 'l' && *locked_l_or_r2 == 'r') {
                parent1->setLeftChildren(parent2->getRightChild());
            }
            if (*locked_l_or_r1 == 'r' && *locked_l_or_r2 == 'l') {
                parent1->setRightChildren(parent2->getLeftChild());
            }
            if (*locked_l_or_r1 == 'r' && *locked_l_or_r2 == 'r') {
                parent1->setRightChildren(parent2->getRightChild());
            }

            if (*locked_l_or_r1 == 'l' && *locked_l_or_r2 == 'l') {
                parent2->setLeftChildren(temp.getLeftChild());
            }
            if (*locked_l_or_r1 == 'r' && *locked_l_or_r2 == 'l') {
                parent2->setLeftChildren(temp.getRightChild());
            }
            if (*locked_l_or_r1 == 'l' && *locked_l_or_r2 == 'r') {
                parent2->setRightChildren(temp.getLeftChild());
            }
            if (*locked_l_or_r1 == 'r' && *locked_l_or_r2 == 'r') {
                parent2->setRightChildren(temp.getRightChild());
            }
            return -1;
        }
        if (head->getLeftChild() && !head->getRightChild()) {
            return *n1 + swapSubtreeAux(head->getLeftChild(), n1, n2, parent1, 'l', locked_l_or_r1, parent2, 'l', locked_l_or_r2);
        }
        else {
            return *n1 + swapSubtreeAux(head->getLeftChild(), n1, n2, parent1, 'l', locked_l_or_r1, parent2, 'l', locked_l_or_r2) + swapSubtreeAux(head->getRightChild(), n1, n2, parent1, 'r', locked_l_or_r1, parent2, 'r', locked_l_or_r2);
        }
    }
    else {
        return 0;
    }
}

bool Node::isSwappable(Node* head, int r1, int r2) {
    return true;
}

//copy of a tree given the head
void Node::copyTree(Node* head, Node* copy) {
    if (head) {
        Node* leftNode = cloneNode(head->getLeftChild());
        copy->setLeftChildren(leftNode);
        copyTree(head->getLeftChild(), copy->getLeftChild());
        
        if (head->getRightChild()) {
            Node* rightNode = cloneNode(head->getRightChild());
            copy->setRightChildren(rightNode);
            copyTree(head->getRightChild(), copy->getRightChild());
        }
    }
}

Node* Node::cloneNode(Node* node) {
    if (node) {
        Node* clone = new Node();
        clone->setValues(node->getValueAt(0), node->getValueAt(1), node->getValueAt(2));
        clone->setOperation(node->getOperation());
        clone->setVar(node->getVar());
        return clone;
    }
    else {
        return nullptr;
    }
}

void Node::cleanUp(Node* head) {
    if (head->getLeftChild()) {
        cleanUp(head->getLeftChild());
    }
    if (head->getRightChild()) {
        cleanUp(head->getRightChild());
    }
    if (!head->getLeftChild() && !head->getRightChild()) {
        delete(head);
    }
}