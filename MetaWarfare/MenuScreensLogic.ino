#define MENU_CAMPAIGN 1
#define MENU_MULTIPLAYER 2
#define MENU_HIGH_SCORE 3

int mmPosX=57;
int mmPosY=30;

int mmSelectedScene=MENU_CAMPAIGN;
int smSelectedScene=1;

void MainMenuScene()
{
  drawMainMenu(mmPosX,mmPosY);
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(mmSelectedScene==MENU_CAMPAIGN)
    {
      mmPosY=50;
      mmSelectedScene=MENU_HIGH_SCORE;
    }
    else if(mmSelectedScene==MENU_HIGH_SCORE)
    {
      mmPosY=40;
      mmSelectedScene=MENU_MULTIPLAYER;
    }
    else
    {
      mmPosY=30;
      mmSelectedScene=MENU_CAMPAIGN;
    }
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(mmSelectedScene==MENU_CAMPAIGN)
    {
      mmPosY=40;
      mmSelectedScene=MENU_MULTIPLAYER;
    }
    else if(mmSelectedScene==MENU_MULTIPLAYER)
    {
      mmPosY=50;
      mmSelectedScene=MENU_HIGH_SCORE;
    }
    else
    {
      mmPosY=30;
      mmSelectedScene=MENU_CAMPAIGN;
    }
  }
  else if(gb.buttons.pressed(BUTTON_A))
  {
    if(mmSelectedScene==MENU_MULTIPLAYER)
    {
      SceneMode=MULTIPLAYER_SCENARIO_MODE;
      mmSelectedScene=MENU_CAMPAIGN;
      mmPosX=57;
      mmPosY=30;
    }
  }
}

void MultiplayerScenarioScene()
{
  drawScenarioMenu(65,1+(smSelectedScene-1)*10);
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(smSelectedScene>0)
    {
      smSelectedScene--;
    }
    else
    {
      smSelectedScene=6;
    }
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(smSelectedScene<6)
    {
      smSelectedScene++;
    }
    else
    {
      smSelectedScene=1;
    }
  }
  else if(gb.buttons.pressed(BUTTON_A))
  {
    if(smSelectedScene==1)
    {
      memcpy(CurrentBoard, Board1, sizeof(CurrentBoard));
      SceneMode=MAP_MODE;
    }
    else if(smSelectedScene==6)
    {
      SceneMode=MENU_MODE;
      smSelectedScene=1;
    }
  }
}

void CampaignScenarioScene()
{
  
}
