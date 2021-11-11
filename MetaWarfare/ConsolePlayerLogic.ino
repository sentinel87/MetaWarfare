UnitLocation ConsoleUnits[25] {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
int ConsoleUnitsCount=0;
int aiFrames=0;
int currentUnit=0;

void prepareConsoleLogic()
{
  currentUnit=0;
  ConsoleUnitsCount=0;
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
  if(currentUnit>=ConsoleUnitsCount)
    return true;
  else
  {
    //TODO: Unit actions
    
    setScreenOnUnit(ConsoleUnits[currentUnit]);
    currentUnit++;
    
    return false;
  }
}

void setScreenOnUnit(UnitLocation unitLocation)
{
  int row = unitLocation.row;
  int column = unitLocation.column;

  if(row<=2)
  {
    sRowIdx=0;
  }
  else if(row>2 && row<12)
  {
    sRowIdx=row-2;
  }
  else
  {
    sRowIdx=10;
  }

  if(column<=3)
  {
    sColIdx=0;
  }
  else if(column>3 && column<11)
  {
    sColIdx=column-3;
  }
  else
  {
    sColIdx=8;
  }
}

void consoleActionFrames()
{
  if(aiFrames==35)
  {
    aiFrames=0;
    bool finished = getNextUnit();
    if(finished==true)
    {
      sRowIdx=0;
      sColIdx=0;
      endTurn();
    }
  }
  else
  {
    aiFrames++;
  }
}
