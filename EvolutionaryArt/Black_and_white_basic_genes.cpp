#include "Black_and_white_basic_genes.h"
#include <iostream>
#include <vector>

Black_and_white_basic_genes::Black_and_white_basic_genes() {
}

void Black_and_white_basic_genes::convertGenotypeToPhenotype(Individual* individual, Image* image) {
	std::string header = { "P2" }; //gray scale image
	std::vector<int> info = { dim, dim, 255 }; // 255x255 image with color range between 0 and 254
	std::vector<std::vector<int>> phenotype(dim, std::vector<int>(dim));

	/*
	std::vector<std::string> stack;
	stackOperations(individual->getGenotype(), &stack);

	int size = stack.size();
	*/
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			int r = 0;
			//phenotype[i][j] = this->eval(i, j, &size, stack, &r)%50;
			phenotype[i][j] = ((unsigned int)(this->eval(i, j, individual->getGenotype())) % 255);
		}
	}
	
	image->setHeader(header);
	image->setInformation(info);
	image->setPhenotype(phenotype);

	return;
}

/*
void Black_and_white_basic_genes::stackOperations(Node* head, std::vector<std::string>* stack) {

	std::string sequentialOperations = std::string();
	sequentialOperations = postfixNode(head);

	std::string delimiter = "$";
	
	size_t pos = 0;
	std::string token;
	while ((pos = sequentialOperations.find(delimiter)) != std::string::npos) {
		token = sequentialOperations.substr(0, pos);
		if (!token.empty()) {
			stack->push_back(token);
		}
		sequentialOperations.erase(0, pos + delimiter.length());
	}
	return;
}

std::string Black_and_white_basic_genes::postfixNode(Node* head) {
	if (!head->isLeaf()) {
		if (head->getLeftChild() && !head->getRightChild()) {
			return head->getOperation() + "$" + postfixNode(head->getLeftChild()) + "$";
		}
		else if (head->getRightChild()) {
			return head->getOperation() + "$" + postfixNode(head->getLeftChild()) + "$" + postfixNode(head->getRightChild()) + "$";
		}
	}
	else {
		if (head->getValue() != -1) {
			return std::to_string(head->getValue());
		}
		else {
			if (head->getVar()) {
				return "x";
			}
			else {
				return "y";
			}
		}
	}
}
int Black_and_white_basic_genes::eval(int x, int y, int* size, std::vector<std::string> stack, int* res) {
	int pos = 0;
	return evalAux(x, y, size, &pos, stack, res, false);
}

int Black_and_white_basic_genes::evalAux(int x, int y, int* size, int* pos, std::vector<std::string> stack, int* res, bool right_op) {
	if (right_op) {
		*pos = *pos + 1;
	}
	if (*pos != *size-1) {
		int p = -1;
		for (int i = 0; i < this->getLen(); i++) {
			if (this->getGene(i) == stack[*pos]) {
				p = i;
				break;
			}
		}
		if (p >= 0) {
			*pos = *pos + 1;
			if (this->getNFunctionArgument(p) == 1) {
				return *res + unaryOp(evalAux(x, y, size, pos, stack, res, false), stack[*pos - 1]);
			}
			else {
				return *res + binaryOp(evalAux(x, y, size, pos, stack, res, false), evalAux(x, y, size, pos, stack, res, true), stack[*pos - 1]);
			}
		}
		else {
			if (stack[*pos] != "x" && stack[*pos] != "y") {
				return std::stoi(stack[*pos]);
			}
			else {
				if (stack[*pos] == "x") {
					return x;
				}
				else {
					return y;
				}
			}
		}
	}
	else {
		return 0;
	}
}
*/