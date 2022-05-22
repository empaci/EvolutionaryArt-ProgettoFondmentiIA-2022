#ifndef GENE_TYPES_H
#define GENE_TYPES_H

#include <string>
#include "Individual.h"

class Genes {
	private:
		std::string* genes_types;
		int* n_function_arguments;
		int len;
	public:
		virtual char* convertGenotypeToPhenotype(Individual);

		std::string getGene(int);
		bool setGenes(std::string*, int);

		int getLen();
		bool setLen(int);

		int getNFunctionArgument(int);
		bool setNFunctionArguments(int*,int);
};

#endif
