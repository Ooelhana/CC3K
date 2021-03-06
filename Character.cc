#include "Character.h"
#include <string>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include "floor.h"
using namespace std;

std::pair<int,int> Character::radius[8] = {std::make_pair(-1,0), std::make_pair(1,0), std::make_pair(0,1), std::make_pair(0,-1),
					std::make_pair(1,-1), std::make_pair(-1,1), std::make_pair(1,1), std::make_pair(-1,-1)};

// Character Constructor, has the cell's location, the symbol, a pointer to the floor, the characteristics, and the amount of gold carried.

Character::Character(int x, int y, char symbol, int health, int attack, int defense, std::string race, int gold):
GameObject(x,y,symbol),
health(health),
attack(attack),
defense(defense),
race(race),
gold(gold)
{}

// Character Destructor:
Character::~Character() {}

int Character::getHP() {
    return health;
}

int Character::getAtk() {
    return attack;
}

int Character::getDef() {
    return defense;
}

int Character::getGold(){
    return gold;
}

std::string Character::getRace() {
    return race;
}

void Character::setHP(int hp){
    health = hp;
}

void Character::setAtk(int at){
    attack = at;
}

void Character::setDef(int def){
    defense = def;
}

void Character::setGold(int g){
    gold = g;
} 

std::string translation(std::string dir){
    if(dir == "no") return "North";
    else if(dir == "so") return "South";
    else if(dir == "ea") return "East";
    else if(dir == "we") return "West";
    else if(dir == "ne") return "NorthEast";
    else if(dir == "nw") return "NorthWest";
    else if(dir == "se") return "SouthEast";
    else if(dir == "sw") return "SouthWest";
    else { return "Invalid Coordinate"; } 
}

// This function, moves/shifts the character in the specific direction.
void Character::shift(std::string dir, Floor *g){
    int old_x = getx();
    int old_y = gety();
    int new_x,new_y;
    if(dir == "no"){
        new_x = getx()-1;
        new_y = gety();
    }
    else if(dir == "so"){
        new_x = getx()+1;
        new_y = gety();
    }
    else if(dir == "ea"){
        new_x = getx();
        new_y = gety()+1;
    }
    else if(dir == "we"){
        new_x = getx();
        new_y = gety()-1;
    }
    else if(dir == "ne"){
        new_x = getx()-1;
        new_y = gety()+1;
    }
    else if(dir == "nw"){
        new_x = getx()-1;
        new_y = gety()-1;
    }
    else if(dir == "se"){
        new_x = getx()+1;
        new_y = gety()+1;
    }
    else if(dir == "sw"){
        new_x = getx()+1;
        new_y = gety()-1;
    }
    else {
        new_x = getx();
        new_y = gety();
    }
    // A floor point to the grid the character is on. First checks, if the new cell where the player is trying to move is valid for player to move or not. If it is valid, and if the new cell has gold object on it, then it creates a GameObject pointer to store the gold. Now if the gold is pickable (i.e. not the dragon gold), then the gold value get's added to the gold carried by the player. The player is shifted to the new cells and removed from the old location.
  //  Floor *g = this->getGrid();
    bool isPlayer = false;
    if(getSymbol() == '@'){
        isPlayer = true;
    }
    
    bool valid = g->isCellValid(new_x, new_y, isPlayer);
    if(isPlayer && g->getSymbol(new_x, new_y) == '\\') setLevel(getLevel() + 1);
    std::ostringstream ss;
    if (valid) {
        if(this->getRace() == "Troll"){ //Every time troll moves, gets 5 points. 
            if(((this->getHP()) + 5) > 120){
                this->setHP(120);
            }
            else{
                this->setHP((this->getHP()) + 5);
            }
        }
        if((g->getSymbol(new_x, new_y)) == 'G'){
            GameObject *gold = g->getObj(new_x, new_y);
            if(gold->getPickable()){
		ss << "PC picks up " << gold->getGold() << " gold. ";
		std::string s = ss.str();
                setGold(gold->getGold()+this->getGold());
                
            }
            delete gold;
        }
        setx(new_x);
        sety(new_y);
        g->objectAdd(new_x, new_y,this);
        g->objectRemove(old_x, old_y);
        if(getSymbol() == '@'){
            callAction(g);
        }
        if(isPlayer){
            ss << "PC moves " << translation(dir);
            std::string s = ss.str();
            setMessage(s);
        } 
    }
}

// The strike function calculates the damage when one character attacks the other, and it manipulates the health points.
void Character::strike(GameObject *c, Floor *g){
    // Troll gains 5 HP every turn; Capped at Max Health
    if(this->getRace() == "Troll"){
        if(((this->getHP()) + 5) > 120){
            this->setHP(120);
        }
        else{
            this->setHP((this->getHP()) + 5);
        }
    }
    // Vampire gains 5 HP for every attack but loses 5HP for every attack on dwarf
    if(this->getRace() == "Vampire"){
        if (c->getSymbol() != 'W')
            this->setHP(this->getHP() + 5);
        else
            this->setHP(this->getHP() - 5);
    }
    // Calculate damage
    double temp = c->getDef();
    double damage = ceil((100/(100+temp))*(this->getAtk()));
    
    // Orcs do 50% more damage to goblins
    if ((this->getSymbol() == 'O') && (c->getRace() == "Goblin"))
        damage *= 1.5;
    // If enemy dies call their death function.
    if((c->getHP() - damage) <= 0){
        c->setHP(0);

        if (c->getSymbol() != '@'){
            c->enemyDeath(*this,g);
            delete c;
	    return;
        }
    }
    else{
        c->setHP(c->getHP() - damage);
    }
    if(this->getSymbol() == '@'){
        //double oppDamage = ceil((100/(100+getDef()))*(c.getAtk()));
        std::ostringstream ss;
        ss << "PC deals " << damage << " to " << c->getRace() <<  ". HP left: " << c->getHP();
        std::string s = ss.str();
        setMessage(s);
    }
}

// BeStruckBY function means Character A is struck by Character B. So, B strikes A, hence it calls the strike function.
void Character::beStruckBy(GameObject *c, Floor *g){
    int hit = 1; // If 1 then hit; if 0 then miss
    std::srand(time(0));
    // Enemies have a 50% chance of striking the player (ie if player is being struck by an enemy, there is a 50% chance of calling strike(player).Players have a 50% chance of striking a halfling, i.e if halfing is being struck by player, there is a 50% chance of calling strike(halfling)
    if((this->getSymbol() == '@') || (this->getSymbol() == 'L')){
        hit = std::rand() % 2;
    }
    if(hit == 1){
        c->strike(this,g);
        // If a Merchant is attacked for the first time; set merchantHostile to true
        if(this->getSymbol() == 'M'){
            c->setMerchantHostile();
        }
        // Elf can strike each race except Drow twice (it still has 50% chance of hitting)
        else if((c->getSymbol()) == 'E'){
            hit = std::rand() % 2;
            if(!(this->getRace() == "Drow") && (hit == 1)){
                if(c) c->strike(this,g);
            }
        }
    }
    c->callAction(g);
}

