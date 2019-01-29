#include "Herbivores.h"

Herbivores::Herbivores(int x, int y, Field* initField) : Creature(10, 30, 5, x, y, "Herbivores") {
    field = initField;
}

bool Herbivores::stepForward() {
    Creature::stepForward();
}


void Herbivores::move() {

}

Creature *Herbivores::breedDescendant() {
    return nullptr;
}
