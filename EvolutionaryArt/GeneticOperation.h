#ifndef GENETIC_OPERATION_H
#define GENETIC_OPERATION_H

#include "Node.h"
#include "Genes.h"

class GeneticOperation {
	
	public:
		static Node* randomlyGenerateGenotype(int, Genes, Node*);
};
#endif
