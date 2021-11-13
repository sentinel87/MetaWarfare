#define MENU_CAMPAIGN 1
#define MENU_MULTIPLAYER 2
#define MENU_LOAD 3
#define MENU_HIGH_SCORE 4
#define MENU_TUTORIAL 5

int mmPosX=57;
int mmPosY=28;

int mmSelectedScene=MENU_TUTORIAL;
int smSelectedScene=1;
int tmSelectedScene=1;

void MainMenuScene()
{
  drawMainMenu(mmPosX,mmPosY);
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(mmSelectedScene==MENU_TUTORIAL)
    {
      mmPosY=56;
      mmSelectedScene=MENU_HIGH_SCORE;
    }
    else if(mmSelectedScene==MENU_CAMPAIGN)
    {
      mmPosY=28;
      mmSelectedScene=MENU_TUTORIAL;
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
      mmPosY=35;
      mmSelectedScene=MENU_CAMPAIGN;
    }
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(mmSelectedScene==MENU_TUTORIAL)
    {
      mmPosY=35;
      mmSelectedScene=MENU_CAMPAIGN;
    }
    else if(mmSelectedScene==MENU_CAMPAIGN)
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
      mmPosY=28;
      mmSelectedScene=MENU_TUTORIAL;
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
        posX = 0;
        posY = 0;
        sRowIdx = 0;
        sColIdx = 0;
        Tutorial=-1;
        gb.gui.popup("GAME LOADED!",50);
      }
    }
    else if(mmSelectedScene==MENU_HIGH_SCORE)
    {
      SceneMode = SCORES_MODE;
    }
    else if(mmSelectedScene==MENU_TUTORIAL)
    {
      SceneMode = TUTORIAL_SCENARIO_MODE;
    }
    else if(mmSelectedScene==MENU_CAMPAIGN)
    {
      //MapId=1;
      //Tutorial=-1;
      //GameMode=CAPTURE_MODE;
      //memcpy(CurrentBoard, CampaignBoard3, sizeof(CurrentBoard));
      //PrepareMap();
      //SceneMode = TUTORIAL_MODE;
      //mapMode = IDLE_MODE;

      //MapId=1;
      Tutorial=-1;
      GameMode=DEATHMATCH_MODE;
      memcpy(CurrentBoard, CampaignBoard2, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
    }
  }
}

void MultiplayerScenarioScene()
{
  drawScenarioMenu(65,1+(smSelectedScene-1)*6);
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(smSelectedScene>1)
    {
      smSelectedScene--;
    }
    else
    {
      smSelectedScene=8;
    }
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(smSelectedScene<8)
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
      Tutorial=-1;
      GameMode=CONQUEST_MODE;
      memcpy(CurrentBoard, Board1, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
    }
    else if(smSelectedScene==2)
    {
      MapId=2;
      Tutorial=-1;
      GameMode=CAPTURE_MODE;
      memcpy(CurrentBoard, Board2, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
    }
    else if(smSelectedScene==3)
    {
      MapId=3;
      Tutorial=-1;
      GameMode=CONQUEST_MODE;
      memcpy(CurrentBoard, Board3, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
    }
    else if(smSelectedScene==4)
    {
      MapId=4;
      Tutorial=-1;
      GameMode=CAPTURE_MODE;
      memcpy(CurrentBoard, Board4, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
    }
    else if(smSelectedScene==5)
    {
      MapId=5;
      Tutorial=-1;
      GameMode=CONQUEST_MODE;
      memcpy(CurrentBoard, Board5, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
    }
    else if(smSelectedScene==6)
    {
      MapId=6;
      Tutorial=-1;
      GameMode=CAPTURE_MODE;
      memcpy(CurrentBoard, Board6, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
    }
    else if(smSelectedScene==7)
    {
      MapId=7;
      Tutorial=-1;
      GameMode=CONQUEST_MODE;
      memcpy(CurrentBoard, Board7, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
    }
    else if(smSelectedScene==8)
    {
      SceneMode=MENU_MODE;
      smSelectedScene=1;
    }
  }
}

void TutorialScenarioScene()
{
  drawTutorialMenu(65,1+(tmSelectedScene-1)*6);
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(tmSelectedScene>1)
    {
      tmSelectedScene--;
    }
    else
    {
      tmSelectedScene=3;
    }
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(tmSelectedScene<3)
    {
      tmSelectedScene++;
    }
    else
    {
      tmSelectedScene=1;
    }
  }
  else if(gb.buttons.pressed(BUTTON_A))
  {
    if(tmSelectedScene==1)
    {
      Tutorial=0;
      GameMode=CONQUEST_MODE;
      memcpy(CurrentBoard, TutorialBoard1, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      tmSelectedScene=1;
    }
    else if(tmSelectedScene==2)
    {
      Tutorial=1;
      GameMode=CAPTURE_MODE;
      memcpy(CurrentBoard, TutorialBoard2, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      tmSelectedScene=1;
    }
    else if(tmSelectedScene==3)
    {
      SceneMode=MENU_MODE;
      tmSelectedScene=1;
    }
  }
}

void PrepareMap()
{
  TurnCount=0;
  BaseLocation = &None;
  Attacker = &None;
  Defender = &None;
  posX = 0;
  posY = 0;
  sRowIdx = 0;
  sColIdx = 0;
  Player_1.baseLevel = 1;
  Player_1.funds = 0;
  Player_1.totalUnits = 0;
  Player_1.points = 0;
  Player_2.baseLevel = 1;
  Player_2.funds = 0;
  Player_2.totalUnits = 0;
  Player_2.points = 0;
  CurrentPlayer=&Player_1;
  //countPlayerStats();
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

void TutorialTip()
{
  drawTutorialScreen();
  if(gb.buttons.pressed(BUTTON_A))
  {
    SceneMode=MAP_MODE;
    countPlayerStats();
    gb.lights.fill(RED);
    gb.gui.popup("PLAYER 1 TURN",50);
  }
}

void HighScoreScene()
{
  drawHighScoreScreen();
  if(gb.buttons.pressed(BUTTON_A))
  {
    SceneMode=MENU_MODE;
  }
}
