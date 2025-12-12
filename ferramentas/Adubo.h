#ifndef TRABALHOPOO_ADUBO_H
#define TRABALHOPOO_ADUBO_H
#include "Adubo.h"
#include "Ferramenta.h"
#include "Settings.h"


class Adubo : public Ferramenta {
public:
    Adubo() : Ferramenta(Settings::Adubo::capacidade) {}

    char getChar() const override{return 'a';}
    bool usar(Posicao *p) override;

};
#endif //TRABALHOPOO_ADUBO_H