#pragma once
#include <string>
#include <vector>
#include <type_traits>
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
    template <typename T>
    void setHealth(T h);
    template <typename T>
    void setPower(T p);
    template <typename T>
    void setSpeed(T s);
    void setCards(const std::vector<Card> c);
};

template <typename T>
void Player::setHealth(T h) {
    static_assert(std::is_arithmetic_v<T>, "Health must be int or double or long");
    health = static_cast<int>(h);
}
template <typename T>
void Player::setPower(T p) {
    static_assert(std::is_arithmetic_v<T>, "Power must be int or double or long");
    power = static_cast<int>(p);
}
template <typename T>
void Player::setSpeed(T s) {
    static_assert(std::is_arithmetic_v<T>, "Speed must be int or double or long");
    speed = static_cast<int>(s);
}