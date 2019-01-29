#include "Plankton.h"

Plankton::Plankton(int x, int y, Field* initField) : Creature(0, 30, 5, x, y, "Plankton"){
    field = initField;
}

bool Plankton::stepForward() {
    if(aliveParam) {
        liveTime++;
        if (liveTime == LIVE_TIME) {
            aliveParam = false;
        } else {
            move();
            return true;
        }
    }
    return false;
}

Creature* Plankton::breedDescendant() {  //TODO Refactor return value and usage
    int xShift = rand()%5;
    int yShift = rand()%5;

    if(liveTime % BREEDING_TIME != 0) return nullptr;

    while(xPos + xShift >= field->getSize() || xPos + xShift < 0
    || yPos + yShift >= field->getSize() || yPos + yShift < 0) {
        xShift = rand()%5;
        yShift = rand()%5;
    }
    return new Plankton(xPos + xShift, yPos + yShift, field);
}

void Plankton::move() {
    bool isStand = rand()%2 == 0;
    bool isLeft = rand()%2 == 0;
    bool isUp = rand()%2 == 0;
    int nextY;
    int nextX;

    if(!isStand) {
        if (isLeft && xPos - 1 > 0) nextX = xPos - 1;
        else if (xPos + 1 < field->getSize())nextX = xPos + 1;
        if (isUp && yPos > 0) nextY = yPos - 1;
        else if(yPos + 1 < field->getSize()) nextY = yPos + 1;
        int prevX = xPos;
        int prevY = yPos;
        xPos = nextX;
        yPos = nextY;
        //field->removeCreature(this);
        field->shift(this, prevX, prevY);
        field->setNewCreature(this, true);
    }
}
