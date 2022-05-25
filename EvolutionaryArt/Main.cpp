#include <iostream>
#include "Individual.h"
#include "Genes.h"
#include "Black_and_white_basic_genes.h"
#include <time.h>

int main() {

	std::srand(time(NULL));
	//Color_basic_genes gene = Color_basic_genes();
	Black_and_white_basic_genes gene = Black_and_white_basic_genes();
	Individual i1 = Individual(4, &gene);
	Individual i2 = Individual(4, &gene);
	std::cout << "i1: " + i1.toString() + "\ni2: " + i2.toString() + "\n";
	//Node* n = new Node();
	//Node p = Node();
	//p.getRandomChild(i.getGenotype(), n);
	//GeneticOperation::subtree_replacement(&i1, &gene);
	//GeneticOperation::node_insertion(&i, &gene);
	//GeneticOperation::node_deletion(&i);
	//GeneticOperation::node_mutation(&i, &gene);
	//GeneticOperation::subtree_swap(&i);
	GeneticOperation::crossover(&i1, &i2);

	Image* image = new Image();
	gene.convertGenotypeToPhenotype(&i1, image);
	image->save("");

	std::cout << "i1: " + i1.toString() + "\ni2: " + i2.toString() + "\n";
	//char* image = gene.convertGenotypeToPhenotype(i);
}