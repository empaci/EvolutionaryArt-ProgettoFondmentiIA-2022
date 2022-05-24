#ifndef IMAGE_H
#define IMAGE_H

class Image {
	private:
		char* image_header = nullptr;
		std::vector<std::vector<int>> phenotype;
	public:
		void setHeader(char *);
		void setPhenotype(std::vector<std::vector<int>>);
};

#endif

