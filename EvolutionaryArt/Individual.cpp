#include "Individual.h"

Individual::Individual(int depth, Genes* genes) {
	genotype = new Node();
	GeneticOperation::randomlyGenerateGenotype(depth, genes, genotype);
	fitness_value = -1; // -1 is not a valid number; the range is [1,10]
}

void Individual::setFitnessValue(int fitness_value) {
	this->fitness_value = fitness_value;
}

int Individual::getFitnessValue() {
	return this->fitness_value;
}

Node* Individual::getGenotype() {
	return genotype;
}

std::string Individual::toString() {
	return "==========================\n Fitness value: " + std::to_string(this->fitness_value) + "\n" + genotype->toString();
}
