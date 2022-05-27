#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Population.h"

class Controller {
	public:
		Controller();
		Controller(int, int);
		void generateImages();
	private:
		Population* population;

};

#endif

