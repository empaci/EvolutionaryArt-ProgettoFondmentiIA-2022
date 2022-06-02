#include "Controller.h"
#include "Black_and_white_basic_genes.h"
#include "Color_basic_genes.h"
#include "FrozenIndividuals.h"

Controller::Controller() {
	Genes* gene = new Black_and_white_basic_genes();
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

//Used to switch from black_and_whites to colored images
void Controller::changeGenes() {
	this->population->setGenes(new Color_basic_genes());
	this->frozenIndividuals->changeGenes();
}

void Controller::evaluate(std::vector<int> fitness_values) {
	population->setFitnessValues(fitness_values);
	//select an image with a 10 rating, save it in the frozen individuals
	frozenIndividuals->pushIndividual(population->getRandomBestIndividual(&lastBestIndividual));
	//since the images of the individuals are saved in the same position of a vector of the individual themselves we can use the same position.
	//the vector are the images are saved in the controller so we don't have to convert them again when they are added to the frozenIndividuals
	if (lastBestIndividual != -1) {
		frozenIndividuals->pushImage(this->tempImages[lastBestIndividual]);
	}
	population->evolve();
}

//use of a temporal array of images saved in the controller allow to trasfer images from/to the FrozenIndividuals without regenerating them
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