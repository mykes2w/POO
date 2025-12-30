#include "Cacto.h"
#include <iostream>

Cacto::Cacto() {
    setIdade(0);
    setNutrientes(0);
    setAgua(0);
    setCAguaMais(0);
    setCFaltaNutr(0);
}
char Cacto::getChar() const {
    return 'c';
}

bool Cacto::viver(int &aguaSolo, int &nutrientesSolo) {
    setIdade(getIdade() + 1);

    int aguaAbs = (aguaSolo * Settings::Cacto::absorcao_agua_percentagem) /100;
    if (aguaAbs > 0) {
        aguaSolo -= aguaAbs;
        setAgua(getAgua() + aguaAbs);
    }
    int nutrAbs = Settings::Cacto::absorcao_nutrientes;
    if (nutrientesSolo >= nutrAbs) {
        nutrientesSolo -= nutrAbs;
        setNutrientes(getNutrientes()+nutrAbs);
    }else {
        setNutrientes(getNutrientes()+nutrientesSolo);
        nutrientesSolo = 0;
    }

    if (aguaSolo > Settings::Cacto::morre_agua_solo_maior) {
        setCAguaMais(getCAguaMais()+1);
    }else {
        setCAguaMais(0);
    }

    if (getCAguaMais() >= Settings::Cacto::morre_agua_solo_instantes) {
        return false;
    }

    if (nutrientesSolo < Settings::Cacto::morre_nutrientes_solo_menor) {
        setCFaltaNutr(getCFaltaNutr()+1);
    }else {
        setCFaltaNutr(0);
    }

    if (getCFaltaNutr()>= Settings::Cacto::morre_nutrientes_solo_instantes) {
        return false;
    }

    return true;
}

int Cacto::getPreco() const {
    return preco;
}

Planta* Cacto::duplicar(){
    if (getNutrientes()>Settings::Cacto::multiplica_nutrientes_maior && getAgua()>Settings::Cacto::multiplica_agua_maior) {
        Cacto* filho = new Cacto();
        setAgua(getAgua() / 2);
        setNutrientes(getNutrientes() / 2);
        filho->setAgua(this->getAgua());
        filho->setNutrientes(this->getNutrientes());
        return filho;
    }

    return nullptr;
}

Planta* Cacto::clone() const {return new Cacto(*this);}





