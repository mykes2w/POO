#ifndef TRABALHOPOO_PLANTA_H
#define TRABALHOPOO_PLANTA_H


class Planta {
protected:
    int idade;
    int agua;
    int nutrientes;

public:
    Planta() : idade(0), agua(0), nutrientes(0) {};
    virtual ~Planta() {};

    virtual bool viver(int &aguaSolo,int &nutrientesSolo)=0;
    virtual char getChar() const=0;
    virtual bool feia() const {return false;}
    virtual int getPreco() const=0;
    virtual Planta* duplicar() =0;
    virtual Planta* clone() const =0;

    int getIdade() const {return idade;};
    int getAgua() const {return agua;};
    int getNutrientes() const {return nutrientes;};
};


#endif //TRABALHOPOO_PLANTA_H