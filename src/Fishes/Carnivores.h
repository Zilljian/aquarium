#ifndef AQUARIUM_CARNIVORES_H
#define AQUARIUM_CARNIVORES_H

#include "Creature.h"
#include "Field.h"
#include <random>

class Carnivores : public Creature {
public:
    Carnivores(int,int,Field*);
    bool stepForward() override;
    Creature* breedDescendant() override;
    void move() override;
    ~Carnivores() = default;

private:
    Creature* getClosest();
    Creature* checkField(int,int);
    void eat();
    Field* field;
};


#endif //AQUARIUM_CARNIVORES_H
