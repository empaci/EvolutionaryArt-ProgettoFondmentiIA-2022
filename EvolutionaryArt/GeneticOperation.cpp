#include "GeneticOperation.h"
#include <iostream>


Node* GeneticOperation::randomlyGenerateGenotype(int depth, Genes genes, Node* head) {

	if (depth != 0) {
		//parent node; they have an operation (+, -, sin, sqrt, ...)
		int r = (std::rand() % (genes.getLen()+1));
		head->setOperation(genes.getGene(r));
		
		Node* left_child = new Node();
		randomlyGenerateGenotype(depth - 1, genes, left_child);
		if (genes.getNFunctionArgument(r) == 2) {
			Node* right_child = new Node();
			randomlyGenerateGenotype(depth - 1, genes, right_child);
			head->setRightChildren(right_child);
		}
		head->setLeftChildren(left_child);
		return head;
	}
	else {
		//leaf nodes; they can have a constant, x and y
		int r = std::rand() % (2 + 1);
		if (r == 0) {
			head->setValue(std::rand() % (20 + 1)); //the consatnt is a random number between 0 and 20
		}
		else {
			head->setVar(r == 1); //true means x, false means y
		}
		return head;
	}
}