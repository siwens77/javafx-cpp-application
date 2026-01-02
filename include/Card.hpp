#pragma once
#include <string>
#include "Player.hpp"
#include <algorithm>

class Player;

class Card {
private:
    std::string name;
    std::string description;
    double probability;
    int powerHit, powerHeal, powerPower, powerSpeed;

public:
    Card(std::string n, std::string desc, double prob, int powHit, int powHeal, int powPow, int powSpeed);
    ~Card();

    void hit(const Player &abuser, Player &victim);
    void heal(const Player &abuser, Player &victim);
    void increasePower(const Player &increaser, Player &target);
    void increaseSpeed(const Player &increaser, Player &target);

    double getProbability() const;
    std::string getDescription() const;
    std::string getName() const;
};
