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
  drawBaseScreen();
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

