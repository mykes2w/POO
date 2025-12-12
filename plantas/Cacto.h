#ifndef TRABALHOPOO_CACTO_H
#define TRABALHOPOO_CACTO_H
#include "Planta.h"
#include "Settings.h"

class Cacto : public Planta {
private:
        int ctgAguaMais;
        int ctgFaltaNutr;
public:
        Cacto();
        bool viver(int &aguaSolo, int &nutrientesSolo) override;
        char getChar() const override;
};

#endif //TRABALHOPOO_CACTO_H