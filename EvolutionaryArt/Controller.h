#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Population.h"

class Controller {
	public:
		Controller();
		Controller(int, int, bool);
		bool getColor();
		void changeGenes();
		std::vector<Image> generateImages();
		void evaluate(std::vector<int>);
	private:
		Population* population;
		bool color;

};

#endif

