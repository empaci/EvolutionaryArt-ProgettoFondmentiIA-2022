#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "GeneticOperation.h"

class Individual {
	private:
		Node* genotype;
		int fitness_value;

	public:
		Individual(int, Genes*);
		Individual(Individual*);
		void setFitnessValue(int);
		int getFitnessValue();
		Node* getGenotype();
		std::string toString();
};


#endif
