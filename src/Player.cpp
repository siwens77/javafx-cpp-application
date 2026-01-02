#include "Player.hpp"
#include <fstream>
#include <thread>
using namespace std;

Player::Player(int h, int p, const std::string &n, int s) : health(h), power(p), name(n), speed(s) {}
Player::~Player() {}

int Player::getSpeed()const { return speed; }
int Player::getHealth()const { return health; }
int Player::getPower()const{ return power; }
string Player::getName()const{ return name; }
vector<Card>& Player::getCards(){ return cards; }
void Player::setCards(vector<Card> c) { cards = c; }

void Hero::makeTurn(vector<Player*>&enemies,Player *hero){
    
    string idPickedCard;
    string idPickedCat;
    while(true){
        ifstream MyFile("clickedCard.txt");
        ifstream MyFile2("clickedCat.txt");
        getline(MyFile, idPickedCard); 
        getline(MyFile2, idPickedCat); 
        if ((idPickedCard == "0" ||idPickedCard == "1" ||idPickedCard == "2") 
        && (idPickedCat == "0" ||idPickedCat == "1" ||idPickedCat == "2" || idPickedCat=="-1")){
            MyFile.close();
            MyFile2.close();
            break;
    }MyFile.close();
    MyFile2.close();
    this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    Card &pickedCard = hero->getCards()[stoi(idPickedCard)];
    int idPickedEnemy = stoi(idPickedCat);
    Player* pickedEnemy = (idPickedEnemy == -1) ? hero : enemies[idPickedEnemy];

    pickedCard(*hero,*pickedEnemy);
}

void Healer::makeTurn(std::vector<Player*>& enemies, Player *hero){
    auto healerPower = this->getPower() * 0.01 * 30;

    for(Player* p :enemies){
        if(p->getHealth() > 0){
            p->setHealth(min(healerPower + p->getHealth(), 100.0));
        }
    }
}

void Warrior::makeTurn(vector<Player*>&enemies, Player *hero){
    hero->setHealth(max(hero->getHealth()-this->getPower()*0.01*50, 0.0));
}

void Wizard::makeTurn(vector<Player*>&enemies, Player *hero){
    for(Player* p :enemies){
        p->setPower(this->getPower()*0.01*30+p->getPower());
    }
}