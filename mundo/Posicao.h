#ifndef TRABALHOPOO_POSICAO_H
#define TRABALHOPOO_POSICAO_H
#include "Ferramenta.h"
#include "../Settings.h"

class Planta;

class Posicao {
private:
    int agua;
    int nutrientes;
    Planta* planta;
    Ferramenta* ferramenta;

public:
    Posicao();
    ~Posicao();
    char getChar() const;

    bool temPlanta() const;
    void adicionarPlanta(Planta* p);
    Planta* getPlanta() const;
    void removerPlanta();

    int getAgua() const;
    int getNutrientes() const;
    void setAgua(int a);
    void setNutrientes(int n);

    bool temFerramenta() const;
    void adicionarFerramente(Ferramenta* f);
    Ferramenta* retirarFerramenta();
    const Ferramenta* getFerramenta() const;

    Posicao(const Posicao& outra);
    Posicao& operator=(const Posicao& outra);
};


#endif //TRABALHOPOO_POSICAO_H