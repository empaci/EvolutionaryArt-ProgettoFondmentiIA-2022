#ifndef GENE_TYPES_H
#define GENE_TYPES_H

#include <string>
#include <vector>
#include "Node.h"
#include "FastNoiseLite.h";

class Individual;
class Image;

class Genes {
	private:
		std::vector<std::string> genes_types = {
			"sqrt",
			"cbrt",
			"+",
			"-",
			"sin",
			"cos",
		//	"tan",
			"xor",
			"/",
			"*",
			"pow2",
			"pow",
			"log",
			"hypot",
		//	"gamma",
			"and",
			"or",
			"not",
			"exp",
			"exp2",
		//	"lgamma",
		//	"erf",
			"arclength",
			"max",
			"min",
			"noise",
			"noise2",
			"cellular",
			"cellular2",
			"cellular3",
		};
		//tells if the operation, in the same position, is unary or binary
		std::vector<int> n_function_arguments = {
			1, //sqrt
			1, //cbrt
			2, //+
			2, //-
			1, //sin
			1, //cos
		//	1, //tan
			2, //xor
			2, // /
			2, // *
			1, // pow2
			2, //pow
			1, //log
			2, //hypot
		//	1, //gamma
			2, //and
			2, //or
			1, //not
			1, //exp
			1, //exp2 (2^x)
		//	1, //lgamma
		//	1, //erf
			2, //arc length
			2, //max
			2, //min
			2, //noise opensimplex
			2, //noise type 2
			2, //cellular noise
			2, //cellular noise type 2
			2, //cellular noise type 3
		};
	protected:
		int dim = 600;
		FastNoiseLite noise;
		FastNoiseLite noise_2;
		FastNoiseLite cellular_noise;
		FastNoiseLite cellular_noise_2;
		FastNoiseLite cellular_noise_3;
	public:
		virtual void convertGenotypeToPhenotype(Individual*, Image*) = 0;

		Genes();
		std::string getGene(int);
		bool setGenes(std::vector<std::string>);

		int getLen();

		int getNFunctionArgument(int);
		bool setNFunctionArguments(std::vector<int>);

		int eval(int, int, Node*, int*);
		int unaryOp(int, std::string);
		int binaryOp(int, int, std::string);
};

#endif

