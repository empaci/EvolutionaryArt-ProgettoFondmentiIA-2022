#include <iostream>
#include "Individual.h"
#include "Genes.h"
#include "Black_and_white_basic_genes.h"

int main() {

	std::cout << " Hello World!\n";
	std::srand(420);
	Genes gene = Black_and_white_basic_genes();
	Individual i = Individual(4, gene);
	std::cout << i.toString();
	//Node* n = new Node();
	//Node p = Node();
	//p.getRandomChild(i.getGenotype(), n);
	//GeneticOperation::subtree_replacement(&i, gene);
	//GeneticOperation::node_insertion(&i, gene);
	//GeneticOperation::node_deletion(&i);
	GeneticOperation::node_mutation(&i, gene);
	std::cout << i.toString();
	//char* image = gene.convertGenotypeToPhenotype(i);
}