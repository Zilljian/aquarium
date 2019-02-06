#ifndef AQUARIUM_HERBIVORES_H
#define AQUARIUM_HERBIVORES_H
#pragma once

#include "Creature.h"
#include "Field.h"
#include <random>

class Herbivores : public Creature {
public:
    Herbivores(int,int,Field*);
    bool stepForward() override;
    Creature* breedDescendant() override;
    void move() override;
    ~Herbivores() = default;

private:
    Creature* getClosest();
    Creature* checkField(int,int);
    void eat();
    Field* field;
};


#endif //AQUARIUM_HERBIVORES_H
