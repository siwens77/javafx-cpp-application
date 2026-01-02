#include "utils.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <numeric>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;

void updatePlayersInfo(std::vector<Player*> &enemies,Player *hero){
    ofstream outFile2("statistics.tmp");
    if(!outFile2.is_open()){
        cerr << "ERROR IN OPENING TMP FILE STATISTICS!";
        return;
    }
    outFile2<< hero->getHealth()<< " "<<hero->getPower()<< " "<<hero->getSpeed()<<endl;
    for(int i = 0;i<3; i++){
        outFile2<< enemies[i]->getHealth() << " "<< enemies[i]->getPower()<<" "<<enemies[i]->getSpeed()<<endl;
        if(outFile2.fail()){
            cerr << "ERROR IN WRITING TO TMP FILE STATISTICS!";
        }
    }
    outFile2.close();
    if(rename("statistics.tmp", "statistics.txt") != 0) {
        cerr << "ERROR RENAMING statistics.tmp TO statistics.txt\n";
    }

}

void updatePickedCards(Player *hero){
    vector<Card>cards = hero->getCards();
    ofstream outFile("cards.tmp");
    if(!outFile.is_open()){
        cerr << "ERROR IN OPENING TMP FILE CARDS!";
        return;
    }
    for(int i = 0 ; i<cards.size(); i++){
        outFile<< "resources/images/"<<cards[i].getName()<< ".png"<<endl;
        outFile<< cards[i].getDescription()<<endl;
        if(outFile.fail()){
            cerr << "ERROR IN WRITING TO TMP FILE CARDS!";
        }
    }
    if(rename("cards.tmp", "cards.txt") != 0) {
        cerr << "ERROR RENAMING cards.tmp TO cards.txt\n";
    }
}

void clearFiles() {
    const char* files[] = {"clickedCard.txt", "statistics.txt", "clickedCat.txt","whosturn.txt"};
    for (const char* file : files) {
        ofstream out(file, ios::trunc);
        if (!out) {
            cerr << "ERROR, COULDNT OPEN FILE '" << file << "' FOR CLEARING\n";
            continue;
        }
        out.close();
    }
}

vector<Card> initializeCards() {
    vector<Card> cards;
    //Card(name, description, probability, hit, heal, power, speed)
    Card hitCard("hit", "common card hitting for 5p", 1, 5, 0, 0,0);
    Card goldHitCard("goldHit", "rare card hitting for 20p", 1, 20, 0, 0,0);
    Card healCard("heal" ,"common card healing 10p", 1,0,20,0,0);
    Card goldHealCard("goldHeal", "rare card healing 50p", 1,0,50,0,0); 
    Card powerCard("power", "common card increasing power by 25p", 1,0,0,25,0);
    Card goldPowerCard("goldPower", "rare card increasing power by 50p", 1,0,0,50,0);
    Card speedCard("speed", "common card increasing speed by 20p", 1,0,0,0,20);
    Card goldSpeedCard("goldSpeed", "common card increasing speed by 400p", 1,0,0,0,40);
    Card jokerCard("joker", "rare card increasing everything by 30",1,0,30,30,30);
    Card goldJokerCard("goldJoker", "very rare card increasing everything by 50",1,0,50,50,50);
    Card gamblerCard("gambler", "rare card power +20 and speed +20 but health to -40",1,40,0,20,20);
    Card mysteryCard("mystery", "card with hidden meaning",0,30,0,30,30);
    cards.push_back(mysteryCard);
    cards.push_back(gamblerCard);
    cards.push_back(goldJokerCard);
    cards.push_back(jokerCard);
    cards.push_back(goldSpeedCard);
    cards.push_back(speedCard);
    cards.push_back(hitCard);
    cards.push_back(goldHitCard);
    cards.push_back(healCard);
    cards.push_back(goldHealCard);
    cards.push_back(goldPowerCard);
    cards.push_back(powerCard);
    return cards;
}

vector<Player*> initializeEnemies(){//Player(health, power, name, speed) 
    return {new Healer{10, 10 , "healer",20}, new Warrior{10,10, "warrior",30}, new Wizard{10,10, "magician",10}};
}

int pickPlayer(vector<Player*>&enemies, Player *hero){
    double total = hero->getSpeed();
    for (auto& e : enemies)
        total += e->getSpeed();

    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, total);
    double r = dist(rng);

    if (r < hero->getSpeed())
        return -1;

    r -= hero->getSpeed();
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (r < enemies[i]->getSpeed())
            return i;
        r -= enemies[i]->getSpeed();
    }
    return -1;
}

bool checkIfEnemiesDead(vector<Player* >&enemies){
    bool allDead = true;
    for(Player* p: enemies){
        if(p->getHealth()<=0){
            p->setPower(0);
            p->setSpeed(0);
        }else{
            allDead = false;
        }
    }return allDead;
}

bool checkIfHeroDead(Player *hero){
    if(hero->getHealth()<=0){
        hero->setHealth(0);
        hero->setPower(0);
        hero->setSpeed(0);
        return true;
    }else{
        return false;
    }
}

void initializePlayerCards(vector<Card> &cards, Player *hero) {
    vector<Card> picked;
    static std::mt19937 rng(std::random_device{}());

    int numToPick = 3;
    while (picked.size() < numToPick && !cards.empty()) {
        double total = 0;
        for (auto& c : cards)
            total += c.getProbability();

        std::uniform_real_distribution<double> dist(0.0, total);
        double r = dist(rng);

        for (auto it = cards.begin(); it != cards.end(); ++it) {
            if (r < it->getProbability()) {
                picked.push_back(*it);   
                cards.erase(it);      
                break;
            }
            r -= it->getProbability();
        }
    }
    hero->setCards(picked);
    updatePickedCards(hero);
}

void waitUntilNextTurn() {
    while (true) {
        std::ifstream file("statistics.txt", std::ios::ate);
        if (file && file.tellg() == 0) {
            return; 
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void waitUntilNextTurn2() {
    while (true) {
        std::ifstream file("cards.txt", std::ios::ate);
        if (file && file.tellg() == 0) {
            return; 
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void writeWhoseTurn(int picked) {
    ofstream file("whosturn.txt", std::ios::trunc);
    if(!file.is_open()){
        cerr << "ERROR IN OPENING WHOSTURN FILE FOR CLEARING!";
        return;
    }

        if(picked==-1)file<<"hero"; 
        else if(picked==0)file<<"healer"; 
        else if(picked==1)file<<"warrior"; 
        if(picked==2)file<<"wizard"; 
}

void writeGameOver(string heroWon){
    std::ofstream file("gameover.txt", std::ios::trunc);
    file<< heroWon;
}

void playTurn(vector<Player*>&enemies, Player *hero, vector<Card> cards){
    updatePlayersInfo(enemies,hero);
    initializePlayerCards(cards,hero);
    waitUntilNextTurn();
    clearFiles();

    int picked = pickPlayer(enemies, hero);
    writeWhoseTurn(picked);
    if(picked==-1){
        waitUntilNextTurn2();
        hero->makeTurn(enemies,hero);
    }
    else{
        enemies[picked]->makeTurn(enemies,hero);
    }
}