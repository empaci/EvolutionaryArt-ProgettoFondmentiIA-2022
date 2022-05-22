#include "Genes.h"

char* Genes::convertGenotypeToPhenotype()
{
	return nullptr;
}

std::string Genes::getGene(int i) {
	return genes_types[i];
}
bool Genes::setGenes(std::string* genes_types, int len) {
	setLen(len);
	this->genes_types = new std::string[this->len];
	std::copy(genes_types, genes_types + this->len, this->genes_types);
	return true;
}

int Genes::getLen() {
	return len;
}
bool Genes::setLen(int len) {
	this->len = len;
	return true;
}

int Genes::getNFunctionArgument(int pos) {
	return n_function_arguments[pos];
}
bool Genes::setNFunctionArguments(int* n_function_arguments, int len) {
	setLen(len);
	this->n_function_arguments = new int[this->len];
	this->n_function_arguments = new int(*n_function_arguments);
	return true;
}