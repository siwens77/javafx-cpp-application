#include <iostream>
#include <cassert>
#include <vector>
#include "utils.hpp"
#include "Player.hpp"
#include "Card.hpp"

using namespace std;

void testMaxMinValue(){
    assert(clampValue(125.00, 0.00,100.00)==100.00);
    assert(clampValue(25.00, 0.00,100.00)==25.00);
    assert(clampValue(-10.00, 0.00,100.00)==0.00);
}
void testHealCard(){
    Hero hero(50, 100, "TestHero", 10);
    Card healCard("TestHeal", "only made for the sake of tests", 1.0, 0, 30, 0, 0);
    healCard(hero, hero);
    assert(hero.getHealth() == 80);
    assert(healCard.getDescription()==("only made for the sake of tests"));
    assert(healCard.getName() == "TestHeal");
}
void testEnemies(){
    Player *healer = new Healer{10, 30 , "healer",20};
    Player *warrior = new Warrior{10,10, "warrior",30};
    Player *wizard = new Wizard{50,60, "magician",100};

    assert(healer->getHealth()==10);
    healer->setHealth(0);
    assert(healer->getHealth()==0);
    
    assert(warrior->getName()=="warrior");

    assert(wizard->getPower()==60);
    wizard->setPower(4000);
    assert(wizard->getPower()==4000);

    delete healer;
    delete warrior;
    delete wizard;
}
void testInitializingCards(){
    Hero hero(50,100, "testHero",10);
    vector<Card> cards = initializeCards();
    initializePlayerCards(cards,&hero);
    assert(!hero.getCards().empty());
    assert(hero.getCards().size() == 3);
}
void testGameOver(){
    Hero hero(10, 10, "hero", 10);
    assert(checkIfHeroDead(&hero) == false);

    hero.setHealth(0);
    assert(checkIfHeroDead(&hero) == true);

    Player* e1 = new Warrior(10, 10, "w", 10);
    Player* e2 = new Healer(10, 10, "h", 10);
    vector<Player*> enemies = {e1, e2};
    assert(checkIfEnemiesDead(enemies) == false);

    e1->setHealth(0);
    assert(checkIfEnemiesDead(enemies) == false);
    e2->setHealth(0);
    assert(checkIfEnemiesDead(enemies) == true);

    delete e1;
    delete e2;
}
void testPolymorphism() {
    Hero* hero = new Hero(100, 100, "hero", 10);
    Player* enemy = new Warrior(100, 100, "warrior", 10);
    
    vector<Player*> enemies;
    enemies.push_back(enemy);
    enemy->makeTurn(enemies, hero);
    assert(hero->getHealth() == 50);

    delete hero;
    delete enemy;
}

int main(){
    cout<<"testing clampValue"<<endl;
    testMaxMinValue();
    cout<<"passed"<<endl;
    
    cout<<""<<endl;
    cout<<"testing healCard"<<endl;
    testHealCard();
    cout<<"passed"<<endl;

    cout<<""<<endl;
    cout<<"testing creating enemies and affecting them"<<endl;
    testEnemies();
    cout<<"passed"<<endl;

    cout<<""<<endl;
    cout<<"testing creating hero and giving him exactly three cards"<<endl;
    testEnemies();
    cout<<"passed"<<endl;

    cout<<""<<endl;
    cout<<"testing ending game in proper moment"<<endl;
    testGameOver();
    cout<<"passed"<<endl;

    cout<<""<<endl;
    cout<<"testing polymorphism and hitting hero"<<endl;
    testPolymorphism();
    cout<<"passed"<<endl;

    cout << "=== ALL TESTS PASSED SUCCESSFULLY! ===" << endl;
    return 0;
}