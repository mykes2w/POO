#include "Ferramenta.h"

int Ferramenta::proxID=1;

Ferramenta::Ferramenta(int q) :quantidade(q) {
    id=proxID++;
}

