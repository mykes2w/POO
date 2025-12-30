#include "FerramentaZ.h"
#include "mundo/Posicao.h"
#include <iostream>

bool FerramentaZ::usar(Posicao *p) {
    if (p==nullptr || getQuantidade()<=0) {
        return false;
    }

    p->setNutrientes(p->getNutrientes()+20);
    setQuantidade(getQuantidade() - 5);
    std::cout << "Nutrientes injetados, restam: "<< getQuantidade() << std::endl;
    return true;
}

