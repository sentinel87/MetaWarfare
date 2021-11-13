#include <Gamebuino-Meta.h>
#include "assets/maps.h"
#include "assets/sprites.h"

#define MENU_MODE 1
#define MAP_MODE 2
#define BATTLE_MODE 3
#define BASE_MODE 4
#define MULTIPLAYER_SCENARIO_MODE 5
#define CAMPAIGN_SCENARIO_MODE 6
#define OUTCOME_MODE 7
#define SCORES_MODE 8
#define TUTORIAL_MODE 9
#define TUTORIAL_SCENARIO_MODE 10

#define CONQUEST_MODE 1
#define CAPTURE_MODE 2
#define DEATHMATCH_MODE 3
#define CAPTURE_FLAG_MODE 4

const Gamebuino_Meta::Sound_FX cannonExplosionSound[] = {
    {Gamebuino_Meta::Sound_FX_Wave::NOISE,0,60,30,40,10,15},
};

const Gamebuino_Meta::Sound_FX artilleryExplosionSound[] = {
    {Gamebuino_Meta::Sound_FX_Wave::NOISE,0,60,20,20,70,20},
};

const Gamebuino_Meta::Sound_FX gunFireSound[] = {
    {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,80,-3,20,20,4},
    {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,80,-3,20,20,4},
    {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,80,-3,20,20,4},
    {Gamebuino_Meta::Sound_FX_Wave::NOISE,0,80,-3,20,20,4}
};

const Gamebuino_Meta::Sound_FX gunExplosionSound[] = {
    {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,57,3,41,100,4},
    {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,57,3,41,100,4},
    {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,57,3,41,100,4},
    {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,57,3,41,100,4},
};

const Gamebuino_Meta::Sound_FX cannonFireSound[] = {
    {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,40,55,25,100,15},
    {Gamebuino_Meta::Sound_FX_Wave::NOISE,0,40,55,25,100,15}
};

const Gamebuino_Meta::Sound_FX artilleryFireSound[] = {
    {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,40,2,20,35,15},
    {Gamebuino_Meta::Sound_FX_Wave::NOISE,0,40,2,20,35,15}
};

const Gamebuino_Meta::Sound_FX captureSound[] = {
    {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,70,-2,60,50,10},
};

const Gamebuino_Meta::Sound_FX selectSound[] = {
    {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,50,3,30,50,3},
};

struct Unit
{
  unsigned int unitId: 5;
  unsigned int movement: 3;
  unsigned int crossMove: 1;
  unsigned int canCrossMountains: 1;
  unsigned int attackRange: 3;
  unsigned int reserve: 19;
};

struct Player
{
  unsigned int id;
  unsigned int baseLevel;
  int funds; 
  unsigned int totalUnits;
  unsigned int points;
};

const Unit NONE = {0,0,0,0,0};
const Unit HALF_TRUCK = {1,4,0,0,1};
const Unit MEDIUM_TANK = {2,3,0,0,1};
const Unit HEAVY_TANK = {3,3,0,0,1};
const Unit TANK_DESTROYER = {4,3,0,0,1};
const Unit MOBILE_ARTILLERY = {5,4,1,0,2};
const Unit MOBILE_SSM = {6,3,1,0,3};
const Unit INFANTRY = {7,2,0,1,1};
const Unit MECH_INFANTRY = {8,1,0,1,1};

GameTileStruct CurrentBoard[16][16];

bool menuMode=false;
bool SaveExist=false;

int Tutorial=-1;
int TurnCount=0;

int SceneMode=MENU_MODE;
int MapId=0;
int GameMode=CONQUEST_MODE;

int ScoreBoard[]={0,0,0,0,0};
Player Player_1={1,1,0,0,0};
Player Player_2={2,1,0,0,0};

GameTileStruct None={0,0,0,0,0,0,0,0,0};
GameTileStruct Att={28,1,1,10,0,0,0,0,0};
GameTileStruct Def={29,2,2,10,0,0,0,0,0};
GameTileStruct* Attacker = &Att;
GameTileStruct* Defender = &Def;
GameTileStruct* BaseLocation = &None;

Player* CurrentPlayer = &Player_1;

const SaveDefault savefileDefaults[] = {
  {0, SAVETYPE_BLOB,{.ptr="00000000 "},9}, //Map config
  {1, SAVETYPE_BLOB,{.ptr="00000000000000000000000000 "},27}, //Players stats
  {2, SAVETYPE_BLOB,{.ptr="00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 "}, 513}, //Map parms (Unit Id)
  {3, SAVETYPE_BLOB,{.ptr="00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 "}, 513}, //Map parms (Unit Hp)
  {4, SAVETYPE_BLOB,{.ptr="0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 "},257}, //Map parms (Unit ownership)
  {5, SAVETYPE_BLOB,{.ptr="0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 "},257}, //Map parms (Unit status)
  {6, SAVETYPE_BLOB,{.ptr="0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 "},257}, //Map parms (Building ownership)
  {7, SAVETYPE_INT,0,0 }, //Check if save exist
  {9, SAVETYPE_INT,0,0 },
  {10, SAVETYPE_INT,0,0 },
  {11, SAVETYPE_INT,0,0 },
  {12, SAVETYPE_INT,0,0 },
  {13, SAVETYPE_INT,0,0 }
};

int posX = 0;
int posY = 0;

int sRowIdx = 0;
int sColIdx = 0;

struct UnitLocation
{
  unsigned int row;
  unsigned int column;
  unsigned int unitId;
  bool activated;
};

void setup() {
  gb.begin();
  gb.save.config(savefileDefaults);
  ScoreBoard[0]=gb.save.get(9);
  ScoreBoard[1]=gb.save.get(10);
  ScoreBoard[2]=gb.save.get(11);
  ScoreBoard[3]=gb.save.get(12);
  ScoreBoard[4]=gb.save.get(13);
  int check=gb.save.get(7);
  if(check==1)
  {
    SaveExist=true;
  }
}    


void loop() {
  while(!gb.update());
  gb.display.clear();
  gb.lights.clear();
  if(SceneMode==MENU_MODE)
  {
    MainMenuScene();
  }
  else if(SceneMode==MULTIPLAYER_SCENARIO_MODE)
  {
    MultiplayerScenarioScene();
  }
  else if(SceneMode==MAP_MODE)
  {
    if(menuMode==true)
    {
      memcpy(CurrentBoard, Board1, sizeof(CurrentBoard));
      menuMode=false;
    }
    
    BattleMap();
  }
  else if(SceneMode==BATTLE_MODE)
  {
    BattleScene();
  }
  else if(SceneMode==OUTCOME_MODE)
  {
    EndGameScene();
  }
  else if(SceneMode==SCORES_MODE)
  {
    HighScoreScene();
  }
  else if(SceneMode==TUTORIAL_MODE)
  {
    TutorialTip();
  }
  else if(SceneMode==TUTORIAL_SCENARIO_MODE)
  {
    TutorialScenarioScene();
  }
  else //Base mode
  {
    BaseScene();
  }

  //debug();
}

bool compareAndUpdateScore(int score)
{
  bool isScoreQualified=false;
  int temp=0;
  int temp2=0;
  int index=0;

  for(int i=0;i<5;i++)
  {
    if(score>ScoreBoard[i])
    {
       temp=ScoreBoard[i];
       ScoreBoard[i]=score;
       index=i;
       isScoreQualified=true;
       break;
    } 
  }

  if(!isScoreQualified)
  {
    return false;
  }

  for(int i=index+1;i<5;i++)
  {
    temp2=ScoreBoard[i];
    ScoreBoard[i]=temp;
    temp=temp2;
  }
  return isScoreQualified;
}
