#include "Population.h"

Population::Population(int population_size, int depth, Genes* genes) {
	this->population_size = population_size;
	this->genes = genes;
	for (int i = 0; i < population_size; i++) {
		Individual ind = Individual(depth, genes);
		this->individuals.push_back(ind);
	}
}

void Population::setFitnessValues(std::vector<int> values) {
	for (int i = 0; i < this->individuals.size(); i++) {
		this->individuals[i].setFitnessValue(values[i]);
	}
	return;
}

void Population::evolve() {
	std::vector<Individual> parents = proportionalSelection(); //proportionaly select parents
	std::vector<Individual> childrens = recombination_and_mutation(parents); //crossover and mutations on new individuals
	//concat parent and children to form the new population
	std::vector<Individual> new_population;
	new_population.insert(new_population.end(), parents.begin(), parents.end());
	new_population.insert(new_population.end(), childrens.begin(), childrens.end());

	replacement(new_population); //sobtitute the old generation with the new one
	return;
}

std::vector<Individual> Population::proportionalSelection() {
	std::vector<Individual> parents;
	
	float total_fitness = 0;
	for (int i = 0; i < this->individuals.size(); i++) {
		total_fitness = total_fitness + this->individuals[i].getFitnessValue();
	}

	int probability = 0;
	int r = 1 + (std::rand() % (100));
	
	for (int i = 0; i < this->individuals.size(); i++) {

		probability = (this->individuals[i].getFitnessValue() / total_fitness) * 100;

		if (probability >= r) {
			parents.push_back(this->individuals[i]);
		}
		r = 1 + (std::rand() % (100));
	}
	return parents;
}

std::vector<Individual> Population::recombination_and_mutation(std::vector<Individual> parents) {
	std::vector<Individual> children;

	int r1, r2 = 0;

	while (this->population_size < parents.size() + children.size()) {
		r1 = std::rand() % (parents.size());
		r2 = std::rand() % (parents.size());
		while (r1 == r2) {
			r2 = std::rand() % (parents.size());
		}

		Individual* i1 = new Individual(parents[r1]);
		Individual* i2 = new Individual(parents[r2]);

		GeneticOperation::crossover(i1, i2);

		apply_random_mutation(i1);
		apply_random_mutation(i2);

		children.push_back(*i1);
		if (this->population_size < parents.size() + children.size()) {
			children.push_back(*i2);
		}
	}

	return children;
}

void Population::apply_random_mutation(Individual* i) {
	int r_mutation = std::rand() % 5;
	switch (r_mutation) {
	case 0:
		GeneticOperation::node_deletion(i);
		break;
	case 1:
		GeneticOperation::node_insertion(i, this->genes);
		break;
	case 2:
		GeneticOperation::node_mutation(i, this->genes);
		break;
	case 3:
		GeneticOperation::subtree_replacement(i, this->genes);
		break;
	case 4:
		GeneticOperation::subtree_swap(i);
		break;
	}
}

void Population::replacement(std::vector<Individual> population) {
	this->individuals = population;
}

void Population::saveImages() {
	std::string path = "..\\images\\";
	Image* image = new Image();
	for (int i = 0; i < this->individuals.size(); i++) {
		this->genes->convertGenotypeToPhenotype(&this->individuals[i], image);
		image->save(path + std::to_string(i));

	}
	return;
}
