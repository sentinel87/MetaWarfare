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
      SetMap(10,CAPTURE_FLAG_MODE,CampaignBoard1,true);
    }
    else if(smSelectedScene==2 && CampaignProgress>=1)
    {
      SetMap(11,DEATHMATCH_MODE,CampaignBoard2,true);
    }
    else if(smSelectedScene==3 && CampaignProgress>=2)
    {
      SetMap(12,CAPTURE_MODE,CampaignBoard3,true);
    }
    else if(smSelectedScene==4 && CampaignProgress>=3)
    {
      SetMap(13,CONQUEST_MODE,CampaignBoard4,true);
    }
    else if(smSelectedScene==5 && CampaignProgress>=4)
    {
      SetMap(14,DEATHMATCH_MODE,CampaignBoard5,true);
    }
    else if(smSelectedScene==6 && CampaignProgress>=5)
    {
      SetMap(15,CAPTURE_MODE,CampaignBoard6,true);
    }
    else if(smSelectedScene==7 && CampaignProgress>=6)
    {
      SetMap(16,CAPTURE_FLAG_MODE,CampaignBoard7,true);
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
      smSelectedScene=4;
    }
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(smSelectedScene<4)
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
    switch(smSelectedScene)
    {
      case 1:
        SetMap(17,CAPTURE_FLAG_MODE,SkirmishBoard1,true); break;
      case 2:
        SetMap(18,CONQUEST_MODE,SkirmishBoard2,true); break;
      case 3:
        SetMap(19,DEATHMATCH_MODE,SkirmishBoard3,true); break;
      case 4:
        SceneMode=MENU_MODE; smSelectedScene=1; break;
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
    switch(smSelectedScene)
    {
      case 1:
        SetMap(3,CONQUEST_MODE,Board1,false); break;
      case 2:
        SetMap(4,CAPTURE_MODE,Board2,false); break;
      case 3:
        SetMap(5,CONQUEST_MODE,Board3,false); break;
      case 4:
        SetMap(6,CAPTURE_MODE,Board4,false); break;
      case 5:
        SetMap(7,CONQUEST_MODE,Board5,false); break;
      case 6:
        SetMap(8,CAPTURE_MODE,Board6,false); break;
      case 7:
        SetMap(9,CONQUEST_MODE,Board7,false); break;
      case 8:
        SceneMode=MENU_MODE; smSelectedScene=1; break;
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
      checkProgress();
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

void checkProgress()
{
  switch(MapId)
  {
    case 10:
      saveProgress(1); break;
    case 11:
      saveProgress(2); break;
    case 12:
      saveProgress(3); break;
    case 13:
      saveProgress(4); break;
    case 14:
      saveProgress(5); break;
    case 15:
      saveProgress(6); break;
    case 16:
      saveProgress(7); break;
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
