#include <iostream>
#include <algorithm>
#include <random>
#include <numeric>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;

class Player;
class Card;

class Card{
    public:
    string name;
    string description;
    double probability;
    int powerHit;
    int powerHeal;
    int powerPower;
    int PowerSpeed;
    
    Card(string n, string desc, double prob, int powHit, int powHeal, int powPow, int powSpeed) 
    : name(n), description(desc), probability(prob), powerHit(powHit) , powerHeal(powHeal) , powerPower(powPow), PowerSpeed(powSpeed){} 
    void hit(Player& abuser, Player& victim);
    void heal(Player& abuser, Player& victim);
    void increasePower(Player& increaser, Player& target);
    void increaseSpeed(Player& increaser, Player& target);
};

class Player{
    private:
    int health;
    int power;
    int speed;
    string name;
    vector<Card> cards;
    public:
    Player(int h, int p, string n, int s) : health(h), power(p), name(n), speed(s) {};

    int getSpeed(){return speed;}
    int getHealth(){return health;}
    int getPower(){return power;}
    string getName(){return name;}
    vector<Card>& getCards(){return cards;}

    void setSpeed(int s){speed = s;}
    void setHealth(int h){health = h;}
    void setPower(int p){power = p;}
    void setCards(vector<Card> c){cards = c;}
};


void Card::hit(Player &abuser, Player &victim){
    victim.setHealth(max(victim.getHealth()-powerHit*abuser.getPower()*0.01,0.00));
}
void Card::heal(Player &abuser, Player &victim){
    if(victim.getHealth()<=0)return;
    victim.setHealth(min(victim.getHealth()+powerHeal*abuser.getPower()*0.01, 100.00));
}
void Card::increasePower(Player &increaser, Player &target){
    target.setPower(target.getPower()+powerPower*increaser.getPower()*0.01);
}
void Card::increaseSpeed(Player &increaser, Player &target){
    target.setSpeed(target.getSpeed()+PowerSpeed*increaser.getPower()*0.01);
}

void updatePlayersInfo(vector<Player>enemies, Player hero){
    ofstream outFile2("statistics.tmp");
    outFile2<< hero.getHealth()<< " "<<hero.getPower()<< " "<<hero.getSpeed()<<endl;
    for(int i = 0;i<3; i++){
        outFile2<< enemies[i].getHealth() << " "<< enemies[i].getPower()<<" "<<enemies[i].getSpeed()<<endl;
    }
    rename("statistics.tmp", "statistics.txt");

    return;
}

void updatePickedCards(Player hero){
    vector<Card>cards = hero.getCards();
    ofstream outFile("cards.tmp");
    for(int i = 0 ; i<cards.size(); i++){
        outFile<< "resources/images/"<<cards[i].name<< ".png"<<endl;
        outFile<< cards[i].description<<endl;
    }
    rename("cards.tmp",  "cards.txt");
}

void clearFiles() {
    const char* files[] = {"clickedCard.txt", "statistics.txt", "clickedCat.txt","whosturn.txt"};
    for (const char* file : files) {
        std::ofstream out(file, std::ios::trunc);
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

vector<Player> initializeEnemies(){//Player(health, power, name, speed) TODO:make different max health?
    return {{10, 10 , "healer",20}, {10,10, "warrior",30}, {10,10, "magician",10}};//TODO: better balance in game
}

int pickPlayer(vector<Player>&enemies, Player &hero){
    double total = hero.getSpeed();
    for (auto& e : enemies)
        total += e.getSpeed();

    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, total);
    double r = dist(rng);

    if (r < hero.getSpeed())
        return -1;

    r -= hero.getSpeed();
    int picked = enemies.size();
    for (auto& e : enemies) {
        if (r < e.getSpeed())
            return picked;
        r -= e.getSpeed();
        picked--;
    }
    return 100000;
}

bool checkIfEnemiesDead(vector<Player>&enemies){
    bool allDead = true;
    for(Player& p: enemies){
        if(p.getHealth()<=0){
            p.setPower(0);
            p.setSpeed(0);
        }else{
            allDead = false;
        }
    }return allDead;
}

bool checkIfHeroDead(Player &hero){
    if(hero.getHealth()<=0){
        hero.setHealth(0);
        hero.setPower(0);
        hero.setSpeed(0);
        return true;
    }else{
        return false;
    }
}

void heroMakeTurn(Player *hero, vector<Player>&enemies){
    
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
    Player& pickedEnemy = (idPickedEnemy == -1) ? *hero : enemies[idPickedEnemy];

    pickedCard.hit(*hero, pickedEnemy);
    pickedCard.heal(*hero, pickedEnemy);
    pickedCard.increasePower(*hero, pickedEnemy);
    pickedCard.increaseSpeed(*hero, pickedEnemy);

}

void healerMakeTurn(vector<Player>&enemies){
    for(Player& p :enemies){
        if(p.getHealth()>0){
            p.setHealth(min(enemies[0].getPower()*0.01*30+p.getHealth(), 100.00));
        }
    }
}

void warriorMakeTurn(vector<Player>&enemies, Player &hero){
    hero.setHealth(max(hero.getHealth()-enemies[1].getPower()*0.01*50, 0.0));
}

void wizardMakeTurn(vector<Player>&enemies){
    for(Player& p :enemies){
        p.setPower(enemies[2].getPower()*0.01*30+p.getPower());
    }
}

void initializePlayerCards(vector<Card> cards, Player &hero) {
    vector<Card> picked;
    static std::mt19937 rng(std::random_device{}());

    int numToPick = 3;
    while (picked.size() < numToPick && !cards.empty()) {
        double total = 0;
        for (auto& c : cards)
            total += c.probability;

        std::uniform_real_distribution<double> dist(0.0, total);
        double r = dist(rng);

        for (auto it = cards.begin(); it != cards.end(); ++it) {
            if (r < it->probability) {
                picked.push_back(*it);   
                cards.erase(it);      
                break;
            }
            r -= it->probability;
        }
    }
    hero.setCards(picked);
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
    std::ofstream file("whosturn.txt", std::ios::trunc);

    switch (picked) {
        case -1:
            file << "hero";
            break;
        case 1:
            file << "wizard";
            break;
        case 2:
            file << "warrior";
            break;
        case 3:
            file << "healer";
            break;
        case 69:
            file << "END";
            break;
        default:
            file << "unknown";
            break;
    }
}

void writeGameOver(string heroWon){
    std::ofstream file("gameover.txt", std::ios::trunc);
    file<< heroWon;
}

void playTurn(vector<Player>&enemies, Player &hero, vector<Card> cards){
    updatePlayersInfo(enemies,hero);
    initializePlayerCards(cards,hero);
    waitUntilNextTurn();
    clearFiles();

    int picked = pickPlayer(enemies, hero);
    writeWhoseTurn(picked);
    switch(picked){

        case -1:
        waitUntilNextTurn2();
        heroMakeTurn(&hero, enemies);
        break;

        case 3:
        healerMakeTurn(enemies);
        break;

        case 2:
        warriorMakeTurn(enemies, hero);
        break;

        case 1:
        wizardMakeTurn(enemies);
        break;

        default:
        return;//todo: raise error here
    }
}

int main(){
    clearFiles();
    vector<Card>cards = initializeCards();
    vector<Player>enemies = initializeEnemies();
    Player hero(100,100, "hero", 30);

    updatePlayersInfo(enemies, hero);
    initializePlayerCards(cards, hero);
    
    bool allDead, heroDead =false;
    while(!allDead && !heroDead){
        playTurn(enemies, hero,cards);
        allDead = checkIfEnemiesDead(enemies);
        heroDead = checkIfHeroDead(hero);
        writeGameOver("N");
    }
    if(allDead){
        writeGameOver("W");
    }else{writeGameOver("L");}
    updatePlayersInfo(enemies,hero);
    return 0;
}
//todo: set cool end game screen
//todo: meet prof's expectations
//todo: game balance