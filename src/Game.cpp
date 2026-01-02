#include "Game.hpp"
#include <algorithm>
#include "utils.hpp" 

Game::Game() {
    clearFiles();
    cards = initializeCards();
    enemies = initializeEnemies();
    hero = std::make_unique<Player>(100, 100, "hero", 30);
    updatePlayersInfo(enemies, *hero);
    initializePlayerCards(cards, *hero);
}

void Game::run() {
    bool allDead = false, heroDead = false;
    while(!allDead && !heroDead){
        playTurn(enemies, *hero, cards);
        allDead = checkIfEnemiesDead(enemies);
        heroDead = checkIfHeroDead(*hero);
        writeGameOver("N");
    }
    if(allDead) writeGameOver("W");
    else writeGameOver("L");

    updatePlayersInfo(enemies, *hero);
}
