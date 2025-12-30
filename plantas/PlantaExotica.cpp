#include "PlantaExotica.h"

PlantaExotica::PlantaExotica() {
    setIdade(0);
    setAgua(50);
    setNutrientes(50);
}

char PlantaExotica::getChar() const {
    return 'x';
}

bool PlantaExotica::viver(int &aguaSolo, int &nutrientesSolo) {
    setIdade(getIdade() + 1);
    if (aguaSolo>=2) {aguaSolo-=2;setAgua(getAgua() + 2);} else {
        setAgua(getAgua() - 5);
    }
    if (getAgua() > 100) {
        setNutrientes(getNutrientes() + 10);
        setAgua(getAgua() - 10);
    }
    if (getNutrientes() <= 0 || getAgua() <= 0) return false;

    return true;
}

int PlantaExotica::getPreco() const {
    return preco;
}

Planta* PlantaExotica::duplicar() {
    return nullptr;
}

Planta* PlantaExotica::clone() const {return new PlantaExotica(*this);}



