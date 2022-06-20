#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <algorithm>
#include "Individual.h"
#include "image.h"

class Population {
	private:
		std::vector<Individual> individuals;
		int population_size;
		Genes* genes;

		void checkXandYAux(Node*, bool*, bool*);
	public:
		Population(int, int, Genes*);
		void setGenes(Genes*);
		void setFitnessValues(std::vector<int>);
		void evolve();
		std::vector<Individual> proportionalSelection(int, int);
		std::vector<float> generateProbabilities(int, int);
		Individual* getRandomIndividualWithFitness(int fitness);
		std::vector<Individual> recombination_and_mutation(std::vector<Individual>);
		void apply_random_mutation(Individual*);
		bool genotypeFilter(Individual);
		bool checkXandY(Node*);
		void replacement(std::vector<Individual>);
		std::vector<Image> saveImages();
		Individual* getRandomBestIndividual(int*);
		void setIndividualAt(int, Individual*);
};

#endif
