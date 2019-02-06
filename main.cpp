#include <iostream>
#include "Field.h"
#include "Plankton.h"
#include "Carnivores.h"
#include "Herbivores.h"



int main() {
    Field field = Field();

    for (int i = 0; i < 20; i++) {
        field.setNewCreature(new Plankton(random() % field.getSize(), random() % field.getSize(), &field));
        field.setNewCreature(new Plankton(random() % field.getSize(), random() % field.getSize(), &field));
        field.setNewCreature(new Plankton(random() % field.getSize(), random() % field.getSize(), &field));
        field.setNewCreature(new Plankton(random() % field.getSize(), random() % field.getSize(), &field));
        field.setNewCreature(new Herbivores(random() % field.getSize(), random() % field.getSize(), &field));
        field.setNewCreature(new Herbivores(random() % field.getSize(), random() % field.getSize(), &field));
        field.setNewCreature(new Herbivores(random() % field.getSize(), random() % field.getSize(), &field));
        field.setNewCreature(new Carnivores(random() % field.getSize(), random() % field.getSize(), &field));
        field.setNewCreature(new Carnivores(random() % field.getSize(), random() % field.getSize(), &field));
    }

    field.run();

    getchar();
}