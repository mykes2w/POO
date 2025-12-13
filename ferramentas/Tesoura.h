#ifndef TRABALHOPOO_TESOURA_H
#define TRABALHOPOO_TESOURA_H
#include "Ferramenta.h"


class Tesoura : public Ferramenta{
public:
    static const int custo=15;
    Tesoura(): Ferramenta(999){}
    char getChar() const override {return 't';}
    bool usar(Posicao *p) override;
};


#endif //TRABALHOPOO_TESOURA_H