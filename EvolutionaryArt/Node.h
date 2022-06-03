#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <iterator>
#include <string>
#include <vector>

class Node{ 
    private:
        std::string operation;
        bool var;
        std::vector<int> value;
        Node* left;
        Node* right;

    public:
        Node();
        void setOperation(std::string);
        std::string getOperation();
        void setVar(bool);
        bool getVar();
        void setValues(int, int, int);
        int getValue();
        int getValueAt(int);
        std::vector<int> getValues();
        bool isLeaf();

        void setLeftChildren(Node*);
        Node* getLeftChild();
        Node* getRightChild();
        void setRightChildren(Node*);
        
        std::string toString();
        
        static int getNumberOfParents(Node*, int*);
        static int getNumberOfParentsAux(Node*, int*);
        static int getNode(Node*, int*, Node*);
        static void getRandomChild(Node*, Node*);
        static int sobstituteBranch(Node*, Node*, int*);
        static int crossBranch(Node*, Node*, int*);
        static int crossBranchAux(Node*, Node*, Node*, int*, char);
        static int insertNode(Node*, Node*, int*);
        static int deleteNode(Node*, int*);
        static int deleteNodeAux(Node*, Node*, int*, char);
        static int sobstituteNode(Node*, Node*, Node*, int*);
        static int sobstituteNodeAux(Node*, Node*, Node*, int*, char, Node*);
        static int swapSubtree(Node*, int*, int*);
        static int swapSubtreeAux(Node*, int*, int*, Node*, char, char*, Node*, char, char*);
        static bool isSwappable(Node*, int, int);

        static void copyTree(Node*, Node*);
        static Node* cloneNode(Node*);
        static void cleanUp(Node*);
};

#endif
