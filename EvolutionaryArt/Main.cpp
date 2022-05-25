#include <iostream>
#include "Individual.h"
#include "Genes.h"
#include "Color_basic_genes.h"

int main() {

	std::srand(421);
	Color_basic_genes gene = Color_basic_genes();
	Individual i1 = Individual(4, &gene);
	Individual i2 = Individual(4, &gene);
	std::cout << "i1: " + i1.toString() + "\ni2: " + i2.toString() + "\n";
	//Node* n = new Node();
	//Node p = Node();
	//p.getRandomChild(i.getGenotype(), n);
	//GeneticOperation::subtree_replacement(&i, gene);
	//GeneticOperation::node_insertion(&i, gene);
	//GeneticOperation::node_deletion(&i);
	//GeneticOperation::node_mutation(&i, gene);
	//GeneticOperation::subtree_swap(&i);
	GeneticOperation::crossover(&i1, &i2);

	Image* image = new Image();
	gene.convertGenotypeToPhenotype(&i1, image);
	image->save("lol");

	std::cout << "i1: " + i1.toString() + "\ni2: " + i2.toString() + "\n";
	//char* image = gene.convertGenotypeToPhenotype(i);
}