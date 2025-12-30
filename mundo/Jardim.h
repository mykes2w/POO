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

    void tentaReproduzir(int l,int c,Planta* p);

public:
    Jardim(int l, int c);
    ~Jardim();
    Jardim(const Jardim &outro);
    Jardim& operator= (const Jardim &outro);
    void desenhar(const Jardineiro* jardineiro);
    bool adicionarPlanta(int l, int c,Planta* p);
    int getLinhas() const;
    int getColunas() const;
    void passarTempo();
    Posicao* getPosicao(int l, int c) const;
    void adicionarFerrRandom();
};
#endif //TRABALHOPOO_JARDIM_H