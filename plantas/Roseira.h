#ifndef TRABALHOPOO_ROSEIRA_H
#define TRABALHOPOO_ROSEIRA_H
#include "Planta.h"
#include "Settings.h"


class Roseira : public Planta {
    public:
        Roseira();
        bool viver(int &aguaSolo, int &nutrientesSolo) override;
        char getChar() const override;
};


#endif //TRABALHOPOO_ROSEIRA_H