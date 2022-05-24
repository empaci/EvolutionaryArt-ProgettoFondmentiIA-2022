#include "Image.h"
#include <vector>

void Image::setHeader(char* header) {
	*this->image_header = *header;
}

void Image::setPhenotype(std::vector<std::vector<int>> phenotype) {
	this->phenotype = phenotype;
}