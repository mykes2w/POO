#include "Adubo.h"
#include "Posicao.h"
#include <iostream>
using namespace std;

bool Adubo::usar(Posicao *p) {
    if (p==nullptr) {
        return false;
    }
    int dose=Settings::Adubo::dose;

    if (quantidade>=dose) {
        quantidade-=dose;
        p->setNutrientes(p->getNutrientes() + dose);
        cout<<"Adubou esta posicao , e tem isto de adubo "<< quantidade <<endl;
        return true;
    }else {
        cout << "O saco do adubo esta vazio" << endl;
        return false;
    }
}

Ferramenta* Adubo::clone() const {return new Adubo(*this);}
