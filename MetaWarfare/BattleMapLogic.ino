#define ATTACK_ACTION 1
#define STOP_ACTION 2

#define RESUME_INFO_ACTION 1
#define END_TURN_INFO_ACTION 2
#define SAVE_INFO_ACTION 3

#define PLAYER_1 1
#define PLAYER_2 2

int currentPlayer=PLAYER_1;

int posX=0;
int posY=0;

int sRowIdx=0;
int sColIdx=0;

int row=0;
int column=0;

int expandedWidth=8;
int expandedHeight=6;

int baseTileRow=0;
int baseTileColumn=0;
Unit selectedUnit=NONE;
int selectedPosX=0;
int selectedPosY=0;

bool unitMovementMode=false;
bool unitMenuMode=false;
bool targetMode=false;
bool infoMode=false;

int menuSelection=1;
int infoSelection=1;

void BattleMap()
{
  drawMap();
  if(unitMenuMode==true)
  {
    drawDropdownMenu(posX,posY,menuSelection);
  }
  else if(infoMode==true)
  {
    drawInfoMenu(infoSelection);
  }
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(unitMenuMode==true)
    {
      if(menuSelection==ATTACK_ACTION)
        menuSelection=STOP_ACTION;
      else
        menuSelection=ATTACK_ACTION;
    }
    else if(infoMode==true)
    {
      if(infoSelection==RESUME_INFO_ACTION)
        infoSelection=END_TURN_INFO_ACTION;
      else
        infoSelection=RESUME_INFO_ACTION;
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
    if(unitMenuMode==true)
    {
      if(menuSelection==ATTACK_ACTION)
        menuSelection=STOP_ACTION;
      else
        menuSelection=ATTACK_ACTION;
    }
    else if(infoMode==true)
    {
      if(infoSelection==RESUME_INFO_ACTION)
        infoSelection=END_TURN_INFO_ACTION;
      else
        infoSelection=RESUME_INFO_ACTION;
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
    if(unitMenuMode==true)
    {
      if(menuSelection==ATTACK_ACTION)
        menuSelection=STOP_ACTION;
      else
        menuSelection=ATTACK_ACTION;
    }
    else if(infoMode==true)
    {
      if(infoSelection==RESUME_INFO_ACTION)
        infoSelection=END_TURN_INFO_ACTION;
      else
        infoSelection=RESUME_INFO_ACTION;
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
    if(unitMenuMode==true)
    {
      if(menuSelection==ATTACK_ACTION)
        menuSelection=STOP_ACTION;
      else
        menuSelection=ATTACK_ACTION;
    }
    else if(infoMode==true)
    {
      if(infoSelection==RESUME_INFO_ACTION)
        infoSelection=END_TURN_INFO_ACTION;
      else
        infoSelection=RESUME_INFO_ACTION;
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
      
    if(unitMovementMode==true) // Move action
    {
      if(selectedPosX==posX && selectedPosY==posY) // If unit does not want to move
      {
        baseTileRow=row;
        baseTileColumn=column;
        unitMovementMode=false;
        clearMovementGrid();
        unitMenuMode=true;
      }
      else // unit moves
      {
        if(CurrentBoard[row][column].terrainTexture!=0 && CurrentBoard[row][column].terrainTexture!=2 && CurrentBoard[row][column].unitId==0 && CurrentBoard[row][column].moveGrid==1)
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
          unitMovementMode=false;
          clearMovementGrid();
          menuSelection=ATTACK_ACTION;
          unitMenuMode=true;
        }
      }
    }
    else if(targetMode==true) // Attack action
    {
      if(checkTargetSelection() == true)
      {
        if(CurrentBoard[row][column].unitId!=0 && CurrentBoard[row][column].player!=currentPlayer)
        {
          targetMode=false;
          CurrentBoard[baseTileRow][baseTileColumn].active=0;
          //Prepare tiles for battle scene
          Attacker = CurrentBoard[baseTileRow][baseTileColumn];
          Defender = CurrentBoard[row][column];
          PrepareBattleScene();
          battleMode=true;
        }
      }
    }
    else if(unitMenuMode==true) // Dropdown menu
    {
      if(menuSelection==ATTACK_ACTION)
      {
        targetMode=true;
        unitMenuMode=false;
      }
      else //CANCEL
      {
        CurrentBoard[baseTileRow][baseTileColumn].active=0;
        unitMenuMode=false;
      }
    }
    else if(infoMode==true) // Info menu
    {
      if(infoSelection==END_TURN_INFO_ACTION)
      {
        endTurn(); 
      }
      infoMode=false;
    }
    else // Selection state
    {
      if(CurrentBoard[row][column].unitId!=0 && CurrentBoard[row][column].active==1 && CurrentBoard[row][column].player==currentPlayer)
      {
        baseTileRow=row;
        baseTileColumn=column;
        selectedUnit=getUnit(CurrentBoard[row][column].unitId);
        selectedPosY=posY;
        selectedPosX=posX;
        unitMovementMode=true;
        drawUnitMovementGrid();
      }
    }   
  }
  else if(gb.buttons.pressed(BUTTON_B))
  {
    if(unitMovementMode==true)
    {
      selectedUnit=NONE;
      unitMovementMode=false;
      clearMovementGrid();
      selectedPosX=0;
      selectedPosY=0;
    }
    else if(targetMode==true)
    {
      targetMode=false;
      unitMenuMode=true;
      row=baseTileRow;
      column=baseTileColumn;
    }
  }
  else if(gb.buttons.pressed(BUTTON_MENU))
  {
    if(unitMovementMode==false && unitMenuMode==false && targetMode==false)
    {
      if(infoMode!=true)
      {
        infoSelection=RESUME_INFO_ACTION;
        infoMode=true;
      }
      else
        infoMode=false; 
    }
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
  for(int i=0;i<16;i++)
  {
    for(int j=0;j<12;j++)
    {
      if(CurrentBoard[j][i].unitId!=0 && CurrentBoard[j][i].player==currentPlayer)
      {
        CurrentBoard[j][i].active=1;
      }
    }
  }
  if(currentPlayer==PLAYER_1)
  {
    currentPlayer=PLAYER_2;
  }
  else
  {
    currentPlayer=PLAYER_1;
  }
}

bool checkTargetSelection()
{
  int tRow = sRowIdx;
  if(posY>0)
    tRow+=(posY/10);
  int tColumn = sColIdx;
  if(posX>0)
    tColumn+=(posX/10);

  if(baseTileRow==tRow)
  {
    if(baseTileColumn+1==tColumn || baseTileColumn-1==tColumn)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else if(baseTileColumn==tColumn)
  {
    if(baseTileRow+1==tRow || baseTileRow-1==tRow)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

void drawUnitMovementGrid()
{
  int tRow = sRowIdx;
  if(posY>0)
    tRow+=(posY/10);
  int tColumn = sColIdx;
  if(posX>0)
    tColumn+=(posX/10);

  if(selectedUnit.unitId!=0)
  {
    unsigned int movement=selectedUnit.movement;
    unsigned int canCrossMountains=selectedUnit.canCrossMountains;
    unsigned int crossMove=selectedUnit.crossMove;

    //Replace max vals for array
    int minX=tRow-movement;
    if(minX<0)
        minX=0;
    int minY = tColumn-movement;
    if(minY<0)
        minY=0;
    int maxX=tRow+movement;
    if(maxX>11)
        maxX=11;
    int maxY = tColumn+movement;
    if(maxY>15)
        maxY=15;

    CurrentBoard[tRow][tColumn].moveGrid=1;
    for(int m=1;m<=movement;m++)
    {
        if(tRow+m<=maxX)
        {
            if(restrictedMove(CurrentBoard[tRow+m][tColumn],canCrossMountains) || CurrentBoard[tRow+(m-1)][tColumn].moveGrid!=1)
            {
                CurrentBoard[tRow+m][tColumn].moveGrid=0;
            }
            else
                CurrentBoard[tRow+m][tColumn].moveGrid=1;
        }
        if(tRow-m>=minX)
        {
            if(restrictedMove(CurrentBoard[tRow-m][tColumn],canCrossMountains) || CurrentBoard[tRow-(m-1)][tColumn].moveGrid!=1)
            {
                CurrentBoard[tRow-m][tColumn].moveGrid=0;
            }
            else
                CurrentBoard[tRow-m][tColumn].moveGrid=1;
        }
        if(tColumn+m<=maxY)
        {
            if(restrictedMove(CurrentBoard[tRow][tColumn+m],canCrossMountains) || CurrentBoard[tRow][tColumn+(m-1)].moveGrid!=1)
            {
                CurrentBoard[tRow][tColumn+m].moveGrid=0;
            }
            else
                CurrentBoard[tRow][tColumn+m].moveGrid=1;
        }
        if(tColumn-m>=minY)
        {
            if(restrictedMove(CurrentBoard[tRow][tColumn-m],canCrossMountains) || CurrentBoard[tRow][tColumn-(m-1)].moveGrid!=1)
            {
                CurrentBoard[tRow][tColumn-m].moveGrid=0;
            }
            else
                CurrentBoard[tRow][tColumn-m].moveGrid=1;
        }
        if(crossMove==0)
        {
            if(tColumn-m>=minY && tRow-m>=minX)
            {
                if(restrictedMove(CurrentBoard[tRow-m][tColumn-m],canCrossMountains) || CurrentBoard[tRow-(m-1)][tColumn-(m-1)].moveGrid!=1)
                {
                    CurrentBoard[tRow-m][tColumn-m].moveGrid=0;
                }
                else
                    CurrentBoard[tRow-m][tColumn-m].moveGrid=1;
            }
            if(tColumn+m<=maxY && tRow+m<=maxX)
            {
                if(restrictedMove(CurrentBoard[tRow+m][tColumn+m],canCrossMountains) || CurrentBoard[tRow+(m-1)][tColumn+(m-1)].moveGrid!=1)
                {
                    CurrentBoard[tRow+m][tColumn+m].moveGrid=0;
                }
                else
                    CurrentBoard[tRow+m][tColumn+m].moveGrid=1;
            }
            if(tColumn-m>=minY && tRow+m<=maxX)
            {
                if(restrictedMove(CurrentBoard[tRow+m][tColumn-m],canCrossMountains) || CurrentBoard[tRow+(m-1)][tColumn-(m-1)].moveGrid!=1)
                {
                    CurrentBoard[tRow+m][tColumn-m].moveGrid=0;
                }
                else
                    CurrentBoard[tRow+m][tColumn-m].moveGrid=1;
            }
            if(tColumn+m<=maxY && tRow-m>=minX)
            {
                if(restrictedMove(CurrentBoard[tRow-m][tColumn+m],canCrossMountains) || CurrentBoard[tRow-(m-1)][tColumn+(m-1)].moveGrid!=1)
                {
                    CurrentBoard[tRow-m][tColumn+m].moveGrid=0;
                }
                else
                    CurrentBoard[tRow-m][tColumn+m].moveGrid=1;
            }
        }
    }
  }
}

void clearMovementGrid()
{
  for(int i=0;i<16;i++)
  {
    for(int j=0;j<12;j++)
    {
      CurrentBoard[j][i].moveGrid=0;
    }
  }
}

bool restrictedMove(GameTileStruct tile,unsigned int canCrossMountains)
{
    if(tile.terrainTexture==0)
        return true;
    if(canCrossMountains==0 && tile.terrainTexture==2)
        return true;
    if(tile.unitId!=0)
        return true;
    return false;
}
