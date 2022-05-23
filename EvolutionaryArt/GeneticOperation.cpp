#include "GeneticOperation.h"


Node* GeneticOperation::randomlyGenerateGenotype(int depth, Genes genes, Node* head) {
	if (depth != 0) {
		//parent node; they have an operation (+, -, sin, sqrt, ...)
		int r = (std::rand() % (genes.getLen()));
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
		int r = (std::rand() % (2 + 1));
		
		if (r == 0) {
			int value = (std::rand() % (20 + 1));
			head->setValue(value); //the constant is a random number between 0 and 20
		}
		else {
			head->setVar(r==1); //true means x, false means y
		}
		return head;
	}
}

void GeneticOperation::subtree_replacement(Individual* individual, Genes genes) {
	Node* n = individual->getGenotype();
	int* n_node = new int();
	Node::getNumberOfParents(n, n_node);
	int r = (std::rand() % (*n_node));
	Node* new_tree = new Node();
	randomlyGenerateGenotype(2 + (std::rand() % 4), genes, new_tree);

	Node::sobstitute_branch(n, new_tree, &r); //given the node in pos r, sobstitute the branch with the new_tree
	return;
}

void GeneticOperation::node_insertion(Individual* individual, Genes genes) {
	Node* n = individual->getGenotype();
	int* n_node = new int();
	Node::getNumberOfParents(n, n_node);
	int r = (std::rand() % (*n_node));
	Node* new_element = new Node();
	
	int o = (std::rand() % (genes.getLen()));
	new_element->setOperation(genes.getGene(o));

	//if is a binary operator we need to create a random sideto the left
	if (genes.getNFunctionArgument(o) == 2) {
		Node* right_child = new Node();
		int r = (std::rand() % (2 + 1));

		randomlyGenerateGenotype(std::rand() % 4, genes, right_child);

		new_element->setRightChildren(right_child);
	}

	Node::insert(n, new_element, &r); //add the new element in positions r, always putting the rest of the tree on the left child
	return;
}

void GeneticOperation::node_deletion(Individual* individual) {
	Node* n = individual->getGenotype();
	int* n_node = new int();
	Node::getNumberOfParents(n, n_node);
	int r = (std::rand() % (*n_node));

	Node::delete(n, &r); //delete the element in the r position

	return;
}

void GeneticOperation::node_mutation(Individual* individual, Genes genes) {
	Node* n = individual->getGenotype();
	int* n_node = new int();
	Node::getNumberOfParents(n, n_node);
	int r = (std::rand() % (*n_node));

	//need to check if the sobstituted element is a unary or bianry operation
	//Node::sobstitute(n, element, &r); //sobstitute the element in the r position
	
	return;
}

void GeneticOperation::crossover(Individual* i1, Individual* i2) {
	return;
}