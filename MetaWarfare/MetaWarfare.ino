#include <Gamebuino-Meta.h>

struct GameTileStruct
{
    unsigned int terrainTexture: 7;
    unsigned int player: 3;
    unsigned int unitId: 5;
    unsigned int unitHp: 4;
    unsigned int active: 1;
    unsigned int reserve: 12;
};

struct Unit
{
  String unitName;
  unsigned int unitId;
  unsigned int moveRange;
};

const Unit NONE = {"None",0,0};
const Unit HALF_TRUCK = {"Half Truck",1,5};
const Unit MEDIUM_TANK = {"Medium Tank",2,4};
const Unit HEAVY_TANK = {"Heavy Tank",3,3};
const Unit TANK_DESTROYER = {"Tank Destroyer",4,3};
const Unit MOBILE_ARTILLERY = {"Mobile Artillery",5,4};
const Unit MOBILE_SSM = {"Mobile SSM",6,3};
const Unit INFANTRY = {"Infantry",7,2};
const Unit MECH_INFANTRY = {"Anti Tank Infantry",8,2};


GameTileStruct Board1[6][8]{
    {{0,0,0,0,0},{13,0,0,0,0},{1,1,7,10,1},{4,2,8,10,1},{10,0,0,0,0},{10,0,0,0,0},{2,0,0,0,0},{2,0,0,0,0}},
    {{16,0,0,0,0},{18,0,0,0,0},{1,2,3,10,1},{4,0,0,0,0},{1,0,0,0,0},{10,0,0,0,0},{1,0,0,0,0},{2,0,0,0,0}},
    {{1,1,4,10,1},{1,0,0,0,0},{1,0,0,0,0},{4,0,0,0,0},{1,2,1,10,1},{7,0,0,0,0},{3,0,0,0,0},{3,0,0,0,0}},
    {{3,0,0,0,0},{3,0,0,0,0},{3,2,2,10,1},{5,0,0,0,0},{3,0,0,0,0},{8,0,0,0,0},{1,1,6,10,1},{2,0,0,0,0}},
    {{1,1,1,10,1},{1,2,5,10,1},{1,0,0,0,0},{4,0,0,0,0},{10,0,0,0,0},{10,0,0,0,0},{2,0,0,0,0},{1,0,0,0,0}},
    {{1,0,0,0,0},{12,0,0,0,0},{1,0,0,0,0},{4,0,0,0,0},{11,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0}},
};

GameTileStruct CurrentBoard[6][8];

bool menuMode=true;

void setup() {
  gb.begin();
}    


void loop() {
  while(!gb.update());
  gb.display.clear();

  if(menuMode==true)
  {
    memcpy(CurrentBoard, Board1, sizeof(CurrentBoard));
    menuMode=false;
  }
  Battle();
}
