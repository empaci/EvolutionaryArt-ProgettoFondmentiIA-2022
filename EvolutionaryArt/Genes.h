#ifndef GENE_TYPES_H
#define GENE_TYPES_H

#include <string>

class Individual;
class Image;

class Genes {
	private:
		std::string* genes_types;
		int* n_function_arguments;
		int len;
	public:
		virtual void convertGenotypeToPhenotype(Individual*, Image*) = 0;

		std::string getGene(int);
		bool setGenes(std::string*, int);

		int getLen();
		bool setLen(int);

		int getNFunctionArgument(int);
		bool setNFunctionArguments(int*,int);
};

#endif

