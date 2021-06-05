#define INFANTRY_SELECTION 1
#define MECH_INFANTRY_SELECTION 2
#define HALF_TRUCK_SELECTION 3
#define MEDIUM_TANK_SELECTION 4
#define MOBILE_ARTILLERY_SELECTION 5
#define HEAVY_TANK_SELECTION 6
#define MOBILE_SSM_SELECTION 7
#define TANK_DESTROYER_SELECTION 8
#define BASE_UPGRADE_SELECTION 9

int rowIdx=0;
int colIdx=0;
int selectedAction = INFANTRY_SELECTION;

void BaseScene()
{
  drawBaseScreen(2+rowIdx*10,27+colIdx*40);
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(rowIdx>0)
    {
      rowIdx--;
      setSelectedAction();
    }
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(colIdx==0)
    {
      if(rowIdx<4)
      {
        rowIdx++;
        setSelectedAction();
      }
    }
    else
    {
      if(rowIdx<3)
      {
        rowIdx++;
        setSelectedAction();
      }
    }
  }
  else if(gb.buttons.pressed(BUTTON_RIGHT))
  {
    if(rowIdx<4)
    {
      if(colIdx==0)
      {
        colIdx=1;
        setSelectedAction();
      }
    }
  }
  else if(gb.buttons.pressed(BUTTON_LEFT))
  {
    if(colIdx==1)
    {
      colIdx=0;
      setSelectedAction();
    }
  }
  else if(gb.buttons.pressed(BUTTON_A))
  {
    int price = getUnitPrice();
    if(CurrentPlayer.funds>=price)
    {
      if(selectedAction==BASE_UPGRADE_SELECTION)
      {
        if(CurrentPlayer.baseLevel<8)
        {
          CurrentPlayer.funds-=price;
          CurrentPlayer.baseLevel++;
          if(CurrentPlayer.id==1)
          {
            Player_1.funds-=price;
            Player_1.baseLevel++;
          }
          else
          {
            Player_2.funds-=price;
            Player_2.baseLevel++;
          }
          gb.gui.popup("Base upgraded!",50);
        }
      }
      else
      {
        if(selectedAction<=CurrentPlayer.baseLevel) // Unlocked or not
        {
          CurrentPlayer.funds-=price;
          CurrentBoard[BaseLocation.row][BaseLocation.column].unitId=getUnitId();
          CurrentBoard[BaseLocation.row][BaseLocation.column].player=CurrentPlayer.id;
          CurrentBoard[BaseLocation.row][BaseLocation.column].unitHp=10;
          BaseLocation.row = 0;
          BaseLocation.column = 0;
          SceneMode=MAP_MODE;
        }
      }
    }
  }
  else if(gb.buttons.pressed(BUTTON_B))
  {
    SceneMode=MAP_MODE;
    BaseLocation.row = 0;
    BaseLocation.column = 0;
  }
}

int getUnitId()
{
  int result=0;
  switch(selectedAction)
  {
    case INFANTRY_SELECTION:
      result = 7; break;
    case MECH_INFANTRY_SELECTION:
      result = 8; break;
    case HALF_TRUCK_SELECTION:
      result = 1; break;
    case MEDIUM_TANK_SELECTION:
      result = 2; break;
    case MOBILE_ARTILLERY_SELECTION:
      result = 5; break;
    case HEAVY_TANK_SELECTION:
      result = 3; break;
    case MOBILE_SSM_SELECTION:
      result = 6; break;
    case TANK_DESTROYER_SELECTION:
      result = 4; break;
  }

  return result;
}

int getUnitPrice()
{
  int result=0;
  switch(selectedAction)
  {
    case INFANTRY_SELECTION:
      result = 100; break;
    case MECH_INFANTRY_SELECTION:
      result = 200; break;
    case HALF_TRUCK_SELECTION:
      result = 300; break;
    case MEDIUM_TANK_SELECTION:
      result = 500; break;
    case MOBILE_ARTILLERY_SELECTION:
      result = 450; break;
    case HEAVY_TANK_SELECTION:
      result = 800; break;
    case MOBILE_SSM_SELECTION:
      result = 750; break;
    case TANK_DESTROYER_SELECTION:
      result = 900; break;
    case BASE_UPGRADE_SELECTION:
      result = 50 + (CurrentPlayer.baseLevel * 100); break;
  }

  return result;
}

void setSelectedAction()
{
  if(colIdx==0)
  {
    if(rowIdx==0)
    {
      selectedAction = INFANTRY_SELECTION;
    }
    else if(rowIdx==1)
    {
      selectedAction = MECH_INFANTRY_SELECTION;
    }
    else if(rowIdx==2)
    {
      selectedAction = HALF_TRUCK_SELECTION;
    }
    else if(rowIdx==3)
    {
      selectedAction = MEDIUM_TANK_SELECTION;
    }
    else
      selectedAction = BASE_UPGRADE_SELECTION;
  }
  else
  {
    if(rowIdx==0)
    {
      selectedAction = MOBILE_ARTILLERY_SELECTION;
    }
    else if(rowIdx==1)
    {
      selectedAction = HEAVY_TANK_SELECTION;
    }
    else if(rowIdx==2)
    {
      selectedAction = MOBILE_SSM_SELECTION;
    }
    else
      selectedAction = TANK_DESTROYER_SELECTION;
  }
}
