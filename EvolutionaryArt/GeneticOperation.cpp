#include "GeneticOperation.h"


Node* GeneticOperation::randomlyGenerateGenotype(int seed, int depth) {
	Node n = Node();
	n.setValue(seed);
	return &n;
}