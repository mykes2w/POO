#ifndef TRABALHOPOO_REGADOR_H
#define TRABALHOPOO_REGADOR_H
#include "Ferramenta.h"
#include "Regador.h"
#include "Settings.h"

class Regador : public Ferramenta{
public:
    static const int custo=50;
    Regador():Ferramenta(Settings::Regador::capacidade){}
    Ferramenta* clone() const override;
    char getChar() const override {return 'g';}
    bool usar(Posicao *p) override;
};

#endif //TRABALHOPOO_REGADOR_H