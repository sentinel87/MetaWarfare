int currentPlayer=1;

int posX=0;
int posY=0;

int sRowIdx=0;
int sColIdx=0;

int row=0;
int column=0;

int expandedWidth=0;
int expandedHeight=0;

int baseTileRow=0;
int baseTileColumn=0;
Unit selectedUnit=NONE;
int selectedPosX=0;
int selectedPosY=0;

bool unitMode=false;
bool targetMode=false;

void Battle()
{
  drawMap();
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(targetMode==true)
    {
      checkTargetSelection(1);
    }
    else
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
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(targetMode==true)
    {
      checkTargetSelection(2);
    }
    else
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
  }
  else if(gb.buttons.pressed(BUTTON_LEFT))
  {
    if(targetMode==true)
    {
      checkTargetSelection(3);
    }
    else
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
  }
  else if(gb.buttons.pressed(BUTTON_RIGHT))
  {
    if(targetMode==true)
    {
      checkTargetSelection(4);
    }
    else
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
  }
  else if(gb.buttons.pressed(BUTTON_A))
  {
    row = sRowIdx;
    if(posY>0)
      row+=(posY/10);
    column = sColIdx;
    if(posX>0)
      column+=(posX/10);
      
    if(unitMode==true)
    {
      if(selectedPosX!=posX || selectedPosY!=posY)
      {
        if(CurrentBoard[row][column].terrainTexture!=0 && CurrentBoard[row][column].terrainTexture!=2 && CurrentBoard[row][column].unitId==0)
        {
          //Fill destination tile with unit info
          CurrentBoard[row][column].player=CurrentBoard[baseTileRow][baseTileColumn].player;
          CurrentBoard[row][column].unitId=CurrentBoard[baseTileRow][baseTileColumn].unitId;
          CurrentBoard[row][column].unitHp=CurrentBoard[baseTileRow][baseTileColumn].unitHp;
          CurrentBoard[row][column].active=1;
          //Remove unit info from starting tile
          CurrentBoard[baseTileRow][baseTileColumn].player=0;
          CurrentBoard[baseTileRow][baseTileColumn].unitId=0;
          CurrentBoard[baseTileRow][baseTileColumn].unitHp=0;
          CurrentBoard[baseTileRow][baseTileColumn].active=0;
          baseTileRow=row;
          baseTileColumn=column;
          unitMode=false;
          targetMode=true;
        }
      }
    }
    else if(targetMode==true)
    {
      targetMode=false;
      CurrentBoard[baseTileRow][baseTileColumn].active=0;
    }
    else
    {
      if(CurrentBoard[row][column].unitId!=0 && CurrentBoard[row][column].active==1 && CurrentBoard[row][column].player==currentPlayer)
      {
        baseTileRow=row;
        baseTileColumn=column;
        selectedUnit=getUnit(CurrentBoard[row][column].unitId);
        selectedPosY=posY;
        selectedPosX=posX;
        unitMode=true;
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
      if(CurrentBoard[j][i].unitId!=0 && CurrentBoard[j][i].player==currentPlayer)
      {
        CurrentBoard[j][i].active=1;
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

void checkTargetSelection(int arrowDirection)
{
  int tRow = sRowIdx;
  if(posY>0)
    tRow+=(posY/10);
  int tColumn = sColIdx;
  if(posX>0)
    tColumn+=(posX/10);
    
  if(arrowDirection==1)
  {
    if(tRow==0)
      return;
    if(CurrentBoard[tRow-1][tColumn].unitId!=0 && CurrentBoard[tRow-1][tColumn].player!=currentPlayer)
    {
      targetMode=false;
      CurrentBoard[baseTileRow][baseTileColumn].active=0;
    }
  }
  else if(arrowDirection==2)
  {
    if(tRow==5)
      return;
    if(CurrentBoard[tRow+1][tColumn].unitId!=0 && CurrentBoard[tRow+1][tColumn].player!=currentPlayer)
    {
      targetMode=false;
      CurrentBoard[baseTileRow][baseTileColumn].active=0;
    }
  }
  else if(arrowDirection==3)
  {
    if(tColumn==0)
      return;
    if(CurrentBoard[tRow][tColumn-1].unitId!=0 && CurrentBoard[tRow][tColumn-1].player!=currentPlayer)
    {
      targetMode=false;
      CurrentBoard[baseTileRow][baseTileColumn].active=0;
    }
  }
  else if(arrowDirection==4)
  {
    if(tColumn==7)
      return;
    if(CurrentBoard[tRow][tColumn+1].unitId!=0 && CurrentBoard[tRow][tColumn+1].player!=currentPlayer)
    {
      targetMode=false;
      CurrentBoard[baseTileRow][baseTileColumn].active=0;
    }
  }
}
