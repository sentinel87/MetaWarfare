#define ARTILLERY_PHASE 0
#define TANK_PHASE 1
#define INFANTRY_PHASE 2

#define P_SELECTION 0
#define P_SHOW_MOVEMENT_GRID 1
#define P_MOVE 2
#define P_SHOW_ATTACK_GRID 3
#define P_ATTACK 4

UnitLocation ConsoleUnits[25] {{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true},{0,0,0,true}};
int ConsoleUnitsCount=0;
int aiFrames=0;
int currentPhase=ARTILLERY_PHASE;
int actionPhase=P_SELECTION;

void prepareConsoleLogic()
{
  selectedUnit=NONE;
  ConsoleUnitsCount=0;
  currentPhase=ARTILLERY_PHASE;
  actionPhase=P_SELECTION;
  
  //clear units array
  for(int i=0;i<25;i++)
  {
    ConsoleUnits[i].row=0;
    ConsoleUnits[i].column=0;
    ConsoleUnits[i].unitId=0;
    ConsoleUnits[i].activated=true;
  }
  
  //fill units array
  int idx = 0;
  for(int i=0;i<16;i++)
  {
    for(int j=0;j<16;j++)
    {
      if(CurrentBoard[j][i].unitId!=0 && CurrentBoard[j][i].player==CurrentPlayer->id)
      {
        ConsoleUnits[idx].row=j;
        ConsoleUnits[idx].column=i;
        ConsoleUnits[idx].unitId=CurrentBoard[j][i].unitId;
        ConsoleUnits[idx].activated=false;

        if(idx<24)
        {
          idx++;
          ConsoleUnitsCount++;
        }
      }
    }
  }
}

bool getNextUnit()
{
  UnitLocation selectedConsoleUnit = getAvailableUnit();
  if(selectedConsoleUnit.unitId==0) //No units left
  {
    selectedUnit=NONE;
    return true;
  }
  else
  {
    selectedUnit=getUnit(selectedConsoleUnit.unitId);
    setScreenOnUnit(selectedConsoleUnit);
    return false;
  }
}

void unitActions()
{
  if(selectedUnit.unitId==5 || selectedUnit.unitId==6) // actions for artillery
  {
    if(actionPhase==P_SELECTION)
    {
      actionPhase=P_SHOW_ATTACK_GRID;
    }
    else if(actionPhase==P_SHOW_ATTACK_GRID)
    {
      drawUnitAttackGrid();
      actionPhase=P_ATTACK;
    }
    else //P_ATTACK
    {
      attackWithArtillery();
      clearGrid();
      actionPhase=P_SELECTION;
    }
  }
  else // actions for direct units
  {
    if(actionPhase==P_SELECTION)
    {
      actionPhase = P_SHOW_MOVEMENT_GRID;
    }
    else if(actionPhase==P_SHOW_MOVEMENT_GRID)
    {
      drawUnitMovementGrid();
      actionPhase=P_ATTACK;
    }
    else //P_ATTACK
    {
      attackWithDirectUnit();
      clearGrid();
      actionPhase=P_SELECTION;
    }
  }
}

void attackWithDirectUnit()
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
    
    int minX=tRow-movement-1;
    if(minX<0)
        minX=0;
    int minY = tColumn-movement-1;
    if(minY<0)
        minY=0;
    int maxX=tRow+movement+1;
    if(maxX>15)
        maxX=15;
    int maxY = tColumn+movement+1;
    if(maxY>15)
        maxY=15;

    int targetRow=-1;
    int targetColumn=-1;
    int unitDestionationRow=-1;
    int unitDestionationColumn=-1;
    bool located=false;

    for(int i=minX;i<maxX;i++) //Register all enemy units in range
    {
      for(int j=minY;j<maxY;j++)
      {
        if(CurrentBoard[i][j].unitId!=0 && CurrentBoard[i][j].player!=CurrentPlayer->id)
        {
          if(i>0)
          {
            if((CurrentBoard[i-1][j].unitId==0 && CurrentBoard[i-1][j].moveGrid==1) || ((i-1==tRow) && j==tColumn))
            {
              targetRow=i;
              targetColumn=j;
              unitDestionationRow=i-1;
              unitDestionationColumn=j;
              located=true;
              break;
            }
          }
          if(i<15)
          {
            if((CurrentBoard[i+1][j].unitId==0 && CurrentBoard[i+1][j].moveGrid==1) || ((i+1==tRow) && j==tColumn))
            {
              targetRow=i;
              targetColumn=j;
              unitDestionationRow=i+1;
              unitDestionationColumn=j;
              located=true;
              break;
            }
          }
          if(j>0)
          {
            if((CurrentBoard[i][j-1].unitId==0 && CurrentBoard[i][j-1].moveGrid==1) || (i==tRow && (j-1==tColumn)))
            {
              targetRow=i;
              targetColumn=j;
              unitDestionationRow=i;
              unitDestionationColumn=j-1;
              located=true;
              break;
            }
          }
          if(j<15)
          {
            if((CurrentBoard[i][j+1].unitId==0 && CurrentBoard[i][j+1].moveGrid==1) || (i==tRow && (j+1==tColumn)))
            {
              targetRow=i;
              targetColumn=j;
              unitDestionationRow=i;
              unitDestionationColumn=j+1;
              located=true;
              break;
            }
          }
        }
      }
      if(located==true)
      {
        break;
      }
    }

    if(targetRow!=-1 && targetColumn!=-1 && unitDestionationRow!=-1 && unitDestionationColumn!=-1)
    {
      if(unitDestionationRow==tRow && unitDestionationColumn==tColumn)
      {
        CurrentBoard[tRow][tColumn].active=0;
      }
      else
      {
        //Fill destination tile with unit info
        CurrentBoard[unitDestionationRow][unitDestionationColumn].player=CurrentBoard[tRow][tColumn].player;
        CurrentBoard[unitDestionationRow][unitDestionationColumn].unitId=CurrentBoard[tRow][tColumn].unitId;
        CurrentBoard[unitDestionationRow][unitDestionationColumn].unitHp=CurrentBoard[tRow][tColumn].unitHp;
        CurrentBoard[unitDestionationRow][unitDestionationColumn].active=0;
        //Remove unit info from starting tile
        CurrentBoard[tRow][tColumn].player=0;
        CurrentBoard[tRow][tColumn].unitId=0;
        CurrentBoard[tRow][tColumn].unitHp=0;
        CurrentBoard[tRow][tColumn].active=0;
      }

      mapMode = IDLE_MODE;
      //Prepare tiles for battle scene
      Attacker = &CurrentBoard[unitDestionationRow][unitDestionationColumn];
      Defender = &CurrentBoard[targetRow][targetColumn];
      PrepareBattleScene();
      SceneMode=BATTLE_MODE;
    }
  }
}

void attackWithArtillery()
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

    UnitLocation targets[8]= {{0,0,6,false},{0,0,5,false},{0,0,4,false},{0,0,3,false},{0,0,2,false},{0,0,1,false},{0,0,8,false},{0,0,7,false}};

    for(int i=minX;i<maxX;i++) //Register all enemy units in range
    {
      for(int j=minY;j<maxY;j++)
      {
        if(CurrentBoard[i][j].unitId!=0 && CurrentBoard[i][j].player!=CurrentPlayer->id && CurrentBoard[i][j].moveGrid==2)
        {
          for(int slot=0;slot<8;slot++)
          {
            if(CurrentBoard[i][j].unitId==targets[slot].unitId && targets[slot].activated==false)
            {
              targets[slot].row=i;
              targets[slot].column=j;
              targets[slot].activated=true;
            }
          }
        }
      }
    }

    //select and attack target
    for(int slot=0;slot<8;slot++)
    {
      if(targets[slot].activated==true)
      {
        mapMode = IDLE_MODE;
        CurrentBoard[tRow][tColumn].active=0;
        //Prepare tiles for battle scene
        Attacker = &CurrentBoard[tRow][tColumn];
        Defender = &CurrentBoard[targets[slot].row][targets[slot].column];
        PrepareBattleScene();
        SceneMode=BATTLE_MODE;
        break;
      }
    }
  }
}

UnitLocation getAvailableUnit()
{
  UnitLocation selectedUnit ={0,0,0,true};
  bool selected = false;
  for(int phase=currentPhase;phase<3;phase++)
  {
    currentPhase=phase;
    for(int i=0;i<ConsoleUnitsCount;i++)
    {
      if(phase==ARTILLERY_PHASE && (ConsoleUnits[i].unitId==5 || ConsoleUnits[i].unitId==6) && ConsoleUnits[i].activated==false)
      {
        ConsoleUnits[i].activated=true;
        selectedUnit=ConsoleUnits[i];
        selected=true;
        break;
      }
      else if(phase==TANK_PHASE && (ConsoleUnits[i].unitId==1 || ConsoleUnits[i].unitId==2 || ConsoleUnits[i].unitId==3 || ConsoleUnits[i].unitId==4) && ConsoleUnits[i].activated==false)
      {
        ConsoleUnits[i].activated=true;
        selectedUnit=ConsoleUnits[i];
        selected=true;
        break;
      }
      else if(phase==INFANTRY_PHASE && (ConsoleUnits[i].unitId==7 || ConsoleUnits[i].unitId==8) && ConsoleUnits[i].activated==false)
      {
        ConsoleUnits[i].activated=true;
        selectedUnit=ConsoleUnits[i];
        selected=true;
        break;
      }
    }
    
    if(selected==true)
    {
      break;  
    }
  }
  return selectedUnit;
}

void setScreenOnUnit(UnitLocation unitLocation)
{
  int row = unitLocation.row;
  int column = unitLocation.column;

  if(row<=2)
  {
    posY=row*10;
    sRowIdx=0;
  }
  else if(row>2 && row<12)
  {
    sRowIdx=row-2;
    posY = (row-sRowIdx)*10;
  }
  else
  {
    posY=(row-10)*10;
    sRowIdx=10;
  }

  if(column<=3)
  {
    posX=column*10;
    sColIdx=0;
  }
  else if(column>3 && column<11)
  {
    sColIdx=column-3;
    posX=(column-sColIdx)*10;
  }
  else
  {
    posX=(column-8)*10;
    sColIdx=8;
  }
}

void consoleActionFrames()
{
  if(aiFrames==10)
  {
    if(actionPhase==P_SELECTION)
    {
      aiFrames=0;
      bool finished = getNextUnit();
      if(finished==true)
      {
        sRowIdx=0;
        sColIdx=0;
        posX=0;
        posY=0;
        endTurn();
      }
      else
      {
        unitActions();
      }
    }
    else
    {
      aiFrames=0;
      unitActions();
    }
  }
  else
  {
    aiFrames++;
  }
}
