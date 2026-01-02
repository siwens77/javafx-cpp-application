#include "Card.hpp"
#include "Player.hpp"
using namespace std;

Card::Card(std::string n, std::string desc, double prob, int powHit, int powHeal, int powPow, int powSpeed)
    : name(n), description(desc), probability(prob), powerHit(powHit), powerHeal(powHeal),
      powerPower(powPow), powerSpeed(powSpeed)
{}

Card::~Card() {}

void Card::hit(const Player &abuser, Player &victim) {
    victim.setHealth(std::max(victim.getHealth() - powerHit * abuser.getPower() * 0.01, 0.0));
}

void Card::heal(const Player &abuser, Player &victim) {
    if (victim.getHealth() <= 0) return;
    victim.setHealth(std::min(victim.getHealth() + powerHeal * abuser.getPower() * 0.01, 100.0));
}

void Card::increasePower(const Player &increaser, Player &target) {
    target.setPower(target.getPower() + powerPower * increaser.getPower() * 0.01);
}

void Card::increaseSpeed(const Player &increaser, Player &target) {
    target.setSpeed(target.getSpeed() + powerSpeed * increaser.getPower() * 0.01);
}

double Card::getProbability() const { return probability; }
std::string Card::getDescription() const { return description; }
std::string Card::getName() const { return name; }

void Card::operator()(Player& hero, Player& target) {
    hit(hero, target);
    heal(hero, target);
    increasePower(hero, target);
    increaseSpeed(hero, target);
}