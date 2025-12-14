#include "ErvaDaninha.h"
#include <complex>

ErvaDaninha::ErvaDaninha() {
    this->agua=Settings::ErvaDaninha::inicial_agua;
    this->nutrientes=Settings::ErvaDaninha::inicial_nutrientes;
    this->idade=0;
    this->contReproducao=0;
}

char ErvaDaninha::getChar() const {
    return 'E';
}

bool ErvaDaninha::viver(int &aguaSolo,int &nutrientesSolo) {
    idade++;
    contReproducao++;
    if (aguaSolo> 0) {
        int absAgua = Settings::ErvaDaninha::absorcao_agua;
        if (aguaSolo>=absAgua) {
            aguaSolo-=absAgua;
            this->agua+=absAgua;
        }else {
            this->agua+=aguaSolo;
            aguaSolo=0;
        }
    }
    if (nutrientesSolo> 0) {
        int absNutr=Settings::ErvaDaninha::absorcao_nutrientes;
        if (nutrientesSolo>=absNutr) {
            nutrientesSolo-=absNutr;
            this->nutrientes+=absNutr;
        }else {
            this->nutrientes+=nutrientesSolo;
            nutrientesSolo=0;
        }
    }
    if (idade>=60) {
        return false;
    }
    return true;
}

Planta *ErvaDaninha::duplicar() {
    if (this->nutrientes>Settings::ErvaDaninha::multiplica_nutrientes_maior && this->contReproducao>=5) {
        this->contReproducao=0;
        return new ErvaDaninha();
    }
    return nullptr;
}


int ErvaDaninha::getPreco() const {
    return preco;
}

