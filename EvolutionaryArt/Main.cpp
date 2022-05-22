#include <iostream>
#include "Individual.h"
#include "Genes.h"
#include "Black_and_white_basic_genes.h"

int main() {

	std::cout << " Hello World!\n";
	std::srand(420);
	Genes gene = Black_and_white_basic_genes();
	Individual i = Individual(6, gene);
	std::cout << i.toString();
}