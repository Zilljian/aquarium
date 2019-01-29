#include "Field.h"
#include <stdlib.h>
#include <cstdlib>
#include <thread>
#include <chrono>


Field::Field() {
   for (int i = 0; i < getSize(); i++) {
       for (int j = 0; j < getSize(); j++) {
           field[i][j] = Cell();
       }
   }
}

void Field::printField() {
    std::system("clear");
    std::cout << "Iteration " << ++iteration << std::endl;
    for (int i = 0; i < getSize(); i++) {
        for (int j = 0; j < getSize(); j++) {
            if(!field[i][j].plankton.empty()) std::cout << "0 ";
            else std::cout << "# ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

std::vector<Creature*> Field::getCreatureList() {
    return creatureList;
}

long Field::getCreatureNumber() {
    return creatureNumber;
}

void Field::setNewCreature(Creature* newInstance, bool que) {
    if (newInstance == nullptr) return;

    if (newInstance->getType() == "Plankton") {
        field[newInstance->getY()][newInstance->getX()]
        .plankton.push_back(newInstance);
    } else if (newInstance->getType() == "Carnivores") {
        field[newInstance->getY()][newInstance->getX()]
        .carnivores.push_back(newInstance);
    } else if (newInstance->getType() == "Herbivores") {
        field[newInstance->getY()][newInstance->getX()]
        .herbivores.push_back(newInstance);
    }
    if (!que) q.push(newInstance);
    creatureList.push_back(newInstance);
    creatureNumber++;
}

void Field::removeCreature(Creature* instance) {
    if (std::find(creatureList.begin(), creatureList.end(), instance) != creatureList.end()) {

        int x = instance->getX();
        int y = instance->getY();

        creatureList.erase(std::remove(creatureList.begin(), creatureList.end(), instance), creatureList.end());
        creatureNumber--;

            if (instance->getType() == "Plankton") {
                field[y][x].plankton.erase(std::remove(field[y][x].plankton.begin(),field[y][x].plankton.end(), instance), field[y][x].plankton.end());

            } else if (instance->getType() == "Carnivores") {
                field[y][x].plankton.erase(std::remove(field[y][x].plankton.begin(),field[y][x].plankton.end(), instance), field[y][x].plankton.end());

            } else if (instance->getType() == "Herbivores") {
                field[y][x].plankton.erase(std::remove(field[y][x].plankton.begin(),field[y][x].plankton.end(), instance), field[y][x].plankton.end());
            }

    }
}

int Field::getSize() {
    return size;
}

void Field::generateFirst() {

}

void Field::liveFun() {
    std::queue<Creature*> tmp;

    while (!q.empty()) {
        int currentX = q.front()->getX();
        int currentY = q.front()->getY();

        if (q.front()->stepForward()) {
            tmp.push(q.front());

            if (currentX != q.front()->getX() || currentY != q.front()->getY()) {

            }

            Creature* t = q.front()->breedDescendant();
            if (t != nullptr) {
                setNewCreature(t, true);
                tmp.push(t);
            }
        }
        q.pop();
    }
    printField();
    q = tmp;
}

Creature *Field::getInstance(int, int) {
    return nullptr;
}

bool Field::isExist(Creature *instance) {
    if (instance->getType() == "Plankton") {
        return std::find(
                field[instance->getY()][instance->getX()].plankton.begin(),
                field[instance->getY()][instance->getX()].plankton.end(),
                instance) != field[instance->getY()][instance->getX()].plankton.end();

    } else if (instance->getType() == "Carnivores") {
        return std::find(
                field[instance->getY()][instance->getX()].carnivores.begin(),
                field[instance->getY()][instance->getX()].carnivores.end(),
                instance) != field[instance->getY()][instance->getX()].carnivores.end();

    } else if (instance->getType() == "Herbivores") {
        return std::find(
                field[instance->getY()][instance->getX()].herbivores.begin(),
                field[instance->getY()][instance->getX()].herbivores.end(),
                instance) != field[instance->getY()][instance->getX()].herbivores.end();
    }
    return false;
}

void Field::shift(Creature *newInstance, int x, int y) {
    field[y][x].remove(newInstance);
    
    if (newInstance->getType() == "Plankton") {
        field[newInstance->getY()][newInstance->getX()]
                .plankton.push_back(newInstance);
    } else if (newInstance->getType() == "Carnivores") {
        field[newInstance->getY()][newInstance->getX()]
                .carnivores.push_back(newInstance);
    } else if (newInstance->getType() == "Herbivores") {
        field[newInstance->getY()][newInstance->getX()]
                .herbivores.push_back(newInstance);
    }
}
