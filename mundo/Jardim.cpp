#include "Jardim.h"
#include "Planta.h"
#include <iostream>
using namespace std;

Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    grelha = new Posicao*[linhas];
    for (int i = 0; i < linhas; ++i) {
        grelha[i] = new Posicao[colunas];
    }
}

Jardim::~Jardim() {
    for (int i = 0; i < linhas; ++i) {
        delete[] grelha[i];
    }
    delete[] grelha;
}

void Jardim::desenhar(const Jardineiro* jardineiro) {
    cout << "  ";
    for (int j = 0; j < colunas; ++j) {
        cout << (char)('A' + j) << " ";
    }
    cout << endl;

    for (int i = 0; i < linhas; ++i) {
        cout << (char)('A' + i) << " ";
        for (int j = 0; j < colunas; ++j) {
            if (jardineiro!=nullptr&&jardineiro->getLinha() == i && jardineiro->getColuna() == j) {
                cout << jardineiro->getChar() << " ";
            }
            else {
                cout << grelha[i][j].getChar() << " ";
            }
        }
        cout << endl;
    }
}

bool Jardim::adicionarPlanta(int l, int c, Planta* p) {
    if (l<0 || l>=linhas || c<0 || c>=colunas) {
        return false;
    }
    if (grelha[l][c].temPlanta()) {
        return false;
    }
    grelha[l][c].adicionarPlanta(p);
    return true;
}

int Jardim::getLinhas() const { return linhas; }
int Jardim::getColunas() const {return colunas; }

void Jardim::passarTempo() {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (grelha[i][j].temPlanta()) {
                Planta* p = grelha[i][j].getPlanta();

                int agua = grelha[i][j].getAgua();
                int nutr = grelha[i][j].getNutrientes();

                bool sobreviveu=p->viver(agua, nutr);

                grelha[i][j].setAgua(agua);
                grelha[i][j].setNutrientes(nutr);

                if (!sobreviveu) {
                    cout << "Planta em " << i << " " << j << " morreu" << endl;
                    grelha[i][j].removerPlanta();
                }else {
                    Planta* filho = p->duplicar();
                    if (filho!=nullptr) {
                        tentaReproduzir(i,j,filho);
                    }
                }
            }
        }
    }
}

Posicao* Jardim::getPosicao(int l, int c) const {
    if (l < 0 || l >=linhas || c<0 ||c>= colunas) return nullptr;
    return &grelha[l][c];
}

void Jardim::tentaReproduzir(int l, int c, Planta* p) {
    for (int dl=-1;dl<=1;dl++) {
        for (int dc=-1;dc<=1;dc++) {
            if (dl==0 && dc==0) continue;

            int nl=l+dl;
            int nc=c+dc;

            if (nl>=0 && nl<linhas && nc>=0 && nc<colunas) {
                if (!grelha[nl][nc].temPlanta()) {
                    grelha[nl][nc].adicionarPlanta(p);
                    return;
                }
            }
        }
    }
    delete p;
}

