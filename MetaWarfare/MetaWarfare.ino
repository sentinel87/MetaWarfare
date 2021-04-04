#include <Gamebuino-Meta.h>

struct GameTileStruct
{
    unsigned int terrainColor: 4;
    unsigned int terrainTexture: 7;
    unsigned int player: 3;
    unsigned int unitId: 5;
    unsigned int unitHp: 4;
    unsigned int active: 1;
    unsigned int reserve: 8;
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

GameTileStruct Board1[6][8]{
    {{1,0,0,0,0,0},{1,13,0,0,0,0},{0,1,1,7,10,1},{0,4,2,8,10,1},{0,10,0,0,0,0},{0,10,0,0,0,0},{0,2,0,0,0,0},{0,2,0,0,0,0}},
    {{1,16,0,0,0,0},{1,18,0,0,0,0},{0,1,2,3,10,1},{0,4,0,0,0,0},{0,1,0,0,0,0},{0,10,0,0,0,0},{0,1,0,0,0,0},{0,2,0,0,0,0}},
    {{0,1,2,4,10,1},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,4,0,0,0,0},{0,1,2,1,10,1},{0,7,0,0,0,0},{0,3,0,0,0,0},{0,3,0,0,0,0}},
    {{0,3,0,0,0,0},{0,3,0,0,0,0},{0,3,2,2,10,0},{0,5,0,0,0,0},{0,3,0,0,0,0},{0,8,0,0,0,0},{0,1,2,6,10,1},{0,2,0,0,0,0}},
    {{0,1,2,1,10,1},{0,1,2,5,10,0},{0,1,0,0,0,0},{0,4,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{0,1,0,0,0,0}},
    {{0,1,0,0,0,0},{0,12,0,0,0,0},{0,1,0,0,0,0},{0,4,0,0,0,0},{0,11,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0}},
};

int posX=0;
int posY=0;
int sRowIdx=0;
int sColIdx=0;

int expandedWidth=0;
int expandedHeight=0;
GameTileStruct selected=Board1[0][0];
Unit selectedUnit=NONE;

bool unitMode=false;

void setup() {
  gb.begin();
  //gb.setFrameRate(20);
}    


void loop() {
  while(!gb.update());
  gb.display.clear();

  drawMap();
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(posX!=0)
      posX-=10;
    else
    {
      if(sRowIdx>0)
      {
        sRowIdx--;
      }
    }
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(posX!=50)
    {
      posX+=10;
    }
    else
    {
      if(sRowIdx<expandedHeight)
      {
        sRowIdx++;
      }
    }
  }
  else if(gb.buttons.pressed(BUTTON_LEFT))
  {
    if(posY!=0)
    {
      posY-=10;
    }
    else
    {
      if(sColIdx>0)
      {
        sColIdx--;
      }
    }
  }
  else if(gb.buttons.pressed(BUTTON_RIGHT))
  {
    if(posY!=70)
    {
      posY+=10;
    }
    else
    {
      if(sColIdx<expandedWidth)
      {
        sColIdx++;
      }
    }
  }
  else if(gb.buttons.pressed(BUTTON_A))
  {
    int row = sRowIdx;
    if(posX>0)
      row+=(posX/10);
    int column = sColIdx;
    if(posY>0)
      column+=(posY/10);
    selected=Board1[row][column];
    if(selected.unitId!=0 && selected.active==1)
    {
      selectedUnit=GetUnit(selected.unitId);
      unitMode=true;
    }
  }
  else if(gb.buttons.pressed(BUTTON_B))
  {
    if(unitMode==true)
    {
      selectedUnit=NONE;
      unitMode=false;
    }
  }
}

Unit GetUnit(unsigned int id)
{
  Unit selected=NONE;
  switch(id)
  {
    case 0:
      selected=NONE; break;
    case 1:
      selected=HALF_TRUCK; break;
    case 2:
      selected=MEDIUM_TANK; break;
    case 3:
      selected=HEAVY_TANK; break;
    case 4:
      selected=TANK_DESTROYER; break;
    case 5:
      selected=MOBILE_ARTILLERY; break;
    case 6:
      selected=MOBILE_SSM; break;
  }
  return selected;
}
