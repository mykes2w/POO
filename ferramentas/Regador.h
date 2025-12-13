#ifndef TRABALHOPOO_REGADOR_H
#define TRABALHOPOO_REGADOR_H
#include "Ferramenta.h"
#include "Regador.h"
#include "Settings.h"

class Regador : public Ferramenta{
public:
    static const int custo=50;
    Regador():Ferramenta(Settings::Regador::capacidade){}
    char getChar() const override {return 'r';}
    bool usar(Posicao *p) override;
};

#endif //TRABALHOPOO_REGADOR_H