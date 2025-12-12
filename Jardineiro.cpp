//
// Created by miigu on 02/11/2025.
//

#include "Jardineiro.h"

Jardineiro::Jardineiro() {
    linha=0;
    coluna=0;
}

int Jardineiro::getLinha() const {return linha;}
int Jardineiro::getColuna() const {return coluna;}

char Jardineiro::getChar() const {return 'J';}

void Jardineiro::setPosicao(int l, int c) {
    linha=l;
    coluna=c;
}

