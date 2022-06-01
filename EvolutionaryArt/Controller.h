#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Population.h"
#include "FrozenIndividuals.h"

class Controller {
	public:
		Controller();
		Controller(int, int, bool);
		bool getColor();
		void changeGenes();
		std::vector<Image> generateImages();
		void evaluate(std::vector<int>);
		std::vector<Image> getFrozenImages();
		int getNFrozenImages();
		void unfreeze(int, int);
		std::vector<Image> getTempImages();
	private:
		Population* population;
		FrozenIndividuals* frozenIndividuals;
		bool color;
		int lastBestIndividual;
		std::vector<Image> tempImages;

};

#endif

