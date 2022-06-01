#ifndef FROZEN_INDIVIDUALS_H
#define FROZEN_INDIVIDUALS_H

#include <vector>
#include "Individual.h";

class FrozenIndividuals {
	public:
		FrozenIndividuals(int);
		void pushIndividual(Individual*);
		void pushImage(Image);
		std::vector<Image> getImages();
		int getNumImages();
		Individual* getIndividualAt(int);
		Image getImageAt(int);
		void changeGenes();
	private:
		std::vector<Individual> individuals;
		std::vector<Image> images;
		Genes* genes;
		int size;
		int n_inserted_elements;
};

#endif
