#ifndef TRABALHOPOO_JARDIM_H
#define TRABALHOPOO_JARDIM_H
#include "Posicao.h"
#include "Planta.h"
#include "Jardineiro.h"

class Planta;

class Jardim {
    Posicao** grelha;
    int linhas;
    int colunas;

public:
    Jardim(int l, int c);
    ~Jardim();
    void desenhar(const Jardineiro* jardineiro);
    bool adicionarPlanta(int l, int c,Planta* p);
    int getLinhas() const;
    int getColunas() const;
    void passarTempo();
};
#endif //TRABALHOPOO_JARDIM_H