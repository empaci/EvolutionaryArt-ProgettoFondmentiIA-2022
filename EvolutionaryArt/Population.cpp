#include "Population.h"

Population::Population(int population_size, int depth, Genes* genes) {
	this->population_size = population_size;
	this->genes = genes;
	for (int i = 0; i < population_size; i++) {
		Individual ind = Individual(depth, genes);
		this->individuals.push_back(ind);
	}
}

void Population::setGenes(Genes* genes) {
	this->genes = genes;
}

void Population::setFitnessValues(std::vector<int> values) {
	for (int i = 0; i < this->individuals.size(); i++) {
		this->individuals[i].setFitnessValue(values[i]);
	}
	return;
}

void Population::evolve() {
	std::vector<Individual> parents = proportionalSelection(1, 10); //proportionaly select parents
	std::vector<Individual> childrens = recombination_and_mutation(parents); //crossover and mutations on new individuals
	//concat parent and children to form the new population
	std::vector<Individual> new_population;
	new_population.insert(new_population.end(), parents.begin(), parents.end());
	new_population.insert(new_population.end(), childrens.begin(), childrens.end());

	replacement(new_population); //sobtitute the old generation with the new one
	return;
}

std::vector<Individual> Population::proportionalSelection(int min, int max) {
	std::vector<Individual> parents;

	std::vector<float> probabilities = generateProbabilities(min, max);

	Individual* temp_individual = nullptr;

	float r = ((float)std::rand() / (RAND_MAX)); // generate number between 0 and 1
	
	//Choose number of parents
	while( parents.size() < population_size/3) {

		for (int j = min; j <= max; j++) {
			if (r < probabilities[j - min]) {
				temp_individual = getRandomIndividualWithFitness(j);
				if (temp_individual) {
					parents.push_back(*temp_individual);
				}
				break;
			}
		}
		r = ((float) std::rand() / (RAND_MAX));
	}
	return parents;
}

std::vector<float> Population::generateProbabilities(int min, int max) {
	std::vector<float> probabilities;
	float previous_probability = 0.0;
	float p = 0;
	float totalFitness = min;

	for (int i = min+1; i <= max; i++) {
		totalFitness = totalFitness + i;
	}

	for (int i = min; i <= max; i++) {
		p = (previous_probability + (i / totalFitness));
		probabilities.push_back(p);
		previous_probability = p;
	}
	return probabilities;
}

Individual* Population::getRandomIndividualWithFitness(int fitness) {
	int n = 0;

	for (int i = 0; i < this->individuals.size(); i++) {
		if (this->individuals[i].getFitnessValue() == fitness) {
			n = n + 1;
		}
	}
	if (n != 0) {
		int r = 1 + (std::rand() % n);
		n = 0;
		for (int i = 0; i < this->individuals.size(); i++) {
			if (this->individuals[i].getFitnessValue() == fitness) {
				n = n + 1;
				if (n == r) {
					Individual* rand_individual = new Individual(this->individuals[i]);
					this->individuals.erase(this->individuals.begin() + i);
					return rand_individual;
				}
			}
		}
	} else {
		return nullptr;
	}
}

std::vector<Individual> Population::recombination_and_mutation(std::vector<Individual> parents) {
	std::vector<Individual> children;

	int r1 = 0, r2 = 0;

	while (this->population_size > parents.size() + children.size()) {
		r1 = std::rand() % (parents.size());
		r2 = std::rand() % (parents.size());
		while (r1 == r2) {
			r2 = std::rand() % (parents.size());
		}

		Individual* i1 = new Individual(&parents[r1]);
		Individual* i2 = new Individual(&parents[r2]);

		GeneticOperation::crossover(i1, i2);

		if ((std::rand() / (RAND_MAX)) <= 0.4) {
			apply_random_mutation(i1); 
		}
		if (genotypeFilter(i1)) {
			children.push_back(*i1);
		}
		
		if (this->population_size > parents.size() + children.size()) {
			if ((std::rand() / (RAND_MAX)) <= 0.4) {
				apply_random_mutation(i2);
			}
			if (genotypeFilter(i2)) {
				children.push_back(*i2);
			}
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

bool Population::genotypeFilter(Individual i) {
	Node* root = i.getGenotype();
	return checkXandY(root);
}

bool Population::checkXandY(Node* head) {
	bool* thereIsX = new bool(false);
	bool* thereIsY = new bool(false);
	checkXandYAux(head, thereIsX, thereIsY);
	return (*thereIsX && *thereIsY);
}

void Population::checkXandYAux(Node* head, bool* thereIsX, bool* thereIsY) {
	if (head) {
		if (!head->isLeaf()) {
			checkXandYAux(head->getLeftChild(), thereIsX, thereIsY);
			if (head->getRightChild()) {
				checkXandYAux(head->getRightChild(), thereIsX, thereIsY);
			}
		} else{
			if (head->getVar()) {
				*thereIsX = true;
			}
			else if (!head->getVar() && head->getValue() == -1) {
				*thereIsY = true;
			}
		}
	}
}


void Population::replacement(std::vector<Individual> population) {
	this->individuals = population;
}

std::vector<Image> Population::saveImages() {
	std::string path = "..\\Images\\";
	std::vector<Image> images = std::vector<Image>();
	Image* image = new Image();
	for (int i = 0; i < this->individuals.size(); i++) {
		this->genes->convertGenotypeToPhenotype(&this->individuals[i], image);
		image->save(path + std::to_string(i));
		images.push_back(*image);
	}
	return images;
}

Individual* Population::getRandomBestIndividual(int* pos) {
	int n = 0;
	int fitness = 10;

	for (int i = 0; i < this->individuals.size(); i++) {
		if (this->individuals[i].getFitnessValue() == fitness) {
			n = n + 1;
		}
	}
	if (n != 0) {
		int r = 1 + (std::rand() % n);
		n = 0;
		for (int i = 0; i < this->individuals.size(); i++) {
			if (this->individuals[i].getFitnessValue() == fitness) {
				n = n + 1;
				if (n == r) {
					Individual* rand_individual = new Individual(this->individuals[i]);
					*pos = i;
					return rand_individual;
				}
			}
		}
	}
	else {
		*pos = -1;
		return nullptr;
	}
}

void Population::setIndividualAt(int pos, Individual* i) {
	this->individuals[pos] = new Individual(i);
}