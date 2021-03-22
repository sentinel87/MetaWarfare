#include <Gamebuino-Meta.h>

int field[12][16] ={
  {         1,  1,       10, 40,       100,100, 20, 20, 10,  1,  1,  1,  1,  1,  1,  1},
  {         1,  1, 10032010, 40,        10,100, 10, 20, 10,  1,  1,  1,  1,  1,  1,  1},
  { 110041010, 10,       10, 40, 110012010, 70, 30, 30, 10,  1,  1,  1, 10, 10, 10, 10},
  {        30, 30,110022030, 50,        30, 80, 10, 20, 10, 10, 10, 10, 10, 10, 10, 10},
  { 110011010, 10,       10, 40,         1,  1,  1, 10, 10, 10, 10, 10, 10, 10, 10, 10},
  {        10,120,       10, 40,       110, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
  {         1,  1,        1,  1,         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
  {         1,  1,        1,  1,         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
  {         1,  1,        1, 10,        10,9,9,9,1,2,3,4,5,6,7,8},
  {        10, 10,       10, 10,        10,10,10,10,1,2,3,4,5,6,7,8},
  {        10, 10,       10, 10,        10,11,11,11,1,2,3,4,5,6,7,8},
  {        10, 10,       10, 10,        10,12,12,12,1,2,3,4,5,6,7,8}
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
