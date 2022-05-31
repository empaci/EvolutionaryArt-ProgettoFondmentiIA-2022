#ifndef BLACK_AND_WHITE_BASIC_GENES_H
#define BLACK_AND_WHITE_BASIC_GENES_H

#include "Genes.h";
#include "Individual.h";
#include "Image.h"
#include <cmath>


class Black_and_white_basic_genes : public Genes {
    public:
        Black_and_white_basic_genes();
        void convertGenotypeToPhenotype(Individual*, Image*);
        //void stackOperations(Node*, std::vector<std::string>*);
        //std::string postfixNode(Node*);
        //int eval(int, int, int*, std::vector<std::string>, int*);
        //int evalAux(int, int, int*, int*, std::vector<std::string>, int*, bool);
};

#endif

