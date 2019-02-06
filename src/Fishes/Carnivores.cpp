#include "Carnivores.h"

Carnivores::Carnivores(int x, int y, Field* initField) : Creature(15, 30, 5, x, y,"Carnivores") {
    field = initField;
    setHunger(10);
}

bool Carnivores::stepForward() {
    if(isAlive()) {
        liveTime++;
        hunger++;
        if (isDeathTime() || isHungerDeath()) {
            field->removeCreature(this);
            field->carnivores--;
        } else {
            move();
            return true;
        }
    }
    return false;
}

void Carnivores::move() {
    int prevX = xPos;
    int prevY = yPos;
    bool isLeft = random()%2 == 0;
    bool isUp = random()%2 == 0;

    if (hunger < 7) {
        bool isStand = random()%2 == 0;

        if (!isStand) {
            if (isLeft) {
                if (xPos - 1 > 0) xPos -= 1;
                else xPos += 1;
            } else {
                if (xPos + 1 < field->getSize()) xPos += 1;
                else xPos -= 1;
            }

            if (isUp) {
                if (yPos - 1 > 0) yPos -= 1;
                else yPos += 1;
            } else {
                if (yPos + 1 < field->getSize()) yPos += 1;
                else yPos -= 1;
            }
        }
    } else {
        Creature* tmp = getClosest();

        if (tmp != nullptr) {
            int deltaX = xPos - tmp->getX();
            int deltaY = yPos - tmp->getY();

            if (deltaX > 0) xPos -= 1;
            else if (deltaX < 0) xPos += 1;

            if (deltaY > 0) yPos -= 1;
            else if (deltaY < 0) yPos += 1;

            if (deltaX == 0 && deltaY == 0)
                eat();
        } else {
            if (isLeft) {
                if (xPos - 1 > 0) xPos -= 1;
                else xPos += 1;
            } else {
                if (xPos + 1 < field->getSize()) xPos += 1;
                else xPos -= 1;
            }

            if (isUp) {
                if (yPos - 1 > 0) yPos -= 1;
                else yPos += 1;
            } else {
                if (yPos + 1 < field->getSize()) yPos += 1;
                else yPos -= 1;
            }
        }
    }
    field->shift(this, prevX, prevY);
}

Creature* Carnivores::breedDescendant() {
    int xShift = random()%10;
    int yShift = random()%10;

    if(liveTime % BREEDING_TIME != 0) return nullptr;

    while(xPos + xShift >= field->getSize() || xPos + xShift < 0
          || yPos + yShift >= field->getSize() || yPos + yShift < 0) {
        xShift = random()%10;
        yShift = random()%10;
    }
    return new Carnivores(xPos + xShift, yPos + yShift, field);
}

Creature* Carnivores::getClosest() {
    Creature* tmpInstance;
    tmpInstance = checkField(0, 0);
    if (tmpInstance != nullptr) return tmpInstance;
    return checkField(0,5);
}

void Carnivores::eat() {
    field->removeCreature(getClosest());
    field->herbivores--;
    hunger -= 7;
}

Creature* Carnivores::checkField(int initShift, int maxShift) {
    if (initShift == 0 && maxShift == 0)
        return field->getInstance(xPos, yPos, "Herbivores");

    for (int i = 0; i < maxShift; i++) {
        for (int j = 0; j < maxShift; j++) {
            if (field->getInstance(j + xPos, i + yPos, "Herbivores") != nullptr)
                return field->getInstance(j + xPos, i + yPos, "Herbivores");
            if (field->getInstance(xPos - j, i + yPos, "Herbivores") != nullptr)
                return field->getInstance(xPos - j, i + yPos, "Herbivores");
            if (field->getInstance(j + xPos, yPos - i, "Herbivores") != nullptr)
                return field->getInstance(j + xPos, yPos - i, "Herbivores");
            if (field->getInstance(xPos - j, yPos - i, "Herbivores") != nullptr)
                return field->getInstance(xPos - j, yPos  - i, "Herbivores");

            if (field->getInstance(xPos, yPos - i, "Herbivores") != nullptr)
                return field->getInstance(xPos, yPos - i, "Herbivores");
            if (field->getInstance(xPos, yPos + i, "Herbivores") != nullptr)
                return field->getInstance(xPos, yPos + i, "Herbivores");

            if (field->getInstance(xPos - j, yPos, "Herbivores") != nullptr)
                return field->getInstance(xPos - j, yPos, "Herbivores");
            if (field->getInstance(xPos + j, yPos, "Herbivores") != nullptr)
                return field->getInstance(xPos + j, yPos, "Herbivores");

        }
    }

    int xBoarder = xPos - maxShift;

    if (xBoarder < 0) xBoarder = 0;
    else if (xBoarder > field->getSize()) xBoarder = field->getSize() - 1;

    int yBoarder = yPos - maxShift;

    if (yBoarder < 0) yBoarder = 0;
    else if (yBoarder > field->getSize()) yBoarder = field->getSize() - 1;



    for (int i = 0; i < maxShift; i++) {
        for (int j = 0; j < maxShift; j++) {
            if (field->getInstance(j + xBoarder, i + yBoarder, "Herbivores") != nullptr)
                return field->getInstance(j + xBoarder, i + yBoarder, "Herbivores");
        }
    }

    return nullptr;
}
