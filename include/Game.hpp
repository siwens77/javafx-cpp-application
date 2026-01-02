#ifndef GAME_HPP
#define GAME_HPP
#include <vector>
#include <memory>
#include "Player.hpp"
#include "Card.hpp"

class Game {
private:
    std::vector<Card> cards;
    std::vector<Player*> enemies;
    Player *hero;

public:
    Game();
    ~Game();
    void run();
};

#endif