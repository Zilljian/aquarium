#include "Plankton.h"

Plankton::Plankton(int x, int y, Field* initField) : Creature(0, 20, 4, x, y, "Plankton"){
    field = initField;
}

bool Plankton::stepForward() {
    if(aliveParam) {
        liveTime++;
        if (liveTime >= LIVE_TIME) {
            field->removeCreature(this);
            field->plankton--;
        } else {
            move();
            return true;
        }
    }
    return false;
}

Creature* Plankton::breedDescendant() {
    int xShift = random()%10;
    int yShift = random()%10;
    bool isTime = true; //random()%2 == 0;

    if(liveTime % BREEDING_TIME != 0 || !isTime) return nullptr;

    while(xPos + xShift >= field->getSize() || xPos + xShift < 0
    || yPos + yShift >= field->getSize() || yPos + yShift < 0) {
        xShift = random()%10;
        yShift = random()%10;
    }
    return new Plankton(xPos + xShift, yPos + yShift, field);
}

void Plankton::move() {
    bool isStand = random()%2 == 0;
    bool isLeft = random()%2 == 0;
    bool isUp = random()%2 == 0;
    int nextY;
    int nextX;

    if(!isStand && liveTime % 5 == 0) {
        if (isLeft) {
            if (xPos - 1 > 0) nextX = xPos - 1;
            else nextX = xPos + 1;
        } else {
            if (xPos + 1 < field->getSize()) nextX = xPos + 1;
            else nextX = xPos - 1;
        }

        if (isUp) {
            if (yPos - 1 > 0) nextY = yPos - 1;
            else nextY = yPos + 1;
        } else {
            if (yPos + 1 < field->getSize()) nextY = yPos + 1;
            else nextY = yPos - 1;
        }

        int prevX = xPos;
        int prevY = yPos;

        xPos = nextX;
        yPos = nextY;
        field->shift(this, prevX, prevY);
    }
}
