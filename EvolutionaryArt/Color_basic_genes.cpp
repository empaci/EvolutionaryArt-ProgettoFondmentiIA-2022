#include "Color_basic_genes.h"
#include <iostream>
#include <vector>

Color_basic_genes::Color_basic_genes() {
}

void Color_basic_genes::convertGenotypeToPhenotype(Individual* individual, Image* image) {
	std::string header = { "P3" }; //RGB scale image
	std::vector<int> info = { dim, dim, 255 }; // 255x255 image with color range between 0 and 254
	std::vector<std::vector<int>> phenotype(dim, std::vector<int>(dim*3));

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim*3; j++) {
			int r = 0;
			for (int k = 0; k < 3; k++) {
				phenotype[i][j+k] = (abs(this->eval(i, j, k, individual->getGenotype(), &r)) % 255);
			}
			j += 2;
		}
	}

	image->setHeader(header);
	image->setInformation(info);
	image->setPhenotype(phenotype);

	return;
}

int Color_basic_genes::eval(int x, int y, int c, Node* head, int* res) {

	if (!head->isLeaf()) {
		if (head->getLeftChild() && !head->getRightChild()) {
			return *res + unaryOp(eval(x, y, c, head->getLeftChild(), res), head->getOperation());
		}
		if (head->getRightChild()) {
			return *res + binaryOp(eval(x, y, c, head->getLeftChild(), res), eval(x, y, c, head->getRightChild(), res), head->getOperation());
		}
	}
	else {
		if (head->getValue() != -1) {
			return head->getValueAt(c);
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