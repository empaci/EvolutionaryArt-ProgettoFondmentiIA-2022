#ifndef GENETIC_OPERATION_H
#define GENETIC_OPERATION_H

#include "Node.h"
#include "Genes.h"
#include "Individual.h"

class Genes;

class GeneticOperation {
	
	public:
		static Node* randomlyGenerateGenotype(int, Genes*, Node*);
		// recombination
		static void crossover(Individual*, Individual*);
		// mutation
		static void subtree_swap(Individual*);
		static void subtree_replacement(Individual*,Genes*);
		static void node_insertion(Individual*, Genes*);
		static void node_deletion(Individual*);
		static void node_mutation(Individual*, Genes*);

};
#endif
