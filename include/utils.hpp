#pragma once
#include <vector>
#include <string>
#include "Card.hpp"
#include "Player.hpp"
using namespace std;

enum class Picked{
    hero = -1,
    healer = 3,
    warrior = 2,
    wizard = 1
};

vector<Card> initializeCards();
vector<Player> initializeEnemies();

void initializePlayerCards(vector<Card> &cards, Player &hero);

void updatePlayersInfo(vector<Player> &enemies,  Player &hero);

void playTurn(std::vector<Player> &enemies, Player &hero, vector<Card> cards);

bool checkIfEnemiesDead( std::vector<Player> &enemies);
bool checkIfHeroDead(Player &hero);

void clearFiles();
void writeGameOver(string result);
