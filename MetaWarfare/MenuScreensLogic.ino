#define MENU_CAMPAIGN 1
#define MENU_MULTIPLAYER 2
#define MENU_LOAD 3
#define MENU_HIGH_SCORE 4
#define MENU_TUTORIAL 5
#define MENU_SKIRMISH 6

int mmPosX=57;
int mmPosY=21;

int mmSelectedScene=MENU_TUTORIAL;
int smSelectedScene=1;

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
      mmPosY=21;
      mmSelectedScene=MENU_TUTORIAL;
    }
    else if(mmSelectedScene==MENU_SKIRMISH)
    {
      mmPosY=28;
      mmSelectedScene=MENU_CAMPAIGN;
    }
    else if(mmSelectedScene==MENU_MULTIPLAYER)
    {
      mmPosY=35;
      mmSelectedScene=MENU_SKIRMISH;
    }
    else if(mmSelectedScene==MENU_LOAD)
    {
      mmPosY=42;
      mmSelectedScene=MENU_MULTIPLAYER;
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
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(mmSelectedScene==MENU_TUTORIAL)
    {
      mmPosY=28;
      mmSelectedScene=MENU_CAMPAIGN;
    }
    else if(mmSelectedScene==MENU_CAMPAIGN)
    {
      mmPosY=35;
      mmSelectedScene=MENU_SKIRMISH;
    }
    else if(mmSelectedScene==MENU_SKIRMISH)
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
      mmPosY=21;
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
        Winner = 0;
        posX = 0;
        posY = 0;
        sRowIdx = 0;
        sColIdx = 0;
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
      SceneMode = CAMPAIGN_SCENARIO_MODE;
    }
    else if(mmSelectedScene==MENU_SKIRMISH)
    {
      SceneMode = SKIRMISH_SCENARIO_MODE;
    }
  }
}

void CampaignScenarioScene()
{
  drawCampaignScenarioMenu(65,1+(smSelectedScene-1)*6);
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
      MapId=10;
      GameMode=CAPTURE_FLAG_MODE;
      memcpy(CurrentBoard, CampaignBoard1, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=true;
    }
    else if(smSelectedScene==2)
    {
      MapId=11;
      GameMode=DEATHMATCH_MODE;
      memcpy(CurrentBoard, CampaignBoard2, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=true;
    }
    else if(smSelectedScene==3)
    {
      MapId=12;
      GameMode=CAPTURE_MODE;
      memcpy(CurrentBoard, CampaignBoard3, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=true;
    }
    else if(smSelectedScene==4)
    {
      MapId=13;
      GameMode=CONQUEST_MODE;
      memcpy(CurrentBoard, CampaignBoard4, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=true;
    }
    else if(smSelectedScene==5)
    {
      MapId=14;
      GameMode=DEATHMATCH_MODE;
      memcpy(CurrentBoard, CampaignBoard5, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=true;
    }
    else if(smSelectedScene==6)
    {
      MapId=15;
      GameMode=CAPTURE_MODE;
      memcpy(CurrentBoard, CampaignBoard6, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=true;
    }
    else if(smSelectedScene==7)
    {
      MapId=16;
      GameMode=CAPTURE_FLAG_MODE;
      memcpy(CurrentBoard, CampaignBoard7, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=true;
    }
    else if(smSelectedScene==8)
    {
      SceneMode=MENU_MODE;
      smSelectedScene=1;
    }
  }
}

void SkirmishScenarioScene()
{
  drawSkirmishScenarioMenu(65,1+(smSelectedScene-1)*6);
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(smSelectedScene>1)
    {
      smSelectedScene--;
    }
    else
    {
      smSelectedScene=2;
    }
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(smSelectedScene<2)
    {
      smSelectedScene++;
    }
    else
    {
      smSelectedScene=1;
    }
  }
  if(gb.buttons.pressed(BUTTON_A))
  {
    if(smSelectedScene==1)
    {
      MapId=17;
      GameMode=CAPTURE_FLAG_MODE;
      memcpy(CurrentBoard, SkirmishBoard1, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=true;
    }
    else if(smSelectedScene==2)
    {
      SceneMode=MENU_MODE;
      smSelectedScene=1;
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
      MapId=3;
      GameMode=CONQUEST_MODE;
      memcpy(CurrentBoard, Board1, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=false;
    }
    else if(smSelectedScene==2)
    {
      MapId=4;
      GameMode=CAPTURE_MODE;
      memcpy(CurrentBoard, Board2, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=false;
    }
    else if(smSelectedScene==3)
    {
      MapId=5;
      GameMode=CONQUEST_MODE;
      memcpy(CurrentBoard, Board3, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=false;
    }
    else if(smSelectedScene==4)
    {
      MapId=6;
      GameMode=CAPTURE_MODE;
      memcpy(CurrentBoard, Board4, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=false;
    }
    else if(smSelectedScene==5)
    {
      MapId=7;
      GameMode=CONQUEST_MODE;
      memcpy(CurrentBoard, Board5, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=false;
    }
    else if(smSelectedScene==6)
    {
      MapId=8;
      GameMode=CAPTURE_MODE;
      memcpy(CurrentBoard, Board6, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=false;
    }
    else if(smSelectedScene==7)
    {
      MapId=9;
      GameMode=CONQUEST_MODE;
      memcpy(CurrentBoard, Board7, sizeof(CurrentBoard));
      PrepareMap();
      SceneMode = TUTORIAL_MODE;
      mapMode = IDLE_MODE;
      smSelectedScene=1;
      IsConsoleOpponent=false;
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
  drawTutorialMenu(65,1+(smSelectedScene-1)*6);
  if(gb.buttons.pressed(BUTTON_UP))
  {
    if(smSelectedScene>1)
    {
      smSelectedScene--;
    }
    else
    {
      smSelectedScene=3;
    }
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(smSelectedScene<3)
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
    switch(smSelectedScene)
    {
      case 1:
        SetMap(1,CONQUEST_MODE,TutorialBoard1,true); break;
      case 2:
        SetMap(2,CAPTURE_MODE,TutorialBoard2,true); break;
      case 3:
        SceneMode=MENU_MODE; smSelectedScene=1; break;
    }
  }
}

void SetMap(int mapId,int gameMode,const GameTileStruct board[][16], bool isConsoleOpponent)
{
  MapId=mapId;
  GameMode=gameMode;
  memcpy(CurrentBoard, board, sizeof(CurrentBoard));
  PrepareMap();
  SceneMode = TUTORIAL_MODE;
  mapMode = IDLE_MODE;
  smSelectedScene=1;
  Winner=0;
  IsConsoleOpponent=isConsoleOpponent;
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
}

void EndGameScene()
{
  drawEndGameScreen();
  if(gb.buttons.pressed(BUTTON_B))
  {
    bool HighScore = false;
    if(IsConsoleOpponent==true && Winner==1)
    {
      HighScore=compareAndUpdateScore(Player_1.points);
    }
    else if(IsConsoleOpponent==false)
    {
      HighScore=compareAndUpdateScore(CurrentPlayer->points);
    }

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
