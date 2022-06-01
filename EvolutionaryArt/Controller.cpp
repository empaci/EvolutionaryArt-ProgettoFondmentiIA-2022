#include "Controller.h"
#include "Black_and_white_basic_genes.h"
#include "Color_basic_genes.h"
#include "FrozenIndividuals.h"

Controller::Controller() {
	Genes* gene = new Black_and_white_basic_genes();
	//Genes* gene = new Color_basic_genes();
	//this->population = new Population(20, 4, gene);
}

Controller::Controller(int population_size, int depth, bool color) {
	srand(time(NULL));
	Genes* gene;
	this->color = color;
	if (color) {
		gene = new Color_basic_genes();
	}
	else {
		gene = new Black_and_white_basic_genes();
	}
	this->population = new Population(population_size, depth, gene);
	this->frozenIndividuals = new FrozenIndividuals(6);
}

bool Controller::getColor() {
	return this->color;
}

void Controller::changeGenes() {
	this->population->setGenes(new Color_basic_genes());
}

void Controller::evaluate(std::vector<int> fitness_values) {
	population->setFitnessValues(fitness_values);
	//select an image with a 10 rating, save it in the frozen attribute
	frozenIndividuals->pushIndividual(population->getRandomBestIndividual(&lastBestIndividual));
	if (lastBestIndividual != -1) {
		frozenIndividuals->pushImage(this->tempImages[lastBestIndividual]);
	}
	population->evolve();
}

std::vector<Image> Controller::generateImages() {
	this->tempImages =  this->population->saveImages();
	return this->tempImages;
}

std::vector<Image> Controller::getFrozenImages() {
	return this->frozenIndividuals->getImages();
}

int Controller::getNFrozenImages() {
	return this->frozenIndividuals->getNumImages();
}

void Controller::unfreeze(int posPopulation, int posFrozen) {
	this->population->setIndividualAt(posPopulation, this->frozenIndividuals->getIndividualAt(posFrozen));
	this->tempImages[posPopulation] = this->frozenIndividuals->getImageAt(posFrozen);
}

std::vector<Image> Controller::getTempImages() {
	return this->tempImages;
}