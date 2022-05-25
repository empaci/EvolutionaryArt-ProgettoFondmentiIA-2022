#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>
#include <fstream>

class Image {
	private:
		std::string header;
		std::vector<int> information;
		std::vector<std::vector<int>> phenotype;
	public:
		void setHeader(std::string);
		void setInformation(std::vector<int>);
		void setPhenotype(std::vector<std::vector<int>>);
		void save(std::string);
};

#endif

