#include "Black_and_white_basic_genes.h"
#include <iostream>

Black_and_white_basic_genes::Black_and_white_basic_genes() {
	int len = 5;
	std::string* basic_genes_types = new std::string[len]{
		"sqrt",
		"+",
		"-",
		"sin",
		"cos",
	};
	//tells if the operation, in the same position, is unary or binary
	int* n_argument_operation = new int[len] {
		1,
		2,
		2,
		1,
		1,
	};
	setNFunctionArguments(n_argument_operation, len);
	setGenes(basic_genes_types, len);
}

char* Black_and_white_basic_genes::convertGenotypeToPhenotype(Individual individual) {
	return NULL;
}