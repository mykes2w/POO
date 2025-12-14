#include "Regador.h"
#include "mundo/Posicao.h"
#include <iostream>
using namespace std;

bool Regador::usar(Posicao *p) {
    if (p==nullptr) return false;

    int dose= Settings::Regador::dose;
    if (quantidade>=dose) {
        quantidade-=dose;
        int aguaA = p->getAgua();
        p->setAgua(aguaA+dose);
        cout << "Regou esta posicao , esta e a agua que resta no regador: "<< quantidade << endl;
        return true;
    }else {
        cout << "O regador esta vazio" << endl;
        return false;
    }
}

Ferramenta* Regador::clone() const {return new Regador(*this);}


