#ifndef TRABALHOPOO_ERVADANINHA_H
#define TRABALHOPOO_ERVADANINHA_H
#include "Planta.h"


class ErvaDaninha : public Planta {
    public:
        ErvaDaninha();
        bool viver(int &aguaSolo, int &nutrientesSolo) override;
        char getChar() const override;
};


#endif //TRABALHOPOO_ERVADANINHA_H