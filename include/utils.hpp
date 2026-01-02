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

std::vector<Card> initializeCards();
std::vector<Player> initializeEnemies();

void initializePlayerCards(vector<Card> &cards, Player &hero);

void updatePlayersInfo( std::vector<Player> &enemies,  Player &hero);

void playTurn(std::vector<Player> &enemies, Player &hero, std::vector<Card> cards);

bool checkIfEnemiesDead( std::vector<Player> &enemies);
bool checkIfHeroDead(Player &hero);

void clearFiles();
void writeGameOver(std::string result);
