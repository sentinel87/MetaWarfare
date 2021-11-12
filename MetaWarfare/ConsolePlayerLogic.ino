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
    else
    {
      clearGrid();
      actionPhase=P_SELECTION;
    }
  }
  else
  {
    actionPhase=P_SELECTION;
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
  if(aiFrames==35)
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
