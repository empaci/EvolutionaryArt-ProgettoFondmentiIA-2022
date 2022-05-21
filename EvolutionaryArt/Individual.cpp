#include "Individual.h"


Individual::Individual(int seed, int depth) {
	genotype = GeneticOperation::randomlyGenerateGenotype(seed, depth);
	fitness_value = -1; // -1 is not a valid number; the range is [1,10]
}

void Individual::setFitnessValue(int fitness_value) {
	this->fitness_value = fitness_value;
}

Node* Individual::getGenotype() {
	return genotype;
}

std::string Individual::toString() {
	return genotype->toString();
}

