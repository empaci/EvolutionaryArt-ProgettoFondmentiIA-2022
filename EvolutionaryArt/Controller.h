#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Population.h"

class Controller {
	public:
		Controller();
		Controller(int, int);
		std::vector<Image> generateImages();
		void evaluate(std::vector<int>);
	private:
		Population* population;

};

#endif

