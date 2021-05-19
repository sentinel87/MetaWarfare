#define ATTACK_ACTION 1
#define STOP_ACTION 2
#define CAPTURE_ACTION 3

#define RESUME_INFO_ACTION 1
#define END_TURN_INFO_ACTION 2
#define SAVE_INFO_ACTION 3

#define IDLE_MODE 0
#define MOVEMENT_MODE 1
#define UNIT_MENU_MODE 2
#define TARGET_MODE 3
#define INFO_MODE 4

#define PLAYER_1 1
#define PLAYER_2 2

//int currentPlayer = PLAYER_1;

int posX = 0;
int posY = 0;

int sRowIdx = 0;
int sColIdx = 0;

int row = 0;
int column = 0;

int expandedWidth = 8;
int expandedHeight = 6;

int baseTileRow = 0;
int baseTileColumn = 0;
int returnTileRow = 0;
int returnTileColumn = 0;
Unit selectedUnit = NONE;

int mapMode = IDLE_MODE;
bool cancelMode=false;

int menuSelection=1;
int infoSelection=1;

void BattleMap()
{
  drawMap();
  if(mapMode == UNIT_MENU_MODE)
    drawDropdownMenu(posX,posY,menuSelection);
  else if(mapMode == INFO_MODE)
    drawInfoMenu(infoSelection);
  
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(mapMode == UNIT_MENU_MODE)
    {
      if(menuSelection==ATTACK_ACTION)
        menuSelection=CAPTURE_ACTION;
      else if(menuSelection==CAPTURE_ACTION)
        menuSelection=STOP_ACTION;
      else
        menuSelection=ATTACK_ACTION;
    }
    else if(mapMode == INFO_MODE)
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
          sRowIdx--;
      }
    }
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(mapMode == UNIT_MENU_MODE)
    {
      if(menuSelection==ATTACK_ACTION)
        menuSelection=STOP_ACTION;
      else if(menuSelection==STOP_ACTION)
        menuSelection=CAPTURE_ACTION;
      else
        menuSelection=ATTACK_ACTION;
    }
    else if(mapMode == INFO_MODE)
    {
      if(infoSelection==RESUME_INFO_ACTION)
        infoSelection=END_TURN_INFO_ACTION;
      else
        infoSelection=RESUME_INFO_ACTION;
    }
    else
    {
      if(posY!=50)
        posY+=10;
      else
      {
        if(sRowIdx<expandedHeight)
          sRowIdx++;
      }
    }
  }
  else if(gb.buttons.pressed(BUTTON_LEFT))
  {
    if(mapMode == UNIT_MENU_MODE)
    {
      if(menuSelection==ATTACK_ACTION)
        menuSelection=CAPTURE_ACTION;
      else if(menuSelection==CAPTURE_ACTION)
        menuSelection=STOP_ACTION;
      else
        menuSelection=ATTACK_ACTION;
    }
    else if(mapMode == INFO_MODE)
    {
      if(infoSelection==RESUME_INFO_ACTION)
        infoSelection=END_TURN_INFO_ACTION;
      else
        infoSelection=RESUME_INFO_ACTION;
    }
    else
    {
      if(posX!=0)
        posX-=10;
      else
      {
        if(sColIdx>0)
          sColIdx--;
      }
    }
  }
  else if(gb.buttons.pressed(BUTTON_RIGHT))
  {
    if(mapMode == UNIT_MENU_MODE)
    {
      if(menuSelection==ATTACK_ACTION)
        menuSelection=STOP_ACTION;
      else if(menuSelection==STOP_ACTION)
        menuSelection=CAPTURE_ACTION;
      else
        menuSelection=ATTACK_ACTION;
    }
    else if(mapMode == INFO_MODE)
    {
      if(infoSelection==RESUME_INFO_ACTION)
        infoSelection=END_TURN_INFO_ACTION;
      else
        infoSelection=RESUME_INFO_ACTION;
    }
    else
    {
      if(posX!=70)
        posX+=10;
      else
      {
        if(sColIdx<expandedWidth)
          sColIdx++;
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
      
    if(mapMode == MOVEMENT_MODE) // Move action
    {
      if(row==baseTileRow && column==baseTileColumn) // If unit does not want to move
      {
        clearGrid();
        mapMode = UNIT_MENU_MODE;
      }
      else // unit moves
      {
        if(CurrentBoard[row][column].unitId==0 && CurrentBoard[row][column].moveGrid==1)
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
          clearGrid();
          menuSelection = ATTACK_ACTION;
          mapMode = UNIT_MENU_MODE; 
        }
      }
    }
    else if(mapMode == TARGET_MODE) // Attack action
    {
        if(CurrentBoard[row][column].unitId!=0 && CurrentBoard[row][column].player!=CurrentPlayer.id && CurrentBoard[row][column].moveGrid==2)
        {
          mapMode = IDLE_MODE;
          CurrentBoard[baseTileRow][baseTileColumn].active=0;
          //Prepare tiles for battle scene
          Attacker = CurrentBoard[baseTileRow][baseTileColumn];
          Defender = CurrentBoard[row][column];
          PrepareBattleScene();
          SceneMode=BATTLE_MODE;
          cancelMode=false;
          clearGrid();
        }
    }
    else if(mapMode == UNIT_MENU_MODE) // Dropdown menu
    {
      if(menuSelection==ATTACK_ACTION)
      {
        drawUnitAttackGrid();
        mapMode = TARGET_MODE;
      }
      else if(menuSelection==CAPTURE_ACTION)
      {
        if((CurrentBoard[baseTileRow][baseTileColumn].terrainTexture==11 || CurrentBoard[baseTileRow][baseTileColumn].terrainTexture==12) 
          && (CurrentBoard[baseTileRow][baseTileColumn].unitId==7 || CurrentBoard[baseTileRow][baseTileColumn].unitId==8)
          && CurrentBoard[baseTileRow][baseTileColumn].playerBuilding!=CurrentPlayer.id)
          {
            CurrentBoard[baseTileRow][baseTileColumn].playerBuilding=CurrentPlayer.id;
            CurrentBoard[baseTileRow][baseTileColumn].active=0;
            cancelMode=false;
            mapMode = IDLE_MODE;
            gb.gui.popup("BUILDING ACQUIRED!",50);
          }
      }
      else //CANCEL
      {
        CurrentBoard[baseTileRow][baseTileColumn].active=0;
        mapMode = IDLE_MODE;
        cancelMode=false;
      }
    }
    else if(mapMode == INFO_MODE) // Info menu
    {
      if(infoSelection==END_TURN_INFO_ACTION)
      {
        endTurn(); 
      }
      mapMode = IDLE_MODE;
    }
    else // Selection state
    {
      if(CurrentBoard[row][column].unitId!=0 && CurrentBoard[row][column].active==1 && CurrentBoard[row][column].player==CurrentPlayer.id) // Select unit
      {
        baseTileRow=row;
        baseTileColumn=column;
        //Save position for cancel mode
        returnTileRow = row;
        returnTileColumn = column;
        selectedUnit=getUnit(CurrentBoard[row][column].unitId);
        mapMode = MOVEMENT_MODE;
        cancelMode=true;
        drawUnitMovementGrid();
      }
      else if(CurrentBoard[row][column].unitId==0 && CurrentBoard[row][column].playerBuilding==CurrentPlayer.id && CurrentBoard[row][column].terrainTexture==11) // Select base
      {
        baseTileRow = row;
        baseTileColumn = column;
        BaseLocation.row = row;
        BaseLocation.column = column;
        SceneMode = BASE_MODE;
      }
    }   
  }
  else if(gb.buttons.pressed(BUTTON_B))
  {
    if(cancelMode == true)
    {
      if(mapMode == MOVEMENT_MODE)
      {
        selectedUnit=NONE;
        mapMode = IDLE_MODE;
        clearGrid();
      }
      else if(mapMode == UNIT_MENU_MODE || mapMode== TARGET_MODE)
      {
        clearGrid();
        CurrentBoard[returnTileRow][returnTileColumn].player=CurrentBoard[baseTileRow][baseTileColumn].player;
        CurrentBoard[returnTileRow][returnTileColumn].unitId=CurrentBoard[baseTileRow][baseTileColumn].unitId;
        CurrentBoard[returnTileRow][returnTileColumn].unitHp=CurrentBoard[baseTileRow][baseTileColumn].unitHp;
        CurrentBoard[returnTileRow][returnTileColumn].active=1;
        CurrentBoard[baseTileRow][baseTileColumn].player=0;
        CurrentBoard[baseTileRow][baseTileColumn].unitId=0;
        CurrentBoard[baseTileRow][baseTileColumn].unitHp=0;
        CurrentBoard[baseTileRow][baseTileColumn].active=0;
        cancelMode = false;
        mapMode = IDLE_MODE;
      }
    }
  }
  else if(gb.buttons.pressed(BUTTON_MENU))
  {
    if(mapMode == IDLE_MODE)
    {
      infoSelection=RESUME_INFO_ACTION;
      mapMode = INFO_MODE;
    }
    else if(mapMode == INFO_MODE)
      mapMode = IDLE_MODE; 
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
      if(CurrentBoard[j][i].unitId!=0 && CurrentBoard[j][i].player==CurrentPlayer.id)
      {
        CurrentBoard[j][i].active=1;
      }
    }
  }
  if(CurrentPlayer.id==PLAYER_1)
  {
    CurrentPlayer=Player_2;
    gb.gui.popup("PLAYER 2 TURN",50);
  }
  else
  {
    CurrentPlayer=Player_1;
    gb.gui.popup("PLAYER 1 TURN",50);
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

void drawUnitAttackGrid()
{
  int tRow = sRowIdx;
  if(posY>0)
    tRow+=(posY/10);
  int tColumn = sColIdx;
  if(posX>0)
    tColumn+=(posX/10);
  
  if(selectedUnit.unitId!=0)
  {
    unsigned int range=selectedUnit.attackRange;

    int minX=tRow-range;
    if(minX<0)
        minX=0;
    int minY = tColumn-range;
    if(minY<0)
        minY=0;
    int maxX=tRow+range;
    if(maxX>11)
        maxX=11;
    int maxY = tColumn+range;
    if(maxY>15)
        maxY=15;

    for(int r=1;r<=range;r++)
    {
        if(r==range)
        {
            if(tRow-r>=minX)
                CurrentBoard[tRow-r][tColumn].moveGrid=2;
            if(tRow+r<=maxX)
                CurrentBoard[tRow+r][tColumn].moveGrid=2;
            if(tColumn-r>=minY)
                CurrentBoard[tRow][tColumn-r].moveGrid=2;
            if(tColumn+r<=maxY)
                CurrentBoard[tRow][tColumn+r].moveGrid=2;
        }
        else if(r==1)
        {
            if(selectedUnit.unitId!=6) //SSM
            {
                if(tRow-r>=minX)
                    CurrentBoard[tRow-r][tColumn].moveGrid=2;
                if(tRow+r<=maxX)
                    CurrentBoard[tRow+r][tColumn].moveGrid=2;
                if(tColumn-r>=minY)
                    CurrentBoard[tRow][tColumn-r].moveGrid=2;
                if(tColumn+r<=maxY)
                    CurrentBoard[tRow][tColumn+r].moveGrid=2;
            }
            if(tRow-r>=minX && tColumn-r>=minY)
                CurrentBoard[tRow-r][tColumn-r].moveGrid=2;
            if(tRow+r<=maxX && tColumn+r<=maxY)
                CurrentBoard[tRow+r][tColumn+r].moveGrid=2;
            if(tRow+r<=maxX && tColumn-r>=minY)
                CurrentBoard[tRow+r][tColumn-r].moveGrid=2;
            if(tRow-r>=minX && tColumn+r<=maxY)
                CurrentBoard[tRow-r][tColumn+r].moveGrid=2;
        }
        else
        {
            if(tRow-r>=minX)
            {
                CurrentBoard[tRow-r][tColumn].moveGrid=2;
                if(tColumn-1>=minY)
                    CurrentBoard[tRow-r][tColumn-1].moveGrid=2;
                if(tColumn+1<=maxY)
                    CurrentBoard[tRow-r][tColumn+1].moveGrid=2;
            }
            if(tRow+r<=maxX)
            {
                CurrentBoard[tRow+r][tColumn].moveGrid=2;
                if(tColumn-1>=minY)
                    CurrentBoard[tRow+r][tColumn-1].moveGrid=2;
                if(tColumn+1<=maxY)
                    CurrentBoard[tRow+r][tColumn+1].moveGrid=2;
            }
            if(tColumn-r>=minY)
            {
                CurrentBoard[tRow][tColumn-r].moveGrid=2;
                if(tRow-1>=minX)
                    CurrentBoard[tRow-1][tColumn-r].moveGrid=2;
                if(tRow+1<=maxX)
                    CurrentBoard[tRow+1][tColumn-r].moveGrid=2;
            }
            if(tColumn+r<=maxY)
            {
                CurrentBoard[tRow][tColumn+r].moveGrid=2;
                if(tRow-1>=minX)
                    CurrentBoard[tRow-1][tColumn+r].moveGrid=2;
                if(tRow+1<=maxX)
                    CurrentBoard[tRow+1][tColumn+r].moveGrid=2;
            }
        }
    }
  }
}

void clearGrid()
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
