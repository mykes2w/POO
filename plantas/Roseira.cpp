#include "Roseira.h"

Roseira::Roseira() {
    this->idade=0;
    this->agua = Settings::Roseira::inicial_agua;
    this->nutrientes = Settings::Roseira::inicial_nutrientes;
}

char Roseira::getChar() const {
    return 'R';
}

bool Roseira::viver(int &aguaSolo, int &nutrientesSolo) {
    idade++;

    this->agua -= Settings::Roseira::perda_agua;
    this->nutrientes -= Settings::Roseira::perda_nutrientes;

    if (aguaSolo >= Settings::Roseira::absorcao_agua) {
        aguaSolo -= Settings::Roseira::absorcao_agua;
        this->agua += Settings::Roseira::absorcao_agua;
    }else {
        this->agua += aguaSolo;
        aguaSolo= 0;
    }

    if (nutrientesSolo >= Settings::Roseira::absorcao_nutrientes) {
        nutrientesSolo -= Settings::Roseira::absorcao_nutrientes;
        this->nutrientes += Settings::Roseira::absorcao_nutrientes;
    }else {
        this->nutrientes += nutrientesSolo;
        nutrientesSolo= 0;
    }

    if (this->agua < Settings::Roseira::morre_agua_menor) {return false;}
    if (this->nutrientes < Settings::Roseira::morre_nutrientes_menor) {return false;}
    if (this->nutrientes > Settings::Roseira::morre_nutrientes_maior) {return false;}

    return true;
}

int Roseira::getPreco() const {
    return preco;
}

Planta *Roseira::duplicar() {
    if (nutrientes>Settings::Roseira::multiplica_nutrientes_maior) {
        Roseira* filho = new Roseira();
        this->agua/=2;
        this->nutrientes/=2;
        filho->agua=this->agua;
        filho->nutrientes=this->nutrientes;
        return filho;
    }
    return nullptr;
}


