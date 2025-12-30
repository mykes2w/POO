#ifndef TRABALHOPOO_FERRAMENTAZ_H
#define TRABALHOPOO_FERRAMENTAZ_H
#include "Ferramenta.h"
#include "Settings.h"


class FerramentaZ : public Ferramenta{
public:
    static const int custo = 80;
    FerramentaZ() : Ferramenta(50){}
    char getChar() const override{return 'z';}
    bool usar(Posicao* p) override;
    Ferramenta* clone() const override{return new FerramentaZ(*this);}
};

#endif //TRABALHOPOO_FERRAMENTAZ_H