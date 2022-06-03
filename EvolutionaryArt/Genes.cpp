#include "Genes.h"


Genes::Genes() {
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
	noise.SetFractalGain(FastNoiseLite::FractalType_Ridged);
	noise.SetFractalGain(0.9);
	noise.SetFractalLacunarity(2);
	noise.SetFractalOctaves(4);
	noise.SetFractalWeightedStrength(0.5);
	noise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
	noise.SetFractalType(FastNoiseLite::FractalType_DomainWarpIndependent);

	noise_2.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
	noise_2.SetDomainWarpType(FastNoiseLite::DomainWarpType_BasicGrid);
	noise_2.SetDomainWarpAmp(50);
	noise_2.SetFractalGain(FastNoiseLite::FractalType_DomainWarpProgressive);
	noise_2.SetFractalOctaves(4);

	noise_3.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise_3.SetDomainWarpType(FastNoiseLite::DomainWarpType_BasicGrid);
	noise_3.SetDomainWarpAmp(50);
	noise_3.SetFractalType(FastNoiseLite::FractalType_FBm);
	noise_3.SetFractalOctaves(4);
	noise_3.SetFractalLacunarity(2);
	noise_3.SetFractalGain(0.8);

	noise_4.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
	noise_4.SetFractalType(FastNoiseLite::FractalType_FBm);
	noise_4.SetFractalOctaves(5);
	noise_4.SetFractalLacunarity(2);
	noise_4.SetFractalGain(0.7);

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
	cellular_noise_3.SetFractalType(FastNoiseLite::FractalType_PingPong);
	cellular_noise_3.SetFractalOctaves(5);

	cellular_noise_4.SetNoiseType(FastNoiseLite::NoiseType_Cellular);

	noise.SetSeed(std::rand());
	noise_2.SetSeed(std::rand());
	noise_3.SetSeed(std::rand());
	noise_4.SetSeed(std::rand());
	cellular_noise.SetSeed(std::rand());
	cellular_noise_2.SetSeed(std::rand());
	cellular_noise_3.SetSeed(std::rand());
	cellular_noise_4.SetSeed(std::rand());
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
		return (sin(x/50) * 10);
	}
	if (operation == "cos") {
		return (cos(x/50) * 10);
	}
	if (operation == "tan") {
		if (x != 90) {
			return (tan(x * M_PI / 180) * 100);
		} else {
			return x;
		}
	}
	else if (operation == "sqrt") {
		return sqrt(abs(x));
	}
	else if (operation == "cbrt") {
		return cbrt(abs(x));
	}
	else if (operation == "log") {
		return (log(abs(x)) * 100);
	}
	else if (operation == "gamma") {
		return tgamma((x/50)) * 10;
	}
	else if (operation == "not") {
		return ~(int)x;
	}
	else if (operation == "pow2") {
		return pow(x, 2);
	}
	else if (operation == "exp") {
		return exp(x);
	} else if (operation == "exp2") {
		return exp2(x);
	}
	else if (operation == "erf") {
		return erf((x/100))*10;
	}
	else if (operation == "lgamma") {
		return lgamma((x / 50))*10;
	}
	return x;
}

int Genes::binaryOp(int x, int y, std::string operation) {
	if (operation == "+") {
		return x + y;
	}
	else if (operation == "-") {
		return x - y;
	}
	else if (operation == "mod") {
		if (y != 0) {
			return x % y;
		}
		else {
			return x;
		}
	}
	else if (operation == "xor") {
		return x ^ y;
	}
	else if (operation == "/") {
		if (y != 0) {
			return x / y;
		}
		else {
			return x;
		}
	}
	else if (operation == "*") {
		return x * y;
	}
	else if (operation == "pow") {
		return pow(x, y);
	}
	else if (operation == "hypot") {
		return hypot(x, y);
	}
	else if (operation == "and") {
		return x & y;
	}
	else if (operation == "or") {
		return x | y;
	}
	else if (operation == "arclength") {
		return ((float)x / 360) * M_PI * y;
	}
	else if (operation == "max") {
		return fmax(x, y);
	}
	else if (operation == "min") {
		return fmin(x, y);
	}
	else if (operation == ">") {
		return (x > y) ? 0 : 254;
	}
	else if (operation == "<") {
		return (x < y) ? 0 : 254;
	}
	else if (operation == "==") {
		return (x == y) ? 0 : 254;
	}
	else if (operation == "!=") {
		return (x != y) ? 0 : 254;
	}
	else if (operation == "hyperbolicparaboloid") {
		return pow(x, 2) + pow(y, 2);
	}
	else if (operation == "infiniteparaboloid") {
		return pow(x, 2) - pow(y, 2);
	}
	else if (operation == "noise") {
		return ((noise.GetNoise((float)x, (float)y) + 1 )* 255/2);
	}
	else if (operation == "noise2") {
		return ((noise_2.GetNoise((float)x, (float)y) + 1 ) * 255 / 2);
	}
	else if (operation == "noise3") {
		return ((noise_3.GetNoise((float)x, (float)y) + 1) * 255 / 2);
	}
	else if (operation == "noise4") {
		return ((noise_4.GetNoise((float)x, (float)y) + 1) * 255 / 2);
	}
	else if (operation == "noisecellular") {
		return ((cellular_noise.GetNoise((float)x, (float)y) + 1 ) * 255 / 2);
	}
	else if (operation == "noisecellular2") {
		return ((cellular_noise_2.GetNoise((float)x, (float)y) + 1 ) * 255 / 2);
	}
	else if (operation == "noisecellular3") {
		return ((cellular_noise_3.GetNoise((float)x, (float)y) + 1 ) * 255 / 2);
	}
	else if (operation == "noisecellular4") {
		return ((cellular_noise_4.GetNoise((float)x, (float)y) + 1) * 255 / 2);
	}
	return x;
}