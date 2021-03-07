#include <Gamebuino-Meta.h>

int field[12][16] ={
  {1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
  {1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
  {3,3,3,3,1,1,1,3,3,3,3,3,3,3,3,3},
  {3,3,3,3,1,1,1,3,3,3,3,3,3,3,3,3},
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
  {7,7,7,7,7,7,7,7,1,2,3,4,5,6,7,8},
  {8,8,8,8,8,8,8,8,1,2,3,4,5,6,7,8},
  {9,9,9,9,9,9,9,9,1,2,3,4,5,6,7,8},
  {10,10,10,10,10,10,10,10,1,2,3,4,5,6,7,8},
  {11,11,11,11,11,11,11,11,1,2,3,4,5,6,7,8},
  {12,12,12,12,12,12,12,12,1,2,3,4,5,6,7,8}
};
int posX=0;
int posY=0;
int sRowIdx=0;
int sColIdx=0;

int selected=0;

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
      if(sRowIdx<6)
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
      if(sColIdx<8)
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
    selected = field[row][column];
  }
}
