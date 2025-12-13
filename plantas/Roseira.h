#ifndef TRABALHOPOO_ROSEIRA_H
#define TRABALHOPOO_ROSEIRA_H
#include "Planta.h"
#include "Settings.h"


class Roseira : public Planta {
    public:
        static const int preco=30;
        Roseira();
        bool viver(int &aguaSolo, int &nutrientesSolo) override;
        int getPreco() const override;
        char getChar() const override;
};


#endif //TRABALHOPOO_ROSEIRA_H