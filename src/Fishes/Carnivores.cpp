#include "Carnivores.h"

Carnivores::Carnivores(int x, int y, Field* initField) : Creature(10, 10, 6, x, y,"Carnivores") {
    field = initField;
}

bool Carnivores::stepForward() {
    if(aliveParam) {
        liveTime++;
        if (liveTime == LIVE_TIME) aliveParam = false;
        else {
            move();
            return true;
        }
    }
    return false;
}

void Carnivores::move() {

}

Creature* Carnivores::breedDescendant() {

}
