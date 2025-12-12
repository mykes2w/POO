#include "PlantaExotica.h"

PlantaExotica::PlantaExotica() {

}

char PlantaExotica::getChar() const {
    return 'X';
}

bool PlantaExotica::viver(int &aguaSolo, int &nutrientesSolo) {
    idade++;
    if (aguaSolo> 0) {aguaSolo--;this->agua++;}
    if (nutrientesSolo> 0) {nutrientesSolo--;this->nutrientes++;}
    return true;
}

