#ifndef BLACK_AND_WHITE_BASIC_GENES_H
#define BLACK_AND_WHITE_BASIC_GENES_H

#include "Genes.h";
#include "Individual.h";
#include "Image.h"
#include <cmath>


class Black_and_white_basic_genes : public Genes {
    public:
        Black_and_white_basic_genes();
        void convertGenotypeToPhenotype(Individual*, Image&);
        int eval(int, int, Node*, int*);
        int unaryOp(int, std::string);
        int binaryOp(int, int, std::string);
};

#endif

