#ifndef AQUARIUM_CARNIVORES_H
#define AQUARIUM_CARNIVORES_H

#include "Creature.h"
#include "Field.h"


class Carnivores : public Creature {
public:
    Carnivores(int,int,Field*);
    bool stepForward() override;
    void move() override;
    Creature* breedDescendant() override;
    ~Carnivores() = default;

private:
    Field *field;
};


#endif //AQUARIUM_CARNIVORES_H
