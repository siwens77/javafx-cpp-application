#pragma once
#include <vector>
#include <memory>
#include "Player.hpp"
#include "Card.hpp"

class Game {
private:
    std::vector<Card> cards;
    std::vector<Player> enemies;
    std::unique_ptr<Player> hero;

public:
    Game();
    void run();
};
