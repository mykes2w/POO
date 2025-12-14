#ifndef TRABALHOPOO_ADUBO_H
#define TRABALHOPOO_ADUBO_H
#include "Adubo.h"
#include "Ferramenta.h"
#include "Settings.h"


class Adubo : public Ferramenta {
public:
    static const int custo=20;
    Adubo() : Ferramenta(Settings::Adubo::capacidade) {}
    Ferramenta* clone() const override;
    char getChar() const override{return 'a';}
    bool usar(Posicao *p) override;

};
#endif //TRABALHOPOO_ADUBO_H