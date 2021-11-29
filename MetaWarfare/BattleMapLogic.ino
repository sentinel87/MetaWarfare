#define ATTACK_ACTION 1
#define STOP_ACTION 2
#define CAPTURE_ACTION 3

#define RESUME_INFO_ACTION 1
#define END_TURN_INFO_ACTION 2
#define SAVE_INFO_ACTION 3
#define QUIT_INFO_ACTION 4

#define IDLE_MODE 0
#define MOVEMENT_MODE 1
#define UNIT_MENU_MODE 2
#define TARGET_MODE 3
#define INFO_MODE 4

#define PLAYER_1 1
#define PLAYER_2 2

int row = 0;
int column = 0;

int expandedWidth = 8;
int expandedHeight = 10;

int baseTileRow = 0;
int baseTileColumn = 0;
int returnTileRow = 0;
int returnTileColumn = 0;
Unit selectedUnit = NONE;

int mapMode = IDLE_MODE;
bool cancelMode=false;
bool noMove=false;

int menuSelection=1;
int infoSelection=1;

bool AITurn=false;

void BattleMap()
{
  drawMap();
  if(AITurn==false)
  {
    if(mapMode == UNIT_MENU_MODE)
      drawDropdownMenu(posX,posY,menuSelection);
    else if(mapMode == INFO_MODE)
      drawInfoMenu(infoSelection);
    
    if(gb.buttons.repeat(BUTTON_UP,3))
    {
      if(mapMode == UNIT_MENU_MODE)
      {
        if(menuSelection==ATTACK_ACTION)
        {
          if(selectedUnit.unitId==7 || selectedUnit.unitId==8)
            menuSelection=CAPTURE_ACTION;
          else
            menuSelection=STOP_ACTION;
        }
        else if(menuSelection==CAPTURE_ACTION)
          menuSelection=STOP_ACTION;
        else
          menuSelection=ATTACK_ACTION;
      }
      else if(mapMode == INFO_MODE)
      {
        if(infoSelection==RESUME_INFO_ACTION)
          infoSelection=QUIT_INFO_ACTION;
        else if(infoSelection==QUIT_INFO_ACTION)
          infoSelection=SAVE_INFO_ACTION;
        else if(infoSelection==SAVE_INFO_ACTION)
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
    else if(gb.buttons.repeat(BUTTON_DOWN,3))
    {
      if(mapMode == UNIT_MENU_MODE)
      {
        if(menuSelection==ATTACK_ACTION)
          menuSelection=STOP_ACTION;
        else if(menuSelection==STOP_ACTION)
        {
          if(selectedUnit.unitId==7 || selectedUnit.unitId==8)
            menuSelection=CAPTURE_ACTION;
          else
            menuSelection=ATTACK_ACTION;
        }
        else
          menuSelection=ATTACK_ACTION;
      }
      else if(mapMode == INFO_MODE)
      {
        if(infoSelection==RESUME_INFO_ACTION)
          infoSelection=END_TURN_INFO_ACTION;
        else if(infoSelection==END_TURN_INFO_ACTION)
          infoSelection=SAVE_INFO_ACTION;
        else if(infoSelection==SAVE_INFO_ACTION)
          infoSelection=QUIT_INFO_ACTION;
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
    else if(gb.buttons.repeat(BUTTON_LEFT,3))
    {
      if(mapMode == UNIT_MENU_MODE)
      {
        if(menuSelection==ATTACK_ACTION)
        {
          if(selectedUnit.unitId==7 || selectedUnit.unitId==8)
            menuSelection=CAPTURE_ACTION;
          else
            menuSelection=STOP_ACTION;
        }
        else if(menuSelection==CAPTURE_ACTION)
          menuSelection=STOP_ACTION;
        else
          menuSelection=ATTACK_ACTION;
      }
      else if(mapMode == INFO_MODE)
      {
        if(infoSelection==RESUME_INFO_ACTION)
          infoSelection=QUIT_INFO_ACTION;
        else if(infoSelection==QUIT_INFO_ACTION)
          infoSelection=SAVE_INFO_ACTION;
        else if(infoSelection==SAVE_INFO_ACTION)
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
    else if(gb.buttons.repeat(BUTTON_RIGHT,3))
    {
      if(mapMode == UNIT_MENU_MODE)
      {
        if(menuSelection==ATTACK_ACTION)
          menuSelection=STOP_ACTION;
        else if(menuSelection==STOP_ACTION)
        {
          if(selectedUnit.unitId==7 || selectedUnit.unitId==8)
            menuSelection=CAPTURE_ACTION;
          else
            menuSelection=ATTACK_ACTION;
        }
        else
          menuSelection=ATTACK_ACTION;
      }
      else if(mapMode == INFO_MODE)
      {
        if(infoSelection==RESUME_INFO_ACTION)
          infoSelection=END_TURN_INFO_ACTION;
        else if(infoSelection==END_TURN_INFO_ACTION)
          infoSelection=SAVE_INFO_ACTION;
        else if(infoSelection==SAVE_INFO_ACTION)
          infoSelection=QUIT_INFO_ACTION;
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
          noMove=true;
          clearGrid();
          menuSelection = ATTACK_ACTION;
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
            if(CurrentBoard[row][column].unitId==5 || CurrentBoard[row][column].unitId==6) // Artillery can only move without attack
            {
              CurrentBoard[row][column].active=0;
              mapMode = IDLE_MODE;
              cancelMode=false;
            }
            else
            {
              menuSelection = ATTACK_ACTION;
              mapMode = UNIT_MENU_MODE; 
            } 
          }
        }
      }
      else if(mapMode == TARGET_MODE) // Attack action
      {
          if(CurrentBoard[row][column].unitId!=0 && CurrentBoard[row][column].player!=CurrentPlayer->id && CurrentBoard[row][column].moveGrid==2)
          {
            mapMode = IDLE_MODE;
            CurrentBoard[baseTileRow][baseTileColumn].active=0;
            //Prepare tiles for battle scene
            Attacker = &CurrentBoard[baseTileRow][baseTileColumn];
            Defender = &CurrentBoard[row][column];
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
          if((CurrentBoard[baseTileRow][baseTileColumn].terrainTexture==11 || CurrentBoard[baseTileRow][baseTileColumn].terrainTexture==12 || CurrentBoard[baseTileRow][baseTileColumn].terrainTexture==25 || CurrentBoard[baseTileRow][baseTileColumn].terrainTexture==30) 
            && (CurrentBoard[baseTileRow][baseTileColumn].unitId==7 || CurrentBoard[baseTileRow][baseTileColumn].unitId==8)
            && CurrentBoard[baseTileRow][baseTileColumn].playerBuilding!=CurrentPlayer->id)
            {
              CurrentBoard[baseTileRow][baseTileColumn].playerBuilding=CurrentPlayer->id;
              CurrentBoard[baseTileRow][baseTileColumn].active=0;
              cancelMode=false;
              if(CurrentBoard[baseTileRow][baseTileColumn].terrainTexture==25) //if player capture capital
              {
                Winner=CurrentPlayer->id; 
                CurrentPlayer->points+=200;
                mapMode = IDLE_MODE;
                SceneMode = OUTCOME_MODE;
                return;
              }
              mapMode = IDLE_MODE;
              if(CurrentPlayer->id==1)
              {
                gb.lights.fill(RED);
              }
              else if(CurrentPlayer->id==2)
              {
                gb.lights.fill(BLUE);
              }
              gb.sound.fx(captureSound);
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
        else if(infoSelection==SAVE_INFO_ACTION)
        {
          SaveGame();
        }
        else if(infoSelection==QUIT_INFO_ACTION) //quit to main menu
        {
          SceneMode=MENU_MODE;
        }
        mapMode = IDLE_MODE;
      }
      else // Selection state
      {
        noMove=false;
        if(CurrentBoard[row][column].unitId!=0 && CurrentBoard[row][column].active==1 && CurrentBoard[row][column].player==CurrentPlayer->id) // Select unit
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
          gb.sound.fx(selectSound);
        }
        else if(CurrentBoard[row][column].unitId==0 && CurrentBoard[row][column].playerBuilding==CurrentPlayer->id && CurrentBoard[row][column].terrainTexture==11) // Select base
        {
          baseTileRow = row;
          baseTileColumn = column;
          BaseLocation = &CurrentBoard[row][column];
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
          if(noMove==false)
          {
            CurrentBoard[baseTileRow][baseTileColumn].player=0;
            CurrentBoard[baseTileRow][baseTileColumn].unitId=0;
            CurrentBoard[baseTileRow][baseTileColumn].unitHp=0;
            CurrentBoard[baseTileRow][baseTileColumn].active=0;
          }
          cancelMode = false;
          mapMode = IDLE_MODE;
        }
        noMove=false;
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
  else    //AI taking control
  {
    consoleActionFrames();
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
  if((MapId==1 || MapId==2) && CurrentPlayer->id==1)
  {
    if(TurnCount<=4)
      TurnCount++;
  }
  int player1Buildings=0;
  int player2Buildings=0;
  int player1Bases=0;
  int player2Bases=0;
  int player1Units=0;
  int player2Units=0;
  bool flagCaptured=false;
  for(int i=0;i<16;i++)
  {
    for(int j=0;j<16;j++)
    {
      if(CurrentBoard[j][i].unitId!=0 && CurrentBoard[j][i].player==CurrentPlayer->id)
      {
        CurrentBoard[j][i].active=1;
      }
      if(CurrentBoard[j][i].unitId!=0)
      {
        if(CurrentBoard[j][i].player==1)
        {
          player1Units++;
        }
        else if(CurrentBoard[j][i].player==2)
        {
          player2Units++;
        }
      }
      if(CurrentBoard[j][i].terrainTexture==11 || CurrentBoard[j][i].terrainTexture==12)
      {
        if(CurrentBoard[j][i].terrainTexture==11 && CurrentBoard[j][i].playerBuilding==1)
          player1Bases++;
        else if(CurrentBoard[j][i].terrainTexture==11 && CurrentBoard[j][i].playerBuilding==2)
          player2Bases++;  

        if(CurrentBoard[j][i].terrainTexture==12 && CurrentBoard[j][i].playerBuilding==1)
          player1Buildings++;
        else if(CurrentBoard[j][i].terrainTexture==12 && CurrentBoard[j][i].playerBuilding==2)
          player2Buildings++;  
      }
      if(CurrentBoard[j][i].keyTile==1 && CurrentBoard[j][i].unitId!=0 && CurrentBoard[j][i].player==1) //only player 1
      {
        flagCaptured=true;
      }
    }
  }
  if(GameMode==CAPTURE_MODE)
  {
    if(player1Buildings>=8 || player2Buildings>=8) // Capture victory
    {
      Winner=CurrentPlayer->id;
      CurrentPlayer->points+=200;
      mapMode = IDLE_MODE;
      SceneMode = OUTCOME_MODE;
      return;
    }
  }
  else if(GameMode==DEATHMATCH_MODE)
  {
    if(player1Units==0 || player2Units==0)
    {
      if(player1Units==0)
        Winner = 2;
      else
        Winner = 1;
      mapMode = IDLE_MODE;
      SceneMode = OUTCOME_MODE;
      return;
    }
  }
  else if(GameMode==CAPTURE_FLAG_MODE)
  {
    if(flagCaptured==true) //If player wins
    {
      CurrentPlayer->points+=50;
      Winner=CurrentPlayer->id;
      mapMode = IDLE_MODE;
      SceneMode = OUTCOME_MODE;
      return;
    }
    if(player1Units==0 && player1Bases==0)
    {
      Winner = 2;
      mapMode = IDLE_MODE;
      SceneMode = OUTCOME_MODE;
      return;
    }
  }
  else //Conquest mode
  {
    if(player1Units==0 && player1Bases==0)
    {
      Winner = 2;
      CurrentPlayer=&Player_2; //for score result
      mapMode = IDLE_MODE;
      SceneMode = OUTCOME_MODE;
      return;
    }
    if(player2Units==0 && player2Bases==0)
    {
      Winner = 1;
      CurrentPlayer=&Player_1; //for score result
      mapMode = IDLE_MODE;
      SceneMode = OUTCOME_MODE;
      return;
    }
  }

  if(CurrentPlayer->id==PLAYER_1)
  {
    CurrentPlayer=&Player_2;
    CountPlayerStats();
    if(IsConsoleOpponent==true)
    {
      AITurn = true;
    }
    prepareConsoleLogic();
    gb.lights.fill(BLUE);
    gb.gui.popup("PLAYER 2 TURN",50);
  }
  else
  {
    CurrentPlayer=&Player_1;
    CountPlayerStats();
    AITurn = false;
    if(MapId==1 || MapId==2) //tutorials
    {
      if(TurnCount<=4)
      {
        SceneMode=TUTORIAL_MODE;
      }
    }
    gb.lights.fill(RED);
    gb.gui.popup("PLAYER 1 TURN",50);
  }
}

void CountPlayerStats()
{
  CurrentPlayer->totalUnits=0;
  for(int i=0;i<16;i++)
  {
    for(int j=0;j<16;j++)
    {
      if((CurrentBoard[i][j].terrainTexture==11 || CurrentBoard[i][j].terrainTexture==12 || CurrentBoard[i][j].terrainTexture==25) && CurrentBoard[i][j].playerBuilding==CurrentPlayer->id)
      {
        if(CurrentPlayer->funds<9900)
        {
          CurrentPlayer->funds += 100;
          if(CurrentPlayer->funds>=10000)
          {
            CurrentPlayer->funds=9900;
          }
        }
      }
      if(CurrentBoard[i][j].unitId!=0 && CurrentBoard[i][j].player==CurrentPlayer->id)
      {
        CurrentPlayer->totalUnits += 1;
      }
      if(CurrentBoard[i][j].terrainTexture==30 && CurrentBoard[i][j].playerBuilding==CurrentPlayer->id && CurrentBoard[i][j].unitId!=0 && CurrentBoard[i][j].player==CurrentPlayer->id) //hospital regeneration
      {
        if(CurrentBoard[i][j].unitHp<10)
        {
          CurrentBoard[i][j].unitHp+=2;
          if(CurrentBoard[i][j].unitHp>10)
          {
            CurrentBoard[i][j].unitHp=10;
          }
        }
      }
    }
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
    if(maxX>15)
        maxX=15;
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
            {
                CurrentBoard[tRow+m][tColumn].moveGrid=1;
            }
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
    if(maxX>15)
        maxX=15;
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
    for(int j=0;j<16;j++)
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
    if(tile.unitId!=0 && tile.player!=CurrentPlayer->id)
        return true;
    return false;
}
