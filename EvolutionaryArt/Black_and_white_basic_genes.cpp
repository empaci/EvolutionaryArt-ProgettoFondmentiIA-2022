#include "Black_and_white_basic_genes.h"
#include <iostream>
#include <vector>

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

void Black_and_white_basic_genes::convertGenotypeToPhenotype(Individual* individual, Image& image) {
	char* image_header = nullptr;
	std::vector<std::vector<int>> phenotype(255, std::vector<int>(255));

	for (int i = 0; i < 255; i++) {
		for (int j = 0; j < 255; j++) {
			int r = 0;
			phenotype[i][j] = eval(i, j, individual->getGenotype(), &r)%255;
		}
	}

	image.setHeader(image_header);
	image.setPhenotype(phenotype);

	return;
}

int Black_and_white_basic_genes::eval(int x, int y, Node* head, int* res) {

	if (!head->isLeaf()) {
		if (head->getLeftChild() && !head->getRightChild()) {
			return *res + unaryOp(eval(x, y, head->getLeftChild(), res), head->getOperation());
		}
		if (head->getRightChild()) {
			return *res + binaryOp(eval(x, y, head->getLeftChild(), res), eval(x, y, head->getRightChild(), res), head->getOperation());
		}
	}
	else {
		if (head->getValue() != -1) {
			return head->getValue();
		}
		else {
			if (head->getVar()) {
				return x;
			}
			else {
				return y;
			}
		}
	}
}

int Black_and_white_basic_genes::unaryOp(int x, std::string operation) {
	if (operation == "sin") {
		return (int)sin(x);
	} else if (operation == "cos") {
		return (int)cos(x);
	} else if (operation == "sqrt") {
		return (int)sqrt(x);
	}
}

int Black_and_white_basic_genes::binaryOp(int x, int y, std::string operation) {
	if (operation == "+") {
		return (int) x+y;
	}
	else if (operation == "-") {
		return (int) sqrt(pow(x-y, 2));
	}
}