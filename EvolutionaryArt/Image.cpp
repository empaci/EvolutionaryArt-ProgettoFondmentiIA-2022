#include "Image.h"

void Image::setHeader(std::string header) {
	this->header = header;
}

void Image::setInformation(std::vector<int> information) {
	this->information = information;
}

void Image::setPhenotype(std::vector<std::vector<int>> phenotype) {
	this->phenotype = phenotype;
}

std::vector<std::vector<int>> Image::getPhenotype() {
	return this->phenotype;
}

void Image::save(std::string path) {
	std::string suffix = ".pgm";
	if (this->header == "P3") {
		suffix = ".ppm";
	}
	std::ofstream myfile(path + suffix);
	myfile << this->header + " ";
	for (int i = 0; i < this->information.size(); i++)
		myfile << information[i] << " ";
	for (int i = 0; i < phenotype.size(); i++)
		for (int j=0; j<phenotype[i].size(); j++)
			myfile << phenotype[i][j] << " ";
	myfile.close();
	return;
}