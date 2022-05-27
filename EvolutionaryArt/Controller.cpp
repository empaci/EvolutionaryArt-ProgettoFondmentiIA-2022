#include "Controller.h"
#include "Black_and_white_basic_genes.h"

Controller::Controller() {
	Genes* gene = new Black_and_white_basic_genes();
	this->population = new Population(20, 4, gene);
}

Controller::Controller(int population_size, int depth) {
	Genes* gene = new Black_and_white_basic_genes();
	this->population = new Population(population_size, depth, gene);
}

void Controller::generateImages() {
	this->population->saveImages();
}