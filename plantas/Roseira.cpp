#include "Roseira.h"

Roseira::Roseira() {
    setIdade(0);
    setAgua(Settings::Roseira::inicial_agua);
    setNutrientes(Settings::Roseira::inicial_nutrientes);
}

char Roseira::getChar() const {
    return 'r';
}

bool Roseira::viver(int &aguaSolo, int &nutrientesSolo) {
    setIdade(getIdade() + 1);

    setAgua(getAgua() - Settings::Roseira::perda_agua);
    setNutrientes(getNutrientes() - Settings::Roseira::perda_nutrientes);

    if (aguaSolo >= Settings::Roseira::absorcao_agua) {
        aguaSolo -= Settings::Roseira::absorcao_agua;
        setAgua(getAgua() + Settings::Roseira::absorcao_agua);
    }else {
        setAgua(getAgua() + aguaSolo);
        aguaSolo= 0;
    }

    if (nutrientesSolo >= Settings::Roseira::absorcao_nutrientes) {
        nutrientesSolo -= Settings::Roseira::absorcao_nutrientes;
        setNutrientes(getNutrientes() + Settings::Roseira::absorcao_nutrientes);
    }else {
        setNutrientes(getNutrientes() + nutrientesSolo);
        nutrientesSolo= 0;
    }

    if (getAgua() < Settings::Roseira::morre_agua_menor) {return false;}
    if (getNutrientes() < Settings::Roseira::morre_nutrientes_menor) {return false;}
    if (getNutrientes() > Settings::Roseira::morre_nutrientes_maior) {return false;}

    return true;
}

int Roseira::getPreco() const {
    return preco;
}

Planta *Roseira::duplicar() {
    if (getNutrientes()>Settings::Roseira::multiplica_nutrientes_maior) {
        Roseira* filho = new Roseira();
        setAgua(getAgua() / 2);
        setNutrientes(getNutrientes() / 2);
        filho->setAgua(this->getAgua());
        filho->setNutrientes(this->getNutrientes());
        return filho;
    }

    return nullptr;
}

Planta* Roseira::clone() const {return new Roseira(*this);}



