#ifndef TRABALHOPOO_JARDINEIRO_H
#define TRABALHOPOO_JARDINEIRO_H
#include <vector>
#include "Ferramenta.h"


class Jardineiro {

private:
    int linha;
    int coluna;
    std::vector<Ferramenta*> mochila;
public:
    Jardineiro();

    int getLinha() const;
    int getColuna() const;
    char getChar() const;
    void setPosicao(int l,int c);

    void apanharFerramenta(Ferramenta* f) {
        mochila.push_back(f);
    }

    Ferramenta* getFerramenta(int index) const {
        if (index >= 0 && index < mochila.size()) {
            return mochila[index];
        }
        return nullptr;
    }
    int getNumFerramentas() const {return mochila.size();}
};


#endif //TRABALHOPOO_JARDINEIRO_H