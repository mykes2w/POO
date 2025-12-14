#include "PlantaExotica.h"

PlantaExotica::PlantaExotica() {
    this->idade = 0;
    this->agua = 50;
    this->nutrientes = 50;
}

char PlantaExotica::getChar() const {
    return 'X';
}

bool PlantaExotica::viver(int &aguaSolo, int &nutrientesSolo) {
    idade++;
    if (aguaSolo> 0) {aguaSolo--;this->agua++;}
    if (nutrientesSolo> 0) {nutrientesSolo--;this->nutrientes++;}
    if (this->agua<=0 || this->nutrientes<=0) {return false;}
    return true;
}

int PlantaExotica::getPreco() const {
    return preco;
}

Planta* PlantaExotica::duplicar() {
    return nullptr;
}

Planta* PlantaExotica::clone() const {return new PlantaExotica(*this);}



