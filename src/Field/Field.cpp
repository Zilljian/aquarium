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

Field::Field(int number) {

}

void Field::printField() {
    std::system("clear");
    std::cout << "Iteration " << ++iteration << std::endl << "Number: " << creatureNumber << std::endl;
    std::cout << "Plankton: " << plankton << std::endl;
    std::cout << "Herbivores: " << herbivores << std::endl;
    std::cout << "Carnivores: " << carnivores << std::endl;
    std::cout << std::string(getSize() * 2 + 2, '=') << std::endl;

    for (int i = 0; i < getSize(); i++) {
        for (int j = 0; j < getSize(); j++) {
            if (j == 0) std::cout << '|';

            if (field[i][j].herbivores.empty() && field[i][j].carnivores.empty() && field[i][j].plankton.empty())
                std::cout << "  ";
            else if (field[i][j].herbivores.size() >= field[i][j].carnivores.size()
            && field[i][j].herbivores.size() >= field[i][j].plankton.size())
                std::cout << "H ";
            else if(field[i][j].carnivores.size() >= field[i][j].plankton.size()
            && field[i][j].carnivores.size() >= field[i][j].herbivores.size())
                std::cout << "C ";
            else
                std::cout << "O ";

            if (j == getSize() - 1) std::cout << '|';
        }
        std::cout << std::endl;
    }

    std::cout << std::string(getSize() * 2 + 2, '=') << std::endl;
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
        plankton++;
    } else if (newInstance->getType() == "Carnivores") {
        field[newInstance->getY()][newInstance->getX()]
        .carnivores.push_back(newInstance);
        carnivores++;
    } else if (newInstance->getType() == "Herbivores") {
        field[newInstance->getY()][newInstance->getX()]
        .herbivores.push_back(newInstance);
        herbivores++;
    }
    if (!que) q.push(newInstance);
    creatureList.push_back(newInstance);
    creatureNumber++;
}

void Field::removeCreature(Creature* instance) {
    if (std::find(creatureList.begin(), creatureList.end(), instance) != creatureList.end()) {
        field[instance->getY()][instance->getX()].remove(instance);
        creatureList.erase(std::remove(creatureList.begin(), creatureList.end(), instance), creatureList.end());
        creatureNumber--;
        instance->setDead();
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
        if (q.front()->stepForward()) {
            tmp.push(q.front());

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

Creature* Field::getInstance(int x, int y, std::string type) {
    if (isValid(x, y)) {
        if (type == "Plankton") {
            if (!field[y][x].plankton.empty())
                return field[y][x].plankton[0];
        } else if (type == "Herbivores")
            if (!field[y][x].herbivores.empty())
                return field[y][x].herbivores[0];
    }

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

void Field::run(int iter) {
    if (iter == 0) {
        while (creatureNumber != 0)
            liveFun();
    } else {
        while (iter -- > 0)
            liveFun();
    }
}

bool Field::isValid(int x, int y) {
    return x >= 0 && x < getSize() && y >=0 && y < getSize();
}
