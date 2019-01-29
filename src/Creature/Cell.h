#ifndef AQUARIUM_CELL_H
#define AQUARIUM_CELL_H

#include "Creature.h"
#include <vector>
#include <algorithm>


class Cell {
public:
    std::vector<Creature*> plankton = std::vector<Creature*>();
    std::vector<Creature*> herbivores = std::vector<Creature*>();
    std::vector<Creature*> carnivores = std::vector<Creature*>();

    bool remove(Creature*);
};


#endif //AQUARIUM_CELL_H
