#ifndef AQUARIUM_FIELD_H
#define AQUARIUM_FIELD_H

#pragma once

#include <vector>
#include "Creature.h"
#include "Cell.h"
#include <algorithm>
#include <iostream>
#include <queue>

class Field {
public:
    Field();
    void printField();
    std::vector<Creature*> getCreatureList();
    long getCreatureNumber();
    void setNewCreature(Creature*,bool que = false);
    void removeCreature(Creature*);
    int getSize();
    Creature* getInstance(int,int);
    void liveFun();
    bool isExist(Creature*);
    void shift(Creature*,int,int);

private:
    void generateFirst();
    long creatureNumber = 0;
    std::vector<Creature*> creatureList = std::vector<Creature*>();
    std::queue<Creature*> q = std::queue<Creature*>();
    Cell field[10][10];
    int size = 10;
    int iteration = 0;
};


#endif //AQUARIUM_FIELD_H
