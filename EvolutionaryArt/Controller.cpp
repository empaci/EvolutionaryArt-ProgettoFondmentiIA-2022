#include "Controller.h"
#include "Black_and_white_basic_genes.h"
//#include "Color_basic_genes.h"

Controller::Controller() {
	Genes* gene = new Black_and_white_basic_genes();
	//Genes* gene = new Color_basic_genes();
	this->population = new Population(20, 4, gene);
}

Controller::Controller(int population_size, int depth) {
	srand(time(NULL));
	Genes* gene = new Black_and_white_basic_genes();
	//Genes* gene = new Color_basic_genes();
	this->population = new Population(population_size, depth, gene);
}

void Controller::evaluate(std::vector<int> fitness_values) {
	population->setFitnessValues(fitness_values);
	population->evolve();
}

void Controller::generateImages() {
	this->population->saveImages();
}