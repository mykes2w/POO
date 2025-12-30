#include "Jardim.h"
#include "Planta.h"
#include <iostream>
#include "ferramentas/Regador.h"
#include "ferramentas/Adubo.h"
#include "ferramentas/Tesoura.h"
using namespace std;

Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    grelha = new Posicao*[linhas];
    for (int i = 0; i < linhas; ++i) {
        grelha[i] = new Posicao[colunas];
    }
    for (int k = 0; k < 3; k++) {
        adicionarFerrRandom();
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
            if (jardineiro!=nullptr&&jardineiro->dentroJardim()&&jardineiro->getLinha() == i && jardineiro->getColuna() == j) {
                cout << jardineiro->getChar() << " ";
            }
            else {
                cout << grelha[i][j].getChar() << " ";
            }
        }
        cout << (char)('A'+ i) <<endl;
    }
    cout << "  ";
    for (int j = 0; j < colunas; ++j) {
        cout << (char)('A' + j) << " ";
    }
    cout << endl;
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

                if (p->getChar() == 'r') {
                    int vizinhosOcupados=0;
                    int vizinhosPossiveis = 0;
                    for (int di = -1; di <= 1; di++) {
                        for (int dj = -1; dj <= 1; dj++) {
                            if (di == 0 && dj == 0) continue;
                            int ni = i + di, nj = j + dj;

                            if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas) {
                                vizinhosPossiveis++;
                                if (grelha[ni][nj].temPlanta()) {
                                    vizinhosOcupados++;
                                }
                            }
                        }
                    }
                    if (vizinhosOcupados == vizinhosPossiveis && vizinhosPossiveis > 0) {
                        grelha[i][j].removerPlanta();
                    }
                }
            }
        }
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (grelha[i][j].temPlanta()) {
                Planta* p = grelha[i][j].getPlanta();

                int aguaSolo = grelha[i][j].getAgua();
                int nutrSolo = grelha[i][j].getNutrientes();

                if (!p->viver(aguaSolo, nutrSolo)) {
                    if (p->getChar() == 'c') {
                        grelha[i][j].setNutrientes(nutrSolo + p->getNutrientes());
                    }
                    else if (p->getChar() == 'r') {
                        grelha[i][j].setNutrientes(nutrSolo + (p->getNutrientes() / 2));
                        grelha[i][j].setAgua(aguaSolo + (p->getAgua() / 2));
                    }

                    grelha[i][j].removerPlanta();
                } else {
                    grelha[i][j].setAgua(aguaSolo);
                    grelha[i][j].setNutrientes(nutrSolo);
                    tentaReproduzir(i, j, p);
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
    int ni=-1,nj=-1;
    bool encontrou=false;

    for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
            if (di == 0 && dj == 0) continue;
            int vi = l + di;
            int vj = c + dj;

            if (vi >= 0 && vi < linhas && vj >= 0 && vj < colunas) {
                if (p->getChar() == 'e') {
                    ni = vi; nj = vj;
                    encontrou = true;
                    break;
                }
                else if (!grelha[vi][vj].temPlanta()) {
                    ni = vi; nj = vj;
                    encontrou = true;
                    break;
                }
            }
        }
        if (encontrou) break;
    }

    if (!encontrou) return;

    Planta* bebe = p->duplicar();
    if (bebe == nullptr) return;

    if (p->getChar() == 'c') {
        int metAgua = p->getAgua() / 2;
        int metNutr = p->getNutrientes() / 2;

        p->setAgua(metAgua);
        p->setNutrientes(metNutr);
        bebe->setAgua(metAgua);
        bebe->setNutrientes(metNutr);
    }
    else if (p->getChar() == 'r') {
        bebe->setNutrientes(Settings::Roseira::nova_nutrientes);
        int aguaParaBebe = (p->getAgua() * Settings::Roseira::nova_agua_percentagem) / 100;
        bebe->setAgua(aguaParaBebe);
        p->setNutrientes(Settings::Roseira::original_nutrientes);
        int aguaRestante = (p->getAgua() * Settings::Roseira::original_agua_percentagem) / 100;
        p->setAgua(aguaRestante);
    }
    else if (p->getChar() == 'e') {
        if (grelha[ni][nj].temPlanta()) {
            grelha[ni][nj].removerPlanta();
        }
    }

    if (grelha[ni][nj].temPlanta()) {
        delete bebe;
    } else {
        grelha[ni][nj].adicionarPlanta(bebe);
    }
}

Jardim::Jardim(const Jardim &outro) : linhas(outro.linhas), colunas(outro.colunas){
    grelha = new Posicao*[linhas];
    for (int i = 0; i < linhas; ++i) {
        grelha[i] = new Posicao[colunas];
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            grelha[i][j].setAgua(outro.grelha[i][j].getAgua());
            grelha[i][j].setNutrientes(outro.grelha[i][j].getNutrientes());

            if (outro.grelha[i][j].temPlanta()) {
                Planta* copiaPlanta = outro.grelha[i][j].getPlanta()->clone();
                grelha[i][j].adicionarPlanta(copiaPlanta);
            }

            if (outro.grelha[i][j].temFerramenta()) {
                const Ferramenta* fOriginal = outro.grelha[i][j].getFerramenta();
                Ferramenta* copiaFerramenta = fOriginal->clone();
                grelha[i][j].adicionarFerramente(copiaFerramenta);
            }
        }
    }
}

Jardim& Jardim::operator=(const Jardim &outro) {
    if (this==&outro) return *this;

    for (int i = 0; i < linhas; ++i) {
        delete[] grelha[i];
    }
    delete[] grelha;

    linhas = outro.linhas;
    colunas = outro.colunas;

    grelha= new Posicao*[linhas];
    for (int i = 0; i < linhas; ++i) {
        grelha[i] = new Posicao[colunas];
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            grelha[i][j].setAgua(outro.grelha[i][j].getAgua());
            grelha[i][j].setNutrientes(outro.grelha[i][j].getNutrientes());

            if (outro.grelha[i][j].temPlanta()) {
                Planta* copiaPlanta = outro.grelha[i][j].getPlanta()->clone();
                grelha[i][j].adicionarPlanta(copiaPlanta);
            }

            if (outro.grelha[i][j].temFerramenta()) {
                const Ferramenta* fOriginal = outro.grelha[i][j].getFerramenta();
                Ferramenta* copiaFerramenta = fOriginal->clone();
                grelha[i][j].adicionarFerramente(copiaFerramenta);
            }
        }
    }

    return *this;
}

void Jardim::adicionarFerrRandom() {
    int l,c;
    for (int i=0;i<100;i++) {
        l=rand()%linhas;
        c=rand()%colunas;
        if (!grelha[l][c].temFerramenta()) {
            int tipo=rand()%3;
            Ferramenta* nova=nullptr;
            if (tipo==0) {
                nova =new Regador();
            }else if (tipo==1) {
                nova = new Adubo();
            }else {
                nova = new Tesoura();
            }
            grelha[l][c].adicionarFerramente(nova);
            return;
        }
    }
}
