#include "Color_basic_genes.h"
#include <iostream>
#include <vector>

Color_basic_genes::Color_basic_genes() {
}

void Color_basic_genes::convertGenotypeToPhenotype(Individual* individual, Image* image) {
	std::string header = { "P3" }; //RGB scale image
	std::vector<int> info = { dim, dim, 255 }; // 255x255 image with color range between 0 and 254
	std::vector<std::vector<int>> phenotype(dim, std::vector<int>(dim * 3));

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			for (int k = j*3; k < (j*3)+3; k++) {
				phenotype[i][k] = ((unsigned int)(this->eval(i, j, k%3, individual->getGenotype())) % 255);
			}
		}
	}

	image->setHeader(header);
	image->setInformation(info);
	image->setPhenotype(phenotype);

	return;
}

//eval redefined to add parameter c: c goes from 0 to 2 and indicated the color to pick in the value array as it contains [RED; GREEN; BLUE] values
int Color_basic_genes::eval(int x, int y, int c, Node* head) {

	if (!head->isLeaf()) {
		if (head->getLeftChild() && !head->getRightChild()) {
			return unaryOp(eval(x, y, c, head->getLeftChild()), head->getOperation());
		}
		if (head->getRightChild()) {
			return binaryOp(eval(x, y, c, head->getLeftChild()), eval(x, y, c, head->getRightChild()), head->getOperation());
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