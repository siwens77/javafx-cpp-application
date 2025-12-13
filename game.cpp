#include <iostream>
#include <algorithm>
#include <random>
#include <numeric>
#include <fstream>
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

void displayPlayers(vector<Player>enemies, Player hero){
    cout<<" YOU[-1] "<< " health="<< hero.getHealth()<< " power="<<hero.getPower()<< " speed="<<hero.getSpeed()<<endl;
    for(int i = 0;i<3; i++){
        cout<<enemies[i].getName()<<"["<<i<<"]"<<" health=" << enemies[i].getHealth() << 
        " power="<< enemies[i].getPower()<<" speed= "<<enemies[i].getSpeed()<<endl;
    }return;
}

void displayCards(Player hero){
    vector<Card>cards = hero.getCards();
    cout<<"Your cards: "<<endl;
    for(int i =0;i<cards.size();i++){
        cout <<"["<< i<<"] "<<cards[i].description<<endl;
    }
}

vector<Card> initializeCards() {
    vector<Card> cards;
    //Card(name, description, probability, hit, heal, power,speed)
    Card hitCard("hit", "common card hitting for 5p", 1, 5, 0, 0,0);
    Card goldHitCard("goldHit", "rare card hitting for 20p", 0.25, 20, 0, 0,0);
    Card healCard("heal" ,"common card healing 10p", 1,0,20,0,0);
    Card goldHealCard("goldHeal", "rare card healing 50p", 0.2,0,50,0,0); 
    Card powerCard("power", "common card increasing power by 25p", 1,0,0,25,0);
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
    return {{100, 10 , "healer",20}, {100,30, "warrior",30}, {100,40, "magician",20}};//TODO: better balance in game
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

    displayCards(*hero);
    int idPickedCard = -10;
    cout<<"which card you pick?: ";
    cin>>idPickedCard;
    Card &pickedCard = hero->getCards()[idPickedCard];
    cout<<"your picked card description: "<< pickedCard.description<<endl;

    displayPlayers(enemies, *hero);
    int idPickedEnemy = -1;
    cout<<"which player do you want to affect?: ";
    cin>>idPickedEnemy;
    
    Player& pickedEnemy = (idPickedEnemy == -1) ? *hero : enemies[idPickedEnemy];
    cout<<"you will affect player "<< pickedEnemy.getName()<<endl;

    std::ofstream out("cards.txt");
    out << pickedCard.name <<"\n"; 
    out << pickedEnemy.getName() <<"\n";
    out.flush();

    pickedCard.hit(*hero, pickedEnemy);
    pickedCard.heal(*hero, pickedEnemy);
    pickedCard.increasePower(*hero, pickedEnemy);
    pickedCard.increaseSpeed(*hero, pickedEnemy);
}

void healerMakeTurn(vector<Player>&enemies){
    for(Player& p :enemies){
        p.setHealth(min(enemies[0].getPower()*0.01*30+p.getHealth(), 100.00));
    }
    cout<<"healer incresed health of enemies by: "<<enemies[0].getPower()*0.01*30<<endl;
}

void warriorMakeTurn(vector<Player>&enemies, Player &hero){
    cout<<"hero hit by "<< enemies[1].getPower()*0.01*5<<" by warrior" <<endl;
    hero.setHealth(max(hero.getHealth()-enemies[1].getPower()*0.01*5, 0.0));
    cout<<"current health: "<<hero.getHealth()<<endl;
}

void wizardMakeTurn(vector<Player>&enemies){
    for(Player& p :enemies){
        p.setPower(enemies[2].getPower()*0.01*30+p.getPower());
    }
    cout<<"enemies get boost in power by "<< enemies[2].getPower()*0.01*30<< endl;
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
}


int main(){//make different difficulty levels? create bosses?
    vector<Card>cards = initializeCards();
    vector<Player>enemies = initializeEnemies();
    Player hero(100,100, "hero", 30);


    initializePlayerCards(cards, hero);
    heroMakeTurn(&hero, enemies);

    while(true){//TODO: make this smarter without ifs (not necessary)

        
        int picked = pickPlayer(enemies, hero);
        switch(picked){
            case -1:
            heroMakeTurn(&hero, enemies);
            //TODO: delete used card? or just draw everytime 3 new(easier)?
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
            cout<<"WHATA"<<picked;
            return -1;
        }
        initializePlayerCards(cards, hero);

    }//TODO: check if everyone live and make speed 0 if dead
    //TODO: update() only those who were changed??
        

    return 0;
}
