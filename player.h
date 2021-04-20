#ifndef PLAYER_H
#define PLAYER_H

#include <sstream>

using namespace std;

class Player {
    public:
    Player(unsigned int health, unsigned int hunger, unsigned int thirst, unsigned int x, unsigned int y);
    unsigned int getX() const;
    unsigned int getY() const;
    void setX(unsigned int newX);
    void setY(unsigned int newY);
    unsigned int getHunger() const;
    unsigned int getThirst() const;
    unsigned int getHealth() const;
    void setThirst(unsigned int t);
    void setHunger(unsigned int h);
    void setHealth(unsigned int h);
    void newTurn();
    string printStats();
    bool isAlive() const;
    bool havePet(int number);
    bool checkPet();
    
    static const unsigned int DEFAULT_HEALTH = 7;
    static const unsigned int DEFAULT_HUNGER = 10;
    static const unsigned int DEFAULT_THIRST = 10;
    
    private:
    bool pet = false;
    unsigned int health;
    unsigned int hunger;
    unsigned int thirst;
    unsigned int x;
    unsigned int y;
};

#endif