#pragma once
#include <string>
#include <vector>
#include "Card.hpp"

class Card;

class Player {
private:
    int health;
    int power;
    int speed;
    std::string name;
    std::vector<Card> cards;

public:
    Player(int h, int p, const std::string &n, int s);
    ~Player();

    int getHealth() const;
    int getPower() const;
    int getSpeed() const;
    std::string getName() const;
    std::vector<Card>& getCards();

    void setHealth(int h);
    void setPower(int p);
    void setSpeed(int s);
    void setCards(const std::vector<Card> c);
};
