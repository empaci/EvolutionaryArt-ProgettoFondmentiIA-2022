#include <iostream>
#include "Individual.h"

int main() {

	std::cout << " Hello World!\n";
	Individual i = Individual(420, 2);
	std::cout << i.toString();
}