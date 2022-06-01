#include "FrozenIndividuals.h"
#include "Color_basic_genes.h"
#include "Black_and_white_basic_genes.h"

FrozenIndividuals::FrozenIndividuals(int size) {
	this->size = size;
	this->n_inserted_elements = 0;
	this->genes = new Black_and_white_basic_genes();
}

void FrozenIndividuals::pushIndividual(Individual* i) {
	if (i) {
		if (this->individuals.size() == size) {
			this->individuals[n_inserted_elements % 6] = new Individual(i);
		}
		else {
			this->individuals.push_back(new Individual(i));
		}
		n_inserted_elements++;
	}
}

void FrozenIndividuals::pushImage(Image img) {
	if (this->images.size() == size) {
		this->images[(n_inserted_elements-1) % 6] = img; //-1 because the individual should be always added before the image
	}
	else {
		this->images.push_back(img);
	}
}

int FrozenIndividuals::getNumImages() {
	return this->individuals.size();
}

void FrozenIndividuals::changeGenes() {
	genes = new Color_basic_genes();
}

std::vector<Image> FrozenIndividuals::getImages() {
	std::string path = "..\\FrozenImages\\";
	for (int i = 0; i < this->individuals.size(); i++) {
		this->images[i].save(path + std::to_string(i));
	}
	return this->images;
}