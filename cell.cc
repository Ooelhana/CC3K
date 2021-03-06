#include <iostream>
#include "cell.h"
#include "Enemy.h"
#include "gold.h"
#include "potion.h"
#include <memory>
Cell::Cell(): x(-1), y(-1), symbol(' '), isPlayerValid(false), isEnemyValid(false), dragonHoard(false), obj(nullptr) {}

Cell::Cell(int x, int y, char sym, GameObject& player): x(x), y(y), symbol(sym), origSym(sym), isPlayerValid(false), isEnemyValid(false), dragonHoard(false), obj(nullptr) {
   if(sym == '.') {
	     isEnemyValid = true;
	     isPlayerValid = true;
   }
   else if(sym == '#' || sym == '+' || sym == 'G') {
	     isPlayerValid = true;
	     isEnemyValid = false;
   }
   else if(sym == 'H') {
	      symbol = 'H';
        origSym = '.';
        GameObject* human = new Human(x,y);
        obj = human;
   }
   else if(sym == 'W') {
        symbol = 'W';
        origSym = '.';
        GameObject* dwarf = new Dwarf(x,y);
        obj = dwarf;
   }
   else if(sym == 'E') {
        symbol = 'E';
        origSym = '.';
       	GameObject* elf = new Elf(x,y);
        obj = elf;
   }
   else if(sym == 'O') {
        symbol = 'O';
        origSym = '.';
        GameObject* orc = new Orc(x,y);
        obj = orc;
  }
   else if(sym == 'M') {
        symbol = 'M';
        origSym = '.';
        GameObject* merchant = new Merchant(x,y);
        obj = merchant;
   }
  /* else if(sym == 'D') {
        symbol = 'D';
        origSym = '.';
        GameObject* dragon = new Dragon(x,y);
        obj = dragon;
   }*/
   else if(sym == 'L') {
        symbol = 'L';
        origSym = '.';
        GameObject* halfling = new Halfling(x,y);
        obj = halfling;
   }

   else if(sym == '0') {
	 symbol = 'P';
	 origSym = '.';
         GameObject* restoreHp = new RestoreHp(x,y);
         obj = restoreHp;
   }
   else if(sym == '1') {
        symbol = 'P';
        origSym = '.';
        GameObject* boostAtk = new BoostAtk(x,y);
        obj = boostAtk;
   }
   else if(sym == '2') {
        symbol = 'P';
        origSym = '.';
        GameObject* boostDef = new BoostDef(x,y);
        obj = boostDef;
   }
   else if(sym == '3') {
        symbol = 'P';
        origSym = '.';
        GameObject* poisonHp = new PoisonHp(x,y);
        obj = poisonHp;
   }
   else if(sym == '4') {
        symbol = 'P';
        origSym = '.';
	GameObject* woundAtk = new WoundAtk(x,y);
	obj = woundAtk;
   }
   else if(sym == '5') {
        symbol = 'P';
        origSym = '.';
	GameObject* woundDef = new WoundDef(x,y);
	obj = woundDef;
   }
   else if(sym == '6') {
        symbol = 'G';
        origSym = '.';
	GameObject* regGold = new Gold(x,y,2);
	obj = regGold;
   }
   else if(sym == '7') {
        symbol = 'G';
        origSym = '.';
	GameObject* smGold = new Gold(x,y,1);
	obj = smGold;
   }
   else if(sym == '8') {
        symbol = 'G';
        origSym = '.';
	GameObject* merGold = new Gold(x,y,4);
	obj = merGold;
   }
   else if(sym == '9') {
        symbol = 'G';
        origSym = '.';
	GameObject* dragGold = new Gold(x,y,6);
	obj = dragGold;
   }
   else if(sym == '@') {
	    origSym = '.';
	    obj = &player;
	    player.setx(x);
	    player.sety(y);
   }
   else if(sym == '\\') {
	symbol = '\\';
	origSym = '\\';
   }
	else {}
}

int Cell::getx() { return x; }
int Cell:: gety() { return y; }

char Cell::getOrigSym() { return origSym; }

char Cell::getSymbol() {
   return symbol;
}

bool Cell::getDragonHoard(){
   return dragonHoard;
}

void Cell::setDragonHoard(bool status){
   dragonHoard = status;
}

GameObject* Cell::getObject() {
   return obj;
}

void Cell::add(GameObject* object) {
   obj = object;
   symbol = obj->getSymbol();
   if(symbol == 'G') isPlayerValid = true;
   else isPlayerValid = false;
   isEnemyValid = false;
}

void Cell::remove() {
   if(dragonHoard == true){
      std::cout << "calling dragonhoard" << std::endl;
      //GameObject *p = new Gold(getx(), gety(), 6);
      //obj=p;
      //symbol = obj->getSymbol();
      //isEnemyValid = false;
   }
   else {
       if(symbol == 'P' || symbol == 'G') {
           delete obj;
       }
       else if(obj && obj->getHP() >= 0) obj = nullptr;
      symbol = getOrigSym();
      isEnemyValid = true;

      if(symbol == '+' || symbol == '#') {
	 isEnemyValid = false;
      }
   }
   isPlayerValid = true;
}

void Cell::setSymbol(char sym) {
  symbol = sym;
}

bool Cell::getPlayerValid() {
   return isPlayerValid;
}

bool Cell::getEnemyValid() {
   return isEnemyValid;
}

void Cell::setPlayerValid(bool value) {
	isPlayerValid = value;
}

void Cell::setEnemyValid(bool value) {
	isEnemyValid = value;
}
