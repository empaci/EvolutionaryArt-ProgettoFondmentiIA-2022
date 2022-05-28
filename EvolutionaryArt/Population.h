#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "Individual.h"
#include "image.h"

class Population {
	private:
		std::vector<Individual> individuals;
		int population_size;
		Genes* genes;
	public:
		Population(int, int, Genes*);
		void setFitnessValues(std::vector<int>);
		void evolve();
		std::vector<Individual> proportionalSelection(int, int);
		std::vector<float> generateProbabilities(int, int);
		Individual* getRandomIndividualWithFitness(int fitness);
		std::vector<Individual> recombination_and_mutation(std::vector<Individual>);
		void apply_random_mutation(Individual*);
		void replacement(std::vector<Individual>);
		void saveImages();
};

#endif
