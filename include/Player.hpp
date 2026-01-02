#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <memory>
#include "Card.hpp"

class Player;
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
    virtual ~Player();
    virtual void makeTurn(std::vector<Player*>& enemies, Player* hero) = 0;

    int getHealth() const;
    int getPower() const;
    int getSpeed() const;
    std::string getName() const;
    std::vector<Card>& getCards();
    void setHealth(int h){health=h;};
    void setPower(int p){power=p;};
    void setSpeed(int s){speed=s;};
    void setCards(const std::vector<Card> c);
};

class Hero : public Player{
    public:
    using Player::Player;
    void makeTurn(std::vector<Player*>&enemies, Player* hero)override;
};
class Healer : public Player{
    public:
    using Player::Player;
    void makeTurn(std::vector<Player*>&enemies, Player* hero)override;
};
class Warrior : public Player{
    public:
    using Player::Player;
    void makeTurn(std::vector<Player*>&enemies, Player* hero)override;
};
class Wizard : public Player{
    public:
    using Player::Player;
    void makeTurn(std::vector<Player*>&enemies, Player* hero)override;
};

#endif