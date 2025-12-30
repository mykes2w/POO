#include "ErvaDaninha.h"
#include <complex>

ErvaDaninha::ErvaDaninha() {
    setAgua(Settings::ErvaDaninha::inicial_agua);
    setNutrientes(Settings::ErvaDaninha::inicial_nutrientes);
    setIdade(0);
    this->contReproducao=0;
}

char ErvaDaninha::getChar() const {
    return 'e';
}

bool ErvaDaninha::viver(int &aguaSolo,int &nutrientesSolo) {
    setIdade(getIdade() + 1);
    contReproducao++;
    if (aguaSolo> 0) {
        int absAgua = Settings::ErvaDaninha::absorcao_agua;
        if (aguaSolo>=absAgua) {
            aguaSolo-=absAgua;
            setAgua(getAgua() + absAgua);
        }else {
            setAgua(getAgua() + aguaSolo);
            aguaSolo=0;
        }
    }
    if (nutrientesSolo> 0) {
        int absNutr=Settings::ErvaDaninha::absorcao_nutrientes;
        if (nutrientesSolo>=absNutr) {
            nutrientesSolo-=absNutr;
            setNutrientes(getNutrientes() + absNutr);
        }else {
            setNutrientes(getNutrientes() + nutrientesSolo);
            nutrientesSolo=0;
        }
    }
    if (getIdade()>=60) {
        return false;
    }
    return true;
}

Planta *ErvaDaninha::duplicar() {
    if (getNutrientes()>Settings::ErvaDaninha::multiplica_nutrientes_maior && this->contReproducao>=5) {
        this->contReproducao=0;
        return new ErvaDaninha();
    }
    return nullptr;
}


int ErvaDaninha::getPreco() const {
    return preco;
}

Planta* ErvaDaninha::clone() const {return new ErvaDaninha(*this);}


