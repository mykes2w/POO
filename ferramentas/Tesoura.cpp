#include "Tesoura.h"
#include <iostream>
#include "Posicao.h"
#include "Planta.h"
using namespace std;

bool Tesoura::usar(Posicao *p) {
    if (p==nullptr) {
        return false;
    }
    if (!p->temPlanta()) {
        cout << "Nao ha planta aqui para cortar" << endl;
        return false;
    }
    Planta* plantaCorta = p->getPlanta();
    if (plantaCorta->feia()) {
        cout << "Uma planta feia foi cortada" << endl;
        p->removerPlanta();
        return true;
    }else {
        cout << "Esta planta nao e feia" << endl;
        return false;
    }
}

Ferramenta* Tesoura::clone() const {return new Tesoura(*this);}

