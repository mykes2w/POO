#ifndef TRABALHOPOO_PLANTA_H
#define TRABALHOPOO_PLANTA_H


class Planta {
private:
    int idade,agua,nutrientes;
    int cAguaMais,cFaltaNutr;
public:
    Planta() : idade(0), agua(0), nutrientes(0), cAguaMais(0), cFaltaNutr(0) {};
    virtual ~Planta() {};

    virtual bool viver(int &aguaSolo,int &nutrientesSolo)=0;
    virtual char getChar() const=0;
    virtual bool feia() const {return false;}
    virtual int getPreco() const=0;
    virtual Planta* duplicar() =0;
    virtual Planta* clone() const =0;

    int getIdade() const {return idade;};
    int getAgua() const {return agua;};
    void setAgua(int a) { agua = a; }
    void setNutrientes(int n) { nutrientes = n; }
    int getNutrientes() const {return nutrientes;};
    int getCAguaMais() const { return cAguaMais; }
    int getCFaltaNutr() const { return cFaltaNutr; }
    void setIdade(int i) { idade = i; }
    void setCAguaMais(int c) { cAguaMais = c; }
    void setCFaltaNutr(int c) { cFaltaNutr = c; }
};


#endif //TRABALHOPOO_PLANTA_H