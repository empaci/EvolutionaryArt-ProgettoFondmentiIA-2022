#include "Controller.h"
#include "Black_and_white_basic_genes.h"
#include "Color_basic_genes.h"

Controller::Controller() {
	Genes* gene = new Black_and_white_basic_genes();
	//Genes* gene = new Color_basic_genes();
	this->population = new Population(20, 4, gene);
}

Controller::Controller(int population_size, int depth, bool color) {
	srand(time(NULL));
	Genes* gene;
	if (color) {
		gene = new Color_basic_genes();
	}
	else {
		gene = new Black_and_white_basic_genes();
	}
	this->population = new Population(population_size, depth, gene);
}

void Controller::evaluate(std::vector<int> fitness_values) {
	population->setFitnessValues(fitness_values);
	population->evolve();
}

std::vector<Image> Controller::generateImages() {
	return this->population->saveImages();
}