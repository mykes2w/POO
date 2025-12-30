#ifndef TRABALHOPOO_JARDINEIRO_H
#define TRABALHOPOO_JARDINEIRO_H
#include <vector>
#include "Ferramenta.h"


class Jardineiro {

private:
    int linha;
    int coluna;
    std::vector<Ferramenta*> mochila;
    bool dentro;
    int dinheiro,contMov,contColheitas,contPlantacoes;
    Ferramenta* ferramentaMao;
    bool entrouTurno,saiuTurno;
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
    Ferramenta* largarFerramenta(int index);

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
    bool getEntrouTurno() const { return entrouTurno; }
    void setEntrouTurno(bool valor) { entrouTurno=valor; }
    bool getSaiuTurno() const { return saiuTurno; }
    void setSaiuTurno(bool valor) { saiuTurno=valor; }
    bool dentroJardim() const {return dentro;}
    void setDentro(bool d) {dentro=d;}

    void setFerramentaMao(Ferramenta* f){ferramentaMao=f;}
    Ferramenta* getFerramentaMao() const {return ferramentaMao;}
    Ferramenta* procurarPorID(int idProcurado);
    void removerFerrGasta(Ferramenta* f);
};


#endif //TRABALHOPOO_JARDINEIRO_H