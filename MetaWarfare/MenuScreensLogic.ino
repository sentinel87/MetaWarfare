#define MENU_CAMPAIGN 1
#define MENU_MULTIPLAYER 2
#define MENU_LOAD 3
#define MENU_HIGH_SCORE 4

int mmPosX=57;
int mmPosY=42;

int mmSelectedScene=MENU_MULTIPLAYER;
int smSelectedScene=1;

void MainMenuScene()
{
  drawMainMenu(mmPosX,mmPosY);
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(mmSelectedScene==MENU_CAMPAIGN)
    {
      mmPosY=56;
      mmSelectedScene=MENU_HIGH_SCORE;
    }
    else if(mmSelectedScene==MENU_HIGH_SCORE)
    {
      if(SaveExist==true)
      {
        mmPosY=49;
        mmSelectedScene=MENU_LOAD;
      }
      else
      {
        mmPosY=42;
        mmSelectedScene=MENU_MULTIPLAYER;
      }
    }
    else if(mmSelectedScene==MENU_LOAD)
    {
      mmPosY=42;
      mmSelectedScene=MENU_MULTIPLAYER;
    }
    else
    {
      //mmPosY=35;
      //mmSelectedScene=MENU_CAMPAIGN;
      mmPosY=56;
      mmSelectedScene=MENU_HIGH_SCORE;
    }
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(mmSelectedScene==MENU_CAMPAIGN)
    {
      mmPosY=42;
      mmSelectedScene=MENU_MULTIPLAYER;
    }
    else if(mmSelectedScene==MENU_MULTIPLAYER)
    {
      if(SaveExist==true)
      {
        mmPosY=49;
        mmSelectedScene=MENU_LOAD;
      }
      else
      {
        mmPosY=56;
        mmSelectedScene=MENU_HIGH_SCORE;
      }
    }
    else if(mmSelectedScene==MENU_LOAD)
    {
      mmPosY=56;
      mmSelectedScene=MENU_HIGH_SCORE;
    }
    else
    {
      //mmPosY=35;
      //mmSelectedScene=MENU_CAMPAIGN;
      mmPosY=42;
      mmSelectedScene=MENU_MULTIPLAYER;
    }
  }
  else if(gb.buttons.pressed(BUTTON_A))
  {
    if(mmSelectedScene==MENU_MULTIPLAYER)
    {
      SceneMode=MULTIPLAYER_SCENARIO_MODE;
      mmSelectedScene=MENU_MULTIPLAYER;
      mmPosY=42;
      mmPosX=57;
    }
    else if(mmSelectedScene==MENU_LOAD)
    {
      if(LoadGame()==true)
      {
        SceneMode = MAP_MODE;
        mapMode = IDLE_MODE;
        gb.gui.popup("GAME LOADED!",50);
      }
    }
    else if(mmSelectedScene==MENU_HIGH_SCORE)
    {
      SceneMode = SCORES_MODE;
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
      MapId=1;
      BaseLocation = &None;
      Attacker = &None;
      Defender = &None;
      memcpy(CurrentBoard, Board1, sizeof(CurrentBoard));
      Player_1.baseLevel = 1;
      Player_1.funds = 0;
      Player_1.totalUnits = 0;
      Player_2.baseLevel = 1;
      Player_2.funds = 0;
      Player_2.totalUnits = 0;
      CurrentPlayer=&Player_1;
      countPlayerStats();
      SceneMode = MAP_MODE;
      mapMode = IDLE_MODE;
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

void EndGameScene()
{
  drawEndGameScreen();
  if(gb.buttons.pressed(BUTTON_B))
  {
    bool HighScore=compareAndUpdateScore(CurrentPlayer->points);
    if(HighScore)
    {
      gb.save.set(9,ScoreBoard[0]);
      gb.save.set(10,ScoreBoard[1]);
      gb.save.set(11,ScoreBoard[2]);
      gb.save.set(12,ScoreBoard[3]);
      gb.save.set(13,ScoreBoard[4]);
    }
    SceneMode=MENU_MODE;
  }
}

void HighScoreScene()
{
  drawHighScoreScreen();
  if(gb.buttons.pressed(BUTTON_B))
  {
    SceneMode=MENU_MODE;
  }
}
