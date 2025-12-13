#ifndef TRABALHOPOO_ERVADANINHA_H
#define TRABALHOPOO_ERVADANINHA_H
#include "Planta.h"


class ErvaDaninha : public Planta {
    public:
        static const int preco=0;
        ErvaDaninha();
        bool viver(int &aguaSolo, int &nutrientesSolo) override;
        bool feia() const override {return true;}
        int getPreco() const override;
        char getChar() const override;
};


#endif //TRABALHOPOO_ERVADANINHA_H