#ifndef BLACK_AND_WHITE_BASIC_GENES_H
#define BLACK_AND_WHITE_BASIC_GENES_H

#include "Genes.h"

class Black_and_white_basic_genes : public Genes {
    public:
        Black_and_white_basic_genes();
        char* convertGenotypeToPhenotype();
};

#endif

