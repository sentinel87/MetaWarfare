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

GameTileStruct Board1[6][8]{
    {{1,0,0,0,0,0},{1,13,0,0,0,0},{0,1,0,0,0,0},{0,4,0,0,0,0},{0,10,0,0,0,0},{0,10,0,0,0,0},{0,2,0,0,0,0},{0,2,0,0,0,0}},
    {{1,16,0,0,0,0},{1,18,0,0,0,0},{0,1,2,3,10,0},{0,4,0,0,0,0},{0,1,0,0,0,0},{0,10,0,0,0,0},{0,1,0,0,0,0},{0,2,0,0,0,0}},
    {{0,1,1,4,10,1},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,4,0,0,0,0},{0,1,2,1,10,1},{0,7,0,0,0,0},{0,3,0,0,0,0},{0,3,0,0,0,0}},
    {{0,3,0,0,0,0},{0,3,0,0,0,0},{0,3,2,2,10,1},{0,5,0,0,0,0},{0,3,0,0,0,0},{0,8,0,0,0,0},{0,1,0,0,0,0},{0,2,0,0,0,0}},
    {{0,1,1,1,10,1},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,4,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{0,1,0,0,0,0}},
    {{0,1,0,0,0,0},{0,12,0,0,0,0},{0,1,0,0,0,0},{0,4,0,0,0,0},{0,11,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0}},
};

int posX=0;
int posY=0;
int sRowIdx=0;
int sColIdx=0;

int expandedWidth=0;
int expandedHeight=0;
GameTileStruct selected=Board1[0][0];

void setup() {
  gb.begin();
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
  }
}
