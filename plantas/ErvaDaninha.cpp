#include "ErvaDaninha.h"

ErvaDaninha::ErvaDaninha() {

}

char ErvaDaninha::getChar() const {
    return 'E';
}

bool ErvaDaninha::viver(int &aguaSolo,int &nutrientesSolo) {
    idade++;
    if (aguaSolo> 0) {aguaSolo--;this->agua++;}
    if (nutrientesSolo> 0) {nutrientesSolo--;this->nutrientes++;}
    return true;
}

int ErvaDaninha::getPreco() const {
    return preco;
}
