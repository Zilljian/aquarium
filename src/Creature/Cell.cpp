#include "Cell.h"

bool Cell::remove(Creature *instance) {
    if (instance->getType() == "Plankton") {
        plankton.erase(std::remove(plankton.begin(),plankton.end(), instance), plankton.end());
        //delete instance;
        return true;

    } else if (instance->getType() == "Carnivores") {
        carnivores.erase(std::remove(carnivores.begin(), carnivores.end(), instance), carnivores.end());
        //delete instance;
        return true;

    } else if (instance->getType() == "Herbivores") {
        herbivores.erase(std::remove(herbivores.begin(), herbivores.end(), instance), herbivores.end());
        //delete instance;
        return true;
    }
    return false;
}
