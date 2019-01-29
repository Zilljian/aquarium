#include "Cell.h"

bool Cell::remove(Creature *instance) {
    if (instance->getType() == "Plankton") {
        plankton.erase(std::remove(plankton.begin(),plankton.end(), instance), plankton.end());
        return true;

    } else if (instance->getType() == "Carnivores") {
        carnivores.erase(std::remove(carnivores.begin(), carnivores.end(), instance), carnivores.end());
        return true;

    } else if (instance->getType() == "Herbivores") {
        herbivores.erase(std::remove(herbivores.begin(), herbivores.end(), instance), herbivores.end());
        return true;
    }
    return false;
}
