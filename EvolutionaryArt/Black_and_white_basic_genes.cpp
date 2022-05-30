#include "Black_and_white_basic_genes.h"
#include <iostream>
#include <vector>

Black_and_white_basic_genes::Black_and_white_basic_genes() {
	int len = 18;
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
		"pow",
		"log",
		"hypot",
		"gamma",
		"max",
		"min",
		"and",
		"or",
		"not",
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
		2,
		1,
		2,
		1,
		2,
		2,
		2,
		2,
		1,
	};
	setNFunctionArguments(n_argument_operation, len);
	setGenes(basic_genes_types, len);
}

void Black_and_white_basic_genes::convertGenotypeToPhenotype(Individual* individual, Image* image) {
	int dim = 200;
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
			phenotype[i][j] = (abs(this->eval(i, j, individual->getGenotype(), &r)) % 255);
		}
	}
	/*
	//max: NOTE:this elimanet all balck images that would have a value, but also eliminate images with dark tones
	int max = 0;
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			if (phenotype[i][j] > max) {
				max = phenotype[i][j];
			}
		}
	}

	std::vector<int> info = { dim, dim, max + 10 };
	*/
	image->setHeader(header);
	image->setInformation(info);
	image->setPhenotype(phenotype);

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

int Black_and_white_basic_genes::unaryOp(int x, std::string operation) {
	if (operation == "sin") {
		return (int) (sin(x)*100);
	} else if (operation == "cos") {
		return (int) (cos(x)*100);
	} else if (operation == "sqrt") {
		if (x > 0) {
			return (int)sqrt(x);
		} else {
			return x;
		}
	} else if (operation == "tanh") {
		return (int) (tanh(x)*100);
	} else if (operation == "log") {
		if (x > 0) {
			return (int)(log(x) * 100);
		} else {
			return x;
		}
	} else if (operation == "gamma") {
		return (int) tgamma(x)*10;
	} else if (operation == "not") {
		return (int) ~x;
	}
}

int Black_and_white_basic_genes::binaryOp(int x, int y, std::string operation) {
	if (operation == "+") {
		return (int) x+y;
	} else if (operation == "-") {
		return (int) sqrt(pow(x-y, 2));
	} else if (operation == "xor") {
		return (int) x ^ y;
	} else if (operation == "/") {
		if (y != 0) {
			return (int)x / y;
		} else {
			return x;
		}
	} else if (operation == "*") {
		return (int) x * y;
	} else if (operation == "pow") {
		return (int)pow(x, y);
	} else if (operation == "hypot") {
		return (int)hypot(x, y);
	} else if (operation == "max") {
		return (int) std::max(x, y);
	} else if (operation == "min") {
		return (int)std::min(x, y);
	} else if (operation == "and") {
		return (int) x & y;
	} else if (operation == "or") {
		return (int) x | y;
	}
}