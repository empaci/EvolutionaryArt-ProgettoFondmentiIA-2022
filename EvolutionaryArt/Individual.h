#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "GeneticOperation.h"

class Individual {
	private:
		Node* genotype;
		int fitness_value;

	public:
		Individual(int, Genes);
		void setFitnessValue(int);
		Node* getGenotype();
		std::string toString();
};


#endif
