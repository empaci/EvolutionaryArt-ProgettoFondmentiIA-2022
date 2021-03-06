#include "FrozenIndividuals.h"
#include "Color_basic_genes.h"
#include "Black_and_white_basic_genes.h"

FrozenIndividuals::FrozenIndividuals(int size) {
	this->size = size;
	this->n_inserted_elements = 0;
	this->genes = new Black_and_white_basic_genes();
	std::string path = "..\\FrozenImages\\";
}

void FrozenIndividuals::pushIndividual(Individual* i) {
	if (i) {
		//an element is added at the bottom, if the array is full then overwrite the oldest inserted element
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

std::vector<Image> FrozenIndividuals::changeGenes() {
	delete(genes);
	this->genes = new Color_basic_genes();
	this->images.clear();
	path = "..\\FrozenImages\\";
	Image* image = new Image();
	for (int i = 0; i < this->individuals.size(); i++) {
		this->genes->convertGenotypeToPhenotype(&this->individuals[i], image);
		image->save(path + std::to_string(i));
		this->images.push_back(*image);
	}
	return this->images;
}

std::vector<Image> FrozenIndividuals::getImages() {
	path = "..\\FrozenImages\\";
	for (int i = 0; i < this->individuals.size(); i++) {
		this->images[i].save(path + std::to_string(i));
	}
	return this->images;
}

Image FrozenIndividuals::getImageAt(int pos) {
	return this->images[pos];
}

Individual* FrozenIndividuals::getIndividualAt(int pos) {
	return &(this->individuals[pos]);
}