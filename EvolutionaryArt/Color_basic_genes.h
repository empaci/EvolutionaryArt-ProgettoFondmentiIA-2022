#ifndef COLOR_GENES_H
#define COLOR_GENES_H

#include "Genes.h";
#include "Individual.h";
#include "Image.h"
#include <cmath>

class Color_basic_genes : public Genes {
    public:
        Color_basic_genes();
        void convertGenotypeToPhenotype(Individual*, Image*);
        int eval(int, int, int, Node*);

        /*
        int* eval(int, int, Node*, char, int*, int*, int*);
        int* unaryOp(int*, std::string, int*);
        int* binaryOp(int*, int*, std::string, int*);
        */
};

#endif
