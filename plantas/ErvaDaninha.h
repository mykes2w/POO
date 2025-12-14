#ifndef TRABALHOPOO_ERVADANINHA_H
#define TRABALHOPOO_ERVADANINHA_H
#include "Planta.h"
#include "Settings.h"


class ErvaDaninha : public Planta {
    private:
        int contReproducao;
    public:
        static const int preco=0;
        ErvaDaninha();
        bool viver(int &aguaSolo, int &nutrientesSolo) override;
        bool feia() const override {return true;}
        int getPreco() const override;
        Planta* duplicar() override;
        char getChar() const override;
        Planta* clone() const override;

};


#endif //TRABALHOPOO_ERVADANINHA_H