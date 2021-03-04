#include <Gamebuino-Meta.h>

int field[12][16] ={
  {1,1,1,1,1,1,1,1,1,2,3,4,5,6,7,8},
  {2,2,2,2,2,2,2,2,1,2,3,4,5,6,7,8},
  {3,3,3,3,3,3,3,3,1,2,3,4,5,6,7,8},
  {4,4,4,4,4,4,4,4,1,2,3,4,5,6,7,8},
  {5,5,5,5,5,5,5,5,1,2,3,4,5,6,7,8},
  {6,6,6,6,6,6,6,6,1,2,3,4,5,6,7,8},
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

void drawMap()
{
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<6;j++)
    {
      switch(field[j+sRowIdx][i+sColIdx])
      {
        case 1:
          gb.display.setColor(BLUE); break;
        case 2:
          gb.display.setColor(RED); break;
        case 3:
          gb.display.setColor(GREEN); break;
        case 4:
          gb.display.setColor(YELLOW); break;
        case 5:
          gb.display.setColor(ORANGE); break;
        case 6:
          gb.display.setColor(BLACK); break;
        case 7:
          gb.display.setColor(BROWN); break;
        case 8:
          gb.display.setColor(BEIGE); break;
        case 9:
          gb.display.setColor(PINK);break;
        case 10:
          gb.display.setColor(PURPLE);break;
        case 11:
          gb.display.setColor(DARKBLUE);break;
        case 12:
          gb.display.setColor(LIGHTGREEN);break;
      }
      gb.display.fillRect(i*10,j*10,10,10);
    }
  }
  gb.display.setColor(WHITE);
  gb.display.drawRect(posY,posX,10,10);
  gb.display.setFontSize(1);
  gb.display.setCursor(3,3);
  gb.display.println(selected);
}
