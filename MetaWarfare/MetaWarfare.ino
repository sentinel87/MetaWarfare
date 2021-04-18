#include <Gamebuino-Meta.h>

struct GameTileStruct
{
    unsigned int terrainTexture: 7;
    unsigned int player: 3;
    unsigned int unitId: 5;
    unsigned int unitHp: 4;
    unsigned int active: 1;
    unsigned int moveGrid: 1;
    unsigned int reserve: 11;
};

struct Unit
{
  unsigned int unitId: 5;
  unsigned int movement: 3;
  unsigned int crossMove: 1;
  unsigned int canCrossMountains: 1;
  unsigned int reserve: 24;
};

const Unit NONE = {0,0,0,0};
const Unit HALF_TRUCK = {1,4,0,0};
const Unit MEDIUM_TANK = {2,3,0,0};
const Unit HEAVY_TANK = {3,3,0,0};
const Unit TANK_DESTROYER = {4,3,0,0};
const Unit MOBILE_ARTILLERY = {5,4,1,0};
const Unit MOBILE_SSM = {6,3,1,0};
const Unit INFANTRY = {7,2,0,1};
const Unit MECH_INFANTRY = {8,1,0,1};


GameTileStruct Board1[6][8]{
    {{0,0,0,0,0,0},{13,0,0,0,0,0},{1,1,7,10,1,0},{4,2,8,10,1,0},{10,0,0,0,0,0},{10,0,0,0,0,0},{2,0,0,0,0,0},{2,0,0,0,0,0}},
    {{16,0,0,0,0,0},{18,0,0,0,0,0},{1,2,3,10,1,0},{4,0,0,0,0,0},{1,0,0,0,0,0},{10,0,0,0,0,0},{1,0,0,0,0,0},{2,0,0,0,0,0}},
    {{1,1,4,10,1,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{4,0,0,0,0,0},{1,2,1,10,1,0},{7,0,0,0,0,0},{3,0,0,0,0,0},{3,0,0,0,0,0}},
    {{3,0,0,0,0,0},{3,0,0,0,0,0},{3,2,2,10,1,0},{5,0,0,0,0,0},{3,0,0,0,0,0},{8,0,0,0,0,0},{1,1,6,10,1,0},{2,0,0,0,0,0}},
    {{1,1,1,10,1,0},{1,2,5,10,1,0},{1,0,0,0,0,0},{4,0,0,0,0,0},{10,0,0,0,0,0},{10,0,0,0,0,0},{2,0,0,0,0,0},{1,0,0,0,0,0}},
    {{1,0,0,0,0,0},{12,0,0,0,0,0},{1,0,0,0,0,0},{4,0,0,0,0,0},{11,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0}},
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
