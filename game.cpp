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
    victim.setHealth(victim.getHealth()-powerHit*abuser.getPower()*0.01);
}
void Card::heal(Player &abuser, Player &victim){
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
    ofstream outFile("cards.txt");
    for(int i = 0 ; i<cards.size(); i++){
        outFile<< "resources/images/"<<cards[i].name<< ".png"<<endl;
    }
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
    //Card(name, description, probability, hit, heal, power,speed)
    Card hitCard("hit", "common card hitting for 5p", 1, 5, 0, 0,0);
    Card goldHitCard("goldHit", "rare card hitting for 20p", 1, 20, 0, 0,0);
    Card healCard("heal" ,"common card healing 10p", 1,0,20,0,0);
    Card goldHealCard("goldHeal", "rare card healing 50p", 1,0,50,0,0); 
    Card powerCard("power", "common card increasing power by 25p", 0,0,0,25,0);
    Card goldPowerCard("goldPower", "rare card increasing power by 50p", 0,0,0,50,0);
    //TODO: card increasing speed
    //TODO: joker increasing everything
    //TODO: card setting every attibrute to 1 
    //TODO: card giving power but setting health to 1
    //TODO: card exchanging attributes BANGER   
    //TODO: card making enemiee do sth against will
    //TODO: card making wizard attack and warrior throw spells
    cards.push_back(hitCard);
    cards.push_back(goldHitCard);
    cards.push_back(healCard);
    cards.push_back(goldHealCard);
    cards.push_back(goldPowerCard);
    cards.push_back(powerCard);
    return cards;
}

vector<Player> initializeEnemies(){//Player(health, power, name, speed) TODO:make different max health?
    return {{90, 10 , "healer",20}, {100,30, "warrior",30}, {100,40, "magician",20}};//TODO: better balance in game
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

void heroMakeTurn(Player *hero, vector<Player>&enemies){
    
    string idPickedCard;
    while(true){
        ifstream MyFile("clickedCard.txt");
        getline(MyFile, idPickedCard); 
        if (idPickedCard == "0" ||idPickedCard == "1" ||idPickedCard == "2") {
            MyFile.close();
            break;
    }MyFile.close();
    this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    Card &pickedCard = hero->getCards()[stoi(idPickedCard)];



    string idPickedCat;
    while(true){
        ifstream MyFile2("clickedCat.txt");
        getline(MyFile2, idPickedCat); 
        if (idPickedCat == "0" ||idPickedCat == "1" ||idPickedCat == "2") {
            MyFile2.close();
            break;
    }MyFile2.close();
    this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    int idPickedEnemy = stoi(idPickedCat);
    Player& pickedEnemy = (idPickedEnemy == -1) ? *hero : enemies[idPickedEnemy];

    pickedCard.hit(*hero, pickedEnemy);
    pickedCard.heal(*hero, pickedEnemy);
    pickedCard.increasePower(*hero, pickedEnemy);
    pickedCard.increaseSpeed(*hero, pickedEnemy);

}

void healerMakeTurn(vector<Player>&enemies){
    for(Player& p :enemies){
        p.setHealth(min(enemies[0].getPower()*0.01*30+p.getHealth(), 100.00));
    }
}

void warriorMakeTurn(vector<Player>&enemies, Player &hero){
    hero.setHealth(max(hero.getHealth()-enemies[1].getPower()*0.01*5, 0.0));
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

void playTurn(vector<Player>&enemies, Player &hero){
    updatePlayersInfo(enemies,hero);
    waitUntilNextTurn();
    clearFiles();

    int picked = pickPlayer(enemies, hero);
    writeWhoseTurn(picked);
    switch(picked){

        case -1:
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
        return;
    }
}

int main(){//make different difficulty levels? create bosses?
    clearFiles();
    vector<Card>cards = initializeCards();
    vector<Player>enemies = initializeEnemies();
    Player hero(100,100, "hero", 30);

    updatePlayersInfo(enemies, hero);
    initializePlayerCards(cards, hero);
    
    writeWhoseTurn(-1);
    heroMakeTurn(&hero, enemies);


    for(int i =0; i<5; i++){
        playTurn(enemies, hero);
    }//TODO: check if everyone live and make speed 0 if dead
    writeWhoseTurn(69);
        

    return 0;
}
