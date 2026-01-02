#include "Player.hpp"
using namespace std;

Player::Player(int h, int p, const std::string &n, int s) : health(h), power(p), name(n), speed(s) {}
Player::~Player() {}

int Player::getSpeed()const { return speed; }
int Player::getHealth()const { return health; }
int Player::getPower()const{ return power; }
string Player::getName()const{ return name; }
vector<Card>& Player::getCards(){ return cards; }

void Player::setSpeed(int s){ speed = s; }
void Player::setPower(int p){ power = p; }
void Player::setCards(vector<Card> c) { cards = c; }
