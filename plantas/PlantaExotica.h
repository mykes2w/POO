//
// Created by miigu on 01/11/2025.
//

#ifndef TRABALHOPOO_PLANTAEXOTICA_H
#define TRABALHOPOO_PLANTAEXOTICA_H
#include "Planta.h"


class PlantaExotica : public Planta {
public:
    PlantaExotica();
    bool viver(int &aguaSolo, int &nutrientesSolo) override;
    char getChar() const override;
};


#endif //TRABALHOPOO_PLANTAEXOTICA_H