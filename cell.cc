//INCOMPLETE

#include "cell.h"

Cell::Cell(): x(-1), y(-1), symbol(' '), isPlayerValid(false), isEnemyValid(false), obj(nullptr) {
    
}
Cell::Cell(int x, int y, char sym): x(x), y(y), symbol(sym), origSym(sym) obj(nullptr) {
    
    if(sym == '.') {
        isEnemyValid = true;
        isPlayerValid = true;
    }
    else if(sym == '#' || sym == '+') {
        isPlayerValid = true;
        isEnemyValid = false;
    }
    else {
        isPlayerValid = false;
        isEnemyValid = false;
    }
}

char Cell::getSymbol() {
   	return symbol;
}

GameObject* Cell::getObject() {
   	return obj;
}

void Cell::add(GameObject* object) {
    obj = object;
    symbol = obj->getSymbol();
    isEnemyValid = false;
    if(symbol == 'G') {
	isPlayerValid = true;
    }
    else {
	isPlayerValid = false;
    }
}
// When the player is on the pathway or the doorway and when they move, it is replaced by # or + not . (remember to modify this)
void Cell::remove() {
    obj = nullptr;
    symbol = origSym;
    isPlayerValid = true;
    isEnemyValid = true;
}

bool Cell::getPlayerValid() {
    return isPlayerValid;
}

bool Cell::getEnemyValid() {
    return isEnemyValid;
}
