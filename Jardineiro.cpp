#include "Jardineiro.h"

Jardineiro::Jardineiro():
    linha(0),
    coluna(0),
    dinheiro(SALDO_INICIAL),
    contMov(0),
    contColheitas(0),
    contPlantacoes(0),
    entrouTurno(false),
    saiuTurno(false)
{
    ferramentaMao=nullptr;
    dentro=false;
}

Jardineiro::~Jardineiro() {
    for (auto f:mochila) delete f;
    mochila.clear();
}

int Jardineiro::getLinha() const {return linha;}
int Jardineiro::getColuna() const {return coluna;}
char Jardineiro::getChar() const {return '*';}

void Jardineiro::setPosicao(int l, int c) {
    linha=l;
    coluna=c;
}

void Jardineiro::apanharFerramenta(Ferramenta *f) {
    if (f!=nullptr) mochila.push_back(f);
}

Ferramenta* Jardineiro::getFerramenta(int index) const {
    if (index>=0 && index < (int)mochila.size()) {
        return mochila[index];
    }
    return nullptr;
}

int Jardineiro::getNumFerramentas() const {
    return (int)mochila.size();
}

int Jardineiro::getDinheiro() const {
    return dinheiro;
}
void Jardineiro::gastarDinheiro(int valor) {
    if (valor>0) dinheiro-=valor;
}
void Jardineiro::receberDinheiro(int valor) {
    if (valor>=0) dinheiro+=valor;
}

int Jardineiro::getMov() const {
    return contMov;
}
void Jardineiro::registarMov() {
    contMov++;
}
int Jardineiro::getColheitas() const {
    return contColheitas;
}
void Jardineiro::registarColheitas() {
    contColheitas++;
}
int Jardineiro::getPlantacoes() const {
    return contPlantacoes;
}
void Jardineiro::registarPlantacoes() {
    contPlantacoes++;
}

void Jardineiro::prepNovoTurno() {
    contMov=0;
    contColheitas=0;
    contPlantacoes=0;
    entrouTurno = false;
    saiuTurno = false;
}

Ferramenta* Jardineiro::largarFerramenta(int index) {
    if (index>=0 && index < (int)mochila.size()) {
        Ferramenta* f = mochila[index];
        if (f==ferramentaMao) ferramentaMao=nullptr;
        mochila.erase(mochila.begin()+index);
        return f;
    }
    return nullptr;
}

Ferramenta* Jardineiro::procurarPorID(int idProcurado) {
    for (Ferramenta* f : mochila) {
        if (f->getId()==idProcurado) return f;
    }
    return nullptr;
}

void Jardineiro::removerFerrGasta(Ferramenta* f) {
    if (f==nullptr) return;

    for (auto it=mochila.begin();it!=mochila.end();it++) {
        if (*it==f) {
            if (f== ferramentaMao) ferramentaMao=nullptr;
            delete *it;
            mochila.erase(it);
            return;
        }
    }
}








