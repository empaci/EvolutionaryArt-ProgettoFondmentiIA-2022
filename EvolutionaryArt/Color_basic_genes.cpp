#include "Color_basic_genes.h"
#include <iostream>
#include <vector>

Color_basic_genes::Color_basic_genes() {
	int len = 9;
	std::string* basic_genes_types = new std::string[len]{
		"sqrt",
		"+",
		"-",
		"sin",
		"cos",
		"xor",
		"/",
		"*",
		"tanh",
	};
	//tells if the operation, in the same position, is unary or binary
	int* n_argument_operation = new int[len] {
		1,
			2,
			2,
			1,
			1,
			2,
			2,
			2,
			1,
	};
	setNFunctionArguments(n_argument_operation, len);
	setGenes(basic_genes_types, len);
}

void Color_basic_genes::convertGenotypeToPhenotype(Individual* individual, Image* image) {
	int dim = 300*3;
	std::string header = { "P3" }; //gray scale image
	std::vector<int> info = { dim/3, dim/3, 80 }; // 255x255 image with color range between 0 and 254
	std::vector<std::vector<int>> phenotype(dim, std::vector<int>(dim));

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			int r = 0;
			phenotype[i][j] = this->eval(i, j, individual->getGenotype(), &r) % 80;
		}
	}

	image->setHeader(header);
	image->setInformation(info);
	image->setPhenotype(phenotype);

	return;
}

int Color_basic_genes::eval(int x, int y, Node* head, int* res) {

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

int Color_basic_genes::unaryOp(int x, std::string operation) {
	if (operation == "sin") {
		return (int)sin(x);
	}
	else if (operation == "cos") {
		return (int)cos(x);
	}
	else if (operation == "sqrt") {
		return (int)sqrt(x);
	}
	else if (operation == "tanh") {
		return (int)tanh(x);
	}
}

int Color_basic_genes::binaryOp(int x, int y, std::string operation) {
	if (operation == "+") {
		return (int)x + y;
	}
	else if (operation == "-") {
		return (int)sqrt(pow(x - y, 2));
	}
	else if (operation == "xor") {
		return (int)x ^ y;
	}
	else if (operation == "/") {
		if (y != 0) {
			return (int)x / y;
		}
		else {
			return x;
		}
	}
	else if (operation == "*") {
		return (int)x * y;
	}

}