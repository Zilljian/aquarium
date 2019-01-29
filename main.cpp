#include <iostream>
#include "Field.h"
#include "Plankton.h"
#include "Carnivores.h"



int main() {
    Field field = Field();

    field.setNewCreature(new Plankton(0, 0, &field));
    //field.setNewCreature(new Herbivores(0, 0, &field));
    //field.setNewCreature(new Carnivores(0, 0, &field));

    int counter = 20;
    while(counter-- > 0) {
        field.liveFun();
    }
}