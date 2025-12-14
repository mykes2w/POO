#include "Posicao.h"
#include <cstdlib>
#include <ctime>
#include "plantas/Planta.h"

Posicao::Posicao() : planta(nullptr) {
    static bool seed_set = false;
    if (!seed_set) {
        srand(time(nullptr));
        seed_set = true;
    }

    agua = rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1) + Settings::Jardim::agua_min;
    nutrientes = rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1) + Settings::Jardim::nutrientes_min;
    ferramenta=nullptr;
}
Posicao::~Posicao() {
    if (planta!=nullptr) delete planta;
    delete ferramenta;
}

char Posicao::getChar() const {
    if (planta!=nullptr) {
        return planta->getChar();
    }
    if (ferramenta!=nullptr) {
        return ferramenta->getChar();
    }
    return '_';
}
bool Posicao::temPlanta() const {
    return planta != nullptr;
}

void Posicao::adicionarPlanta(Planta *p) {
    if (planta!=nullptr) {
        delete planta;
    }
    planta=p;
}
void Posicao::removerPlanta() {
    if (planta!=nullptr) {
        delete planta;
        planta=nullptr;
    }
}
Planta* Posicao::getPlanta() const {
    return planta;
}
int Posicao::getAgua() const {return agua;}
int Posicao::getNutrientes() const {return nutrientes;}
void Posicao::setNutrientes(int n) {nutrientes = n;}
void Posicao::setAgua(int a) {agua = a;}

bool Posicao::temFerramenta() const {
    return ferramenta!=nullptr;
}
void Posicao::adicionarFerramente(Ferramenta *f) {
    if (ferramenta!=nullptr) {
        delete ferramenta;
    }
    ferramenta=f;
}

Ferramenta *Posicao::retirarFerramenta() {
    Ferramenta* temp = ferramenta;
    ferramenta=nullptr;
    return temp;
}

const Ferramenta* Posicao::getFerramenta() const {
    return ferramenta;
}


