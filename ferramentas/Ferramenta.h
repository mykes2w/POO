#ifndef TRABALHOPOO_FERRAMENTA_H
#define TRABALHOPOO_FERRAMENTA_H

class Posicao;

class Ferramenta {
private:
    int quantidade;
    int id;
    static int proxID;
public:
    Ferramenta(int q);
    virtual ~Ferramenta() {}
    int getId() const{return id;}
    int getQuantidade() const{return quantidade;}
    void setQuantidade(int q) { quantidade = q; }
    virtual char getChar() const=0;
    virtual bool usar(Posicao* p)=0;
    virtual Ferramenta* clone() const=0;
};

#endif //TRABALHOPOO_FERRAMENTA_H