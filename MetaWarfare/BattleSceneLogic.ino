#define GRASSLAND 1
#define ROAD 2
#define FOREST 3

#define ARTILLERY_EFFECT 1
#define TANK_GUN_EFFECT 2
#define AUTOMATIC_GUN_EFFECT 3

#define SCENE_STATE_IDLE 1
#define SCENE_STATE_ATTACK 2

int LeftSceneTheme=FOREST;
int RightSceneTheme=FOREST;

int AttackerAttackType=ARTILLERY_EFFECT;
int DefenderAttackType=ARTILLERY_EFFECT;

int SceneState=SCENE_STATE_IDLE;

int frames=0;

void BattleScene()
{
  //animationFrames();
  drawBattleScene(1,2,2,2);
}

void animationFrames()
{
  if(SceneState==SCENE_STATE_IDLE)
  {
    if(frames==78)
    {
      frames=1;
      SceneState=SCENE_STATE_ATTACK;
    }
    else
    {
      frames++;
    }
  }
  else
  {
    if(frames==16)
    {
      frames=1;
      SceneState=SCENE_STATE_IDLE;
    }
    else
    {
      frames++;
    }
  }
}

