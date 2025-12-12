//
// Created by miigu on 01/11/2025.
//

#ifndef TRABALHOPOO_POSICAO_H
#define TRABALHOPOO_POSICAO_H
#include "../Settings.h"

class Planta;

class Posicao {
private:
    int agua;
    int nutrientes;
    Planta* planta;

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
};


#endif //TRABALHOPOO_POSICAO_H