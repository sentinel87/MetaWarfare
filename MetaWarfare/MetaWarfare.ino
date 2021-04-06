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

int currentPlayer=1;

int posX=0;
int posY=0;

int sRowIdx=0;
int sColIdx=0;

int expandedWidth=0;
int expandedHeight=0;

int baseTileRow=0;
int baseTileColumn=0;
Unit selectedUnit=NONE;
int selectedPosX=0;
int selectedPosY=0;

bool unitMode=false;

void setup() {
  gb.begin();
}    


void loop() {
  while(!gb.update());
  gb.display.clear();

  drawMap();
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(posY!=0)
      posY-=10;
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
    if(posY!=50)
    {
      posY+=10;
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
    if(posX!=0)
    {
      posX-=10;
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
    if(posX!=70)
    {
      posX+=10;
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
    if(posY>0)
      row+=(posY/10);
    int column = sColIdx;
    if(posX>0)
      column+=(posX/10);

    if(unitMode!=true)
    {
      if(Board1[row][column].unitId!=0 && Board1[row][column].active==1 && Board1[row][column].player==currentPlayer)
      {
        baseTileRow=row;
        baseTileColumn=column;
        selectedUnit=getUnit(Board1[row][column].unitId);
        selectedPosY=posY;
        selectedPosX=posX;
        unitMode=true;
      }
    }
    else
    {
      if(selectedPosX!=posX || selectedPosY!=posY)
      {
        if(Board1[row][column].terrainTexture!=0 && Board1[row][column].terrainTexture!=2 && Board1[row][column].unitId==0)
        {
          //Fill destination tile with unit info
          Board1[row][column].player=Board1[baseTileRow][baseTileColumn].player;
          Board1[row][column].unitId=Board1[baseTileRow][baseTileColumn].unitId;
          Board1[row][column].unitHp=Board1[baseTileRow][baseTileColumn].unitHp;
          Board1[row][column].active=0;
          //Remove unit info from starting tile
          Board1[baseTileRow][baseTileColumn].player=0;
          Board1[baseTileRow][baseTileColumn].unitId=0;
          Board1[baseTileRow][baseTileColumn].unitHp=0;
          Board1[baseTileRow][baseTileColumn].active=0;
          unitMode=false;
        }
      }
    }
    
  }
  else if(gb.buttons.pressed(BUTTON_B))
  {
    if(unitMode==true)
    {
      selectedUnit=NONE;
      unitMode=false;
      selectedPosX=0;
      selectedPosY=0;
    }
  }
  else if(gb.buttons.pressed(BUTTON_MENU))
  {
    endTurn();
  }
}

Unit getUnit(unsigned int id)
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
    case 7:
      selected=INFANTRY; break;
    case 8:
      selected=MECH_INFANTRY; break;
  }
  return selected;
}

void endTurn()
{
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<6;j++)
    {
      if(Board1[j][i].unitId!=0 && Board1[j][i].player==currentPlayer)
      {
        Board1[j][i].active=1;
      }
    }
  }
  if(currentPlayer==1)
  {
    currentPlayer=2;
  }
  else
  {
    currentPlayer=1;
  }
}

