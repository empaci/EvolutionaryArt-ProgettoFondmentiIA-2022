#ifndef GENE_TYPES_H
#define GENE_TYPES_H

#include <string>
#include <vector>
#include "Node.h"
#include "FastNoiseLite.h";
#include <cmath>

#define M_PI 3.14159265358979323846
#define PHI 1.6180339887498948482
#define EXP 2.7182818284

class Individual;
class Image;

class Genes {
	private:
		std::vector<std::string> genes_types = {
			"sqrt",
			"cbrt",
			"square",
			"cube",
			"+",
			"-",
			"mod",
			"sin",
			"cos",
			"tan",
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
		//	"arclength",
			"max",
			"min",
			">",
			"<",
			"==",
			"!=", 
		//	"noise",
			"noise2",
		//	"noise3",
			"noise4",
		//	"noisecellular",
			"noisecellular2",
			"noisecellular3",
			"noisecellular4",
		//	"binet",
			"stripes",
		};
		//tells if the operation, in the same position, is unary or binary
		std::vector<int> n_function_arguments = {
			1, //sqrt
			1, //cbrt
			1, //square
			1, //cube
			2, //+
			2, //-
			2, //mod
			1, //sin
			1, //cos
			1, //tan
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
		//	2, //arc length
			2, //max
			2, //min
			2, //>
			2, //<
			2, //==
			2, //!=
		//	2, //noise opensimplex
			2, //noise type 2
		//	2, //noise type 3
			2, //noise type 4
		//	2, //cellular noise
			2, //cellular noise type 2
			2, //cellular noise type 3
			2, //cellular noise type 4
		//	1, //binet
			2, //stripes 
		};
	protected:
		int dim = 400;
		FastNoiseLite noise;
		FastNoiseLite noise_2;
		FastNoiseLite noise_3;
		FastNoiseLite noise_4;
		FastNoiseLite cellular_noise;
		FastNoiseLite cellular_noise_2;
		FastNoiseLite cellular_noise_3;
		FastNoiseLite cellular_noise_4;
	public:
		virtual void convertGenotypeToPhenotype(Individual*, Image*) = 0;

		Genes();
		std::string getGene(int);
		bool setGenes(std::vector<std::string>);

		int getLen();

		int getNFunctionArgument(int);
		bool setNFunctionArguments(std::vector<int>);

		int eval(int, int, Node*);
		float unaryOp(float, std::string);
		float binaryOp(float, float, std::string);
};

#endif

