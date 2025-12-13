#ifndef TRABALHOPOO_JARDINEIRO_H
#define TRABALHOPOO_JARDINEIRO_H
#include <vector>
#include "Ferramenta.h"


class Jardineiro {

private:
    int linha;
    int coluna;
    std::vector<Ferramenta*> mochila;

    int dinheiro,contMov,contColheitas,contPlantacoes;
public:
    static const int SALDO_INICIAL=500;
    static const int MAX_MOV=10;
    static const int MAX_PLANTACOES=2;
    static const int MAX_COLHEITAS=5;

    Jardineiro();
    virtual ~Jardineiro();

    int getLinha() const;
    int getColuna() const;
    char getChar() const;
    void setPosicao(int l,int c);

    void apanharFerramenta(Ferramenta* f);
    Ferramenta* getFerramenta(int index) const;
    int getNumFerramentas() const;

    int getDinheiro() const;
    void gastarDinheiro(int valor);
    void receberDinheiro(int valor);
    int getMov() const;
    void registarMov();
    int getColheitas() const;
    void registarColheitas();
    int getPlantacoes() const;
    void registarPlantacoes();
    void prepNovoTurno();
};


#endif //TRABALHOPOO_JARDINEIRO_H