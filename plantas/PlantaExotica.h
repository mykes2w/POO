#ifndef TRABALHOPOO_PLANTAEXOTICA_H
#define TRABALHOPOO_PLANTAEXOTICA_H
#include "Planta.h"


class PlantaExotica : public Planta {
public:
    static const int preco=100;
    PlantaExotica();
    bool viver(int &aguaSolo, int &nutrientesSolo) override;
    Planta* duplicar() override;
    int getPreco() const override;
    char getChar() const override;
};


#endif //TRABALHOPOO_PLANTAEXOTICA_H