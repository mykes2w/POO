#include "Cacto.h"
#include <iostream>

Cacto::Cacto() {
    this->idade = 0;
    this->agua = 0;
    this->nutrientes = 0;
    this->ctgAguaMais = 0;
    this->ctgFaltaNutr = 0;
}
char Cacto::getChar() const {
    return 'C';
}

bool Cacto::viver(int &aguaSolo, int &nutrientesSolo) {
    idade++;

    int aguaAbs = (aguaSolo * Settings::Cacto::absorcao_agua_percentagem) /100;
    if (aguaAbs > 0) {
        aguaAbs -= aguaAbs;
        this->agua += aguaAbs;
    }
    int nutrAbs = Settings::Cacto::absorcao_nutrientes;
    if (nutrientesSolo >= nutrAbs) {
        nutrientesSolo -= nutrientesSolo;
        this->nutrientes += nutrAbs;
    }else {
        this->nutrientes += nutrientesSolo;
        nutrientesSolo = 0;
    }

    if (aguaSolo > Settings::Cacto::morre_agua_solo_maior) {
        ctgAguaMais++;
    }else {
        ctgAguaMais = 0;
    }

    if (ctgAguaMais >= Settings::Cacto::morre_agua_solo_instantes) {
        return false;
    }

    if (nutrientesSolo < Settings::Cacto::morre_nutrientes_solo_menor) {
        ctgFaltaNutr++;
    }else {
        ctgFaltaNutr = 0;
    }

    if (ctgFaltaNutr>= Settings::Cacto::morre_nutrientes_solo_instantes) {
        return false;
    }

    return true;
}

int Cacto::getPreco() const {
    return preco;
}

Planta* Cacto::duplicar(){
    if (nutrientes>Settings::Cacto::multiplica_nutrientes_maior && agua>Settings::Cacto::multiplica_agua_maior) {
        Cacto* filho = new Cacto();
        this->agua/=2;
        this->nutrientes/=2;
        filho->agua=this->agua;
        filho->nutrientes=this->nutrientes;
        return filho;
    }
    return nullptr;
}

Planta* Cacto::clone() const {return new Cacto(*this);}




