#ifndef AQUARIUM_HERBIVORES_H
#define AQUARIUM_HERBIVORES_H
#pragma once


#include "Creature.h"
#include "Field.h"

class Herbivores : public Creature {
public:
    Herbivores(int,int,Field*);
    bool stepForward() override;
    Creature* breedDescendant() override;
    ~Herbivores() = default;

protected:
    void move() override;

private:
    Field *field;
};


#endif //AQUARIUM_HERBIVORES_H
