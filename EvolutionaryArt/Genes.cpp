#include "Genes.h"


std::string Genes::getGene(int i) {
	return genes_types[i];
}
bool Genes::setGenes(std::vector<std::string> genes_types) {
	this->genes_types = genes_types;
	return true;
}

int Genes::getLen() {
	return genes_types.size();
}

int Genes::getNFunctionArgument(int pos) {
	return n_function_arguments[pos];
}
bool Genes::setNFunctionArguments(std::vector<int> n_function_arguments) {
	this->n_function_arguments = n_function_arguments;
	return true;
}

int Genes::eval(int x, int y, Node* head, int* res) {

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

int Genes::unaryOp(int x, std::string operation) {
	if (operation == "sin") {
		return (int)(sin(x) * 100);
	}
	else if (operation == "sqrt") {
		return (int)sqrt(abs(x));
	}
	else if (operation == "log") {
		return (int)(log(abs(x)) * 100);
	}
	else if (operation == "gamma") {
		return (int)tgamma(x) * 10;
	}
	else if (operation == "not") {
		return (int)~x;
	}
	else if (operation == "pow2") {
		return (int)pow(x, 2);
	}
	else if (operation == "exp") {
		return (int)exp(x);
	}
}

int Genes::binaryOp(int x, int y, std::string operation) {
	if (operation == "+") {
		return (int)x + y;
	}
	else if (operation == "-") {
		return (int)abs(x - y);
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
	else if (operation == "pow") {
		return (int)pow(x, y);
	}
	else if (operation == "hypot") {
		return (int)hypot(x, y);
	}
	else if (operation == "and") {
		return (int)x & y;
	}
	else if (operation == "or") {
		return (int)x | y;
	}
}