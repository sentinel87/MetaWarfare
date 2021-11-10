
struct Point
{
  unsigned int row;
  unsigned int column;
  unsigned int unitId;
};

Point ConsoleUnits[25] {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
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
        ConsoleUnits[idx].column=j;
        ConsoleUnits[idx].row=i;
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
    gb.gui.popup("Unit turn",20);
    currentUnit++;
    
    //TODO: Unit actions
    
    return false;
  }
}

void consoleActionFrames()
{
  if(aiFrames==25)
  {
    aiFrames=0;
    bool finished = getNextUnit();
    if(finished==true)
    {
      endTurn();
    }
  }
  else
  {
    aiFrames++;
  }
}
