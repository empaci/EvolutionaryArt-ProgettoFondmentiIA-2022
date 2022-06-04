#include "GeneticOperation.h"


Node* GeneticOperation::randomlyGenerateGenotype(int depth, Genes* genes, Node* head) {
	if (depth != 0) {
		//parent node; they have an operation (+, -, sin, sqrt, ...)
		int r = (std::rand() % ((*genes).getLen()));
		head->setOperation((*genes).getGene(r));
		
		Node* left_child = new Node();
		randomlyGenerateGenotype(depth - 1, genes, left_child);
		if ((*genes).getNFunctionArgument(r) == 2) {
			Node* right_child = new Node();
			randomlyGenerateGenotype(depth - 1, genes, right_child);
			head->setRightChildren(right_child);
		}
		head->setLeftChildren(left_child);
		return head;
	}
	else {
		//leaf nodes; they can have a constant, x and y
		int r = (std::rand() % 3);
		
		int red = 0;
		int green = 0;
		int blue = 0;

		if (r == 0) {
			red = (std::rand() % 101);
			green = (std::rand() % 101);
			blue = (std::rand() % 101);
			head->setValues(red, green, blue);
		} else {
			head->setVar(r==1); //true means x, false means y
		}
		return head;
	}
}

void GeneticOperation::subtree_replacement(Individual* individual, Genes* genes) {
	Node* n = individual->getGenotype();
	int n_node = 0;
	Node::getNumberOfParents(n, &n_node);
	int r = (std::rand() % n_node);
	Node* new_tree = new Node();
	randomlyGenerateGenotype(2 + (std::rand() % 4), genes, new_tree);

	Node::sobstituteBranch(n, new_tree, &r); //given the node in pos r, sobstitute the branch with the new_tree
	return;
}

void GeneticOperation::node_insertion(Individual* individual, Genes* genes) {
	Node* n = individual->getGenotype();
	int n_node = 0;
	Node::getNumberOfParents(n, &n_node);
	int r = (std::rand() % n_node);
	Node* new_element = new Node();
	
	int o = (std::rand() % ((*genes).getLen()));
	new_element->setOperation((*genes).getGene(o));

	//if is a binary operator we need to create a random child to the right
	if ((*genes).getNFunctionArgument(o) == 2) {
		Node* right_child = new Node();

		randomlyGenerateGenotype(std::rand() % 3, genes, right_child);

		new_element->setRightChildren(right_child);
	}

	Node::insertNode(n, new_element, &r); //add the new element in positions r, always putting the rest of the tree on the left child
	return;
}

void GeneticOperation::node_deletion(Individual* individual) {
	Node* n = individual->getGenotype();
	int n_node = 0;
	Node::getNumberOfParents(n, &n_node);
	if (n_node > 1) {
		int r = (std::rand() % n_node);

		Node::deleteNode(n, &r); //delete the element in the r position
	}
	return;
}

void GeneticOperation::node_mutation(Individual* individual, Genes* genes) {
	Node* n = individual->getGenotype();
	int n_node = 0;
	Node::getNumberOfParents(n, &n_node);
	int r = 1 + (std::rand() % n_node);
	int r_copy = r;
	Node* unaryElement = new Node();
	Node* binaryElement = new Node();

	int o = (std::rand() % ((*genes).getLen()));
	while ((*genes).getNFunctionArgument(o) != 2) {
		o = (std::rand() % ((*genes).getLen()));
	}
	binaryElement->setOperation((*genes).getGene(o));
	while ((*genes).getNFunctionArgument(o) != 1) {
		o = (std::rand() % ((*genes).getLen()));
	}
	unaryElement->setOperation((*genes).getGene(o));

	//give both a unary and a binary operations, than is changed accordingly with the node original operator 
	Node::sobstituteNode(n, unaryElement, binaryElement, &r); //sobstitute the element in the r position
	
	return;
}

void GeneticOperation::subtree_swap(Individual* individual) {
	Node* n = individual->getGenotype();
	int n_node = 0;
	Node::getNumberOfParents(n, &n_node);
	if (n_node > 3) {
		int r1 = 2 + (std::rand() % (n_node - 2));
		int r2 = 2 + (std::rand() % (n_node - 2));
		//can't swap if one is a sub-tree of the other
		//while (!Node::isSwappable(n, r1, r2)) {
			while (r1 == r2) {
				r2 = 2 + (std::rand() % (n_node - 2));
			}
		//}

		Node::swapSubtree(n, &r2, &r1); //put subtree1 in pos r1, and subtree2 in position r2
	}
	return;
}

void GeneticOperation::crossover(Individual* i1, Individual* i2) {
	Node* n1 = i1->getGenotype();
	int n_node1 = 0;
	Node::getNumberOfParents(n1, &n_node1);
	int r1 = 1 + (std::rand() % n_node1);
	Node* subtree1 = new Node();
	Node* copy_subtree1 = new Node();
	int r1_copy = r1;
	Node::getNode(n1, &r1_copy, subtree1);
	Node::copyTree(subtree1, copy_subtree1);

	Node* n2 = i2->getGenotype();
	int n_node2 = 0;
	Node::getNumberOfParents(n2, &n_node2);
	int r2 = 1 + (std::rand() % n_node2);
	Node* subtree2 = new Node();
	Node* copy_subtree2 = new Node();
	int r2_copy = r2;
	Node::getNode(n2, &r2_copy, subtree2);
	Node::copyTree(subtree2, copy_subtree2);

	//if both are 1 wouldn't make sense to swap them, so each tree is appended on the left of the other
	if (r1 == 1 && r2 == 1) {
		Node::sobstituteBranch(n1, copy_subtree2, &r1);
		Node::sobstituteBranch(n2, copy_subtree1, &r2);
	}
	else {

		Node::crossBranch(n1, copy_subtree2, &r1);
		Node::crossBranch(n2, copy_subtree1, &r2);
	}

	return;
}