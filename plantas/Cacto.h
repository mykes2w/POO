#ifndef TRABALHOPOO_CACTO_H
#define TRABALHOPOO_CACTO_H
#include "Planta.h"
#include "Settings.h"

class Cacto : public Planta {
public:
        static const int preco=20;
        Cacto();
        bool viver(int &aguaSolo, int &nutrientesSolo) override;
        int getPreco() const override;
        char getChar() const override;
        Planta* duplicar() override;
        Planta* clone() const override;
};

#endif //TRABALHOPOO_CACTO_H