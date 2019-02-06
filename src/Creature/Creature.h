#ifndef AQUARIUM_CREATURE_H
#define AQUARIUM_CREATURE_H
#pragma once

#include <string>

class Creature {
public:
    Creature(int,int,int,int,int,std::string);
    bool isAlive();
    bool isDeathTime();
    bool isBreedingTime();
    std::string getType();
    void setDead();
    int getX();
    int getY();
    bool isHungerDeath();
    void setHunger(int);

    virtual Creature* breedDescendant() = 0;
    virtual void move() = 0;
    virtual bool stepForward() = 0;
    ~Creature() = default;

protected:
    bool aliveParam = true;
    int liveTime = 0;
    int BREEDING_TIME = 0;
    int hunger;
    int MAX_HUNGER = 6;
    int LIVE_TIME;
    int xPos;
    int yPos;
    std::string type;
};


#endif //AQUARIUM_CREATURE_H
