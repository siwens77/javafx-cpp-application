#ifndef UTILS_HPP
#define UTILS_HPP
#include "Player.hpp"
#include <vector>
using namespace std;

enum class Picked{
    hero = -1,
    healer = 0,
    warrior = 1,
    wizard = 2
};

vector<Card> initializeCards();
vector<Player*> initializeEnemies();
void initializePlayerCards(vector<Card> &cards, Player *hero);
void updatePickedCards(Player *hero);
void updatePlayersInfo(vector<Player*> &enemies,  Player *hero);
int pickPlayer(vector<Player*> &enemies, Player *hero);
bool checkIfEnemiesDead(vector<Player*> &enemies);
bool checkIfHeroDead(Player *hero);
void playTurn(std::vector<Player*> &enemies, Player *hero, vector<Card> cards);
bool checkIfEnemiesDead( std::vector<Player> &enemies);
bool checkIfHeroDead(Player *hero);
void writeWhoseTurn(int picked);
void clearFiles();
void writeGameOver(string result);
void waitUntilNextTurn();
void waitUntilNextTurn2();

#endif