#include "Genes.h"


Genes::Genes() {
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
	noise.SetFractalGain(FastNoiseLite::FractalType_Ridged);
	noise.SetFractalGain(0.9);
	noise.SetFractalLacunarity(2);
	noise.SetFractalOctaves(3);
	noise.SetFractalWeightedStrength(0.5);
	noise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
	noise.SetFractalType(FastNoiseLite::FractalType_DomainWarpIndependent);

	noise_2.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
	noise_2.SetDomainWarpType(FastNoiseLite::DomainWarpType_BasicGrid);
	noise_2.SetDomainWarpAmp(50);
	noise_2.SetFractalGain(FastNoiseLite::FractalType_DomainWarpProgressive);

	noise_3.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise_3.SetDomainWarpType(FastNoiseLite::DomainWarpType_BasicGrid);
	noise_3.SetDomainWarpAmp(50);
	noise_3.SetFractalType(FastNoiseLite::FractalType_FBm);
	noise_3.SetFractalOctaves(4);
	noise_3.SetFractalLacunarity(2);
	noise_3.SetFractalGain(0.8);

	cellular_noise.SetNoiseType(FastNoiseLite::NoiseType_Value);
	cellular_noise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
	cellular_noise.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);
	cellular_noise.SetCellularJitter(1);
	cellular_noise.SetDomainWarpType(FastNoiseLite::DomainWarpType_BasicGrid);
	cellular_noise.SetDomainWarpAmp(50);
	cellular_noise.SetFractalType(FastNoiseLite::FractalType_DomainWarpProgressive);
	cellular_noise.SetFractalOctaves(5);
	cellular_noise.SetFractalLacunarity(2);
	cellular_noise.SetFractalGain(0.6);

	cellular_noise_2.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	cellular_noise_2.SetFractalGain(FastNoiseLite::FractalType_PingPong);
	cellular_noise_2.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Euclidean);
	cellular_noise_2.SetDomainWarpAmp(50);
	cellular_noise_2.SetFractalOctaves(5);
	cellular_noise_2.SetFractalLacunarity(2);
	cellular_noise_2.SetFractalGain(0.6);

	cellular_noise_3.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	cellular_noise_3.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
	cellular_noise_3.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2);
	cellular_noise_3.SetDomainWarpAmp(100);

	noise.SetSeed(std::rand());
	noise_2.SetSeed(std::rand());
	cellular_noise.SetSeed(std::rand());
	cellular_noise_2.SetSeed(std::rand());
	cellular_noise_3.SetSeed(std::rand());
}

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
	if (operation == "cos") {
		return (int)(cos(x) * 100);
	}
	if (operation == "tan") {
		return (int)(tan(x*3.14/180) * 100);
	}
	else if (operation == "sqrt") {
		return (int)sqrt(abs(x));
	}
	else if (operation == "cbrt") {
		return (int)cbrt(abs(x));
	}
	else if (operation == "log") {
		return (int)(log(abs(x)) * 100);
	}
	else if (operation == "gamma") {
		return (int)tgamma(((float)x)/50) * 10;
	}
	else if (operation == "not") {
		return (int)~x;
	}
	else if (operation == "pow2") {
		return (int)pow(x, 2);
	}
	else if (operation == "exp") {
		return (int)exp(x);
	} else if (operation == "exp2") {
		return (int)exp2(x);
	}
	else if (operation == "erf") {
		return (int)erf(((float)x)/100)*100;
	}
	else if (operation == "lgamma") {
		return (int)lgamma(((float)x) / 50)*10;
	}
	return x;
}

int Genes::binaryOp(int x, int y, std::string operation) {
	if (operation == "+") {
		return (int)x + y;
	}
	else if (operation == "-") {
		return (int)abs(x - y);
	}
	else if (operation == "mod") {
		if (y != 0) {
			return (int)x % y;
		}
		else {
			return x;
		}
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
	else if (operation == "arclength") {
		return (int)((float)x / 360) * 2 * 3.14159 * y;
	}
	else if (operation == "max") {
		return (int) fmax(x, y);
	}
	else if (operation == "min") {
		return (int)fmin(x, y);
	}
	else if (operation == "noise") {
		return (int) ((noise.GetNoise((float)x, (float)y) + 1 )* 255/2);
	}
	else if (operation == "noise2") {
		return (int) ((noise_2.GetNoise((float)x, (float)y) + 1 ) * 255 / 2);
	}
	else if (operation == "noise3") {
		return (int)((noise_3.GetNoise((float)x, (float)y) + 1) * 255 / 2);
	}
	else if (operation == "noisecellular") {
		return (int) ((cellular_noise.GetNoise((float)x, (float)y) + 1 ) * 255 / 2);
	}
	else if (operation == "noisecellular2") {
		return (int) ((cellular_noise_2.GetNoise((float)x, (float)y) + 1 ) * 255 / 2);
	}
	else if (operation == "noisecellular3") {
		return (int) ((cellular_noise_3.GetNoise((float)x, (float)y) + 1 ) * 255 / 2);
	}
	return x;
}