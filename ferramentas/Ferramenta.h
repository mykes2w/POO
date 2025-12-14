#ifndef TRABALHOPOO_FERRAMENTA_H
#define TRABALHOPOO_FERRAMENTA_H

class Posicao;

class Ferramenta {
protected:
    int quantidade;
public:
    Ferramenta(int q) : quantidade(q) {}
    virtual ~Ferramenta() {}
    virtual char getChar() const=0;
    virtual bool usar(Posicao* p)=0;
    virtual Ferramenta* clone() const=0;
    int getQuantidade() const{return quantidade;}
};

#endif //TRABALHOPOO_FERRAMENTA_H