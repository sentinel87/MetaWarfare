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

int AttackerAttackType=TANK_GUN_EFFECT;
int DefenderAttackType=TANK_GUN_EFFECT;

int SceneState=SCENE_STATE_IDLE;

int frames=0;

void BattleScene()
{
  animationFrames();
  drawBattleScene(1,5,2,5);
}

void animationFrames()
{
  if(SceneState==SCENE_STATE_IDLE)
  {
    if(frames==80)
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
    if(frames==20)
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

