#ifndef _CELL_H_
#define _CELL_H_
//INCOMPLETE
//Error: Enemies can walk on gold (Make validPlayer, validEnemy?)

#include "GameObject.h"

class GameObject;
class Cell {
    int x,y;
    char symbol;
    //-1 - No item 0 - RH, 1 - BA, 2 - BD, 3 - PH, 4 - WA, 5 - WD
    //6 normal gold pile, 7 - small hoard, 8 - merchant hoard
    //9 - dragon hoard. 10 - Human 11 - Dwarf 12 - Halfling 13 - Elf
    //14 - Orc 15 - Merchant 16 - Dragon
    bool isPlayerValid;
    bool isEnemyValid;
    GameObject* obj;
public:
    Cell();
    Cell(int x, int y, char sym);
    char getSymbol();
    GameObject *getObject();
    void add(GameObject* object);
    void remove();
    bool getPlayerValid();
    bool getEnemyValid();
    bool isValid();
};

#endif