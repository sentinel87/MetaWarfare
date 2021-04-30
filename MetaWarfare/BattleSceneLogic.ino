#define GRASSLAND 1
#define ROAD 2
#define FOREST 3

#define ARTILLERY_EFFECT 1
#define TANK_GUN_EFFECT 2
#define AUTOMATIC_GUN_EFFECT 3

#define SCENE_STATE_IDLE 1
#define SCENE_STATE_ATTACK 2
#define SCENE_STATE_DEMOLITION 3
#define SCENE_STATE_SUMMARY 4

int LeftSceneTheme=FOREST;
int RightSceneTheme=FOREST;

GameTileStruct Attacker={1,1,2,10,0,0};
int AttackerAttackType=TANK_GUN_EFFECT;
GameTileStruct Defender={1,2,2,10,0,0};
int DefenderAttackType=TANK_GUN_EFFECT;

int SceneState=SCENE_STATE_IDLE;
int frames=0;

int AttackerUnitHealth=0;
int DefenderUnitHealth=0;
int ReducedAttackerHealth=0;
int ReducedDefenderHealth=0;

bool debugRefresh=true;

void PrepareBattleScene()
{
  AttackerUnitHealth=Attacker.unitHp;
  DefenderUnitHealth=Defender.unitHp;
  SetAttackType(true,Attacker.unitId);
  SetTerrainType(true,Attacker.terrainTexture);
  SetAttackType(false,Defender.unitId);
  SetTerrainType(false,Defender.terrainTexture);
  CalculateBattleResult();
}

void SetAttackType(bool attacker,int unitId)
{
  int result=AUTOMATIC_GUN_EFFECT;
  
  switch(unitId)
  {
    case 1:
    case 7:
      result=AUTOMATIC_GUN_EFFECT; break;
    case 5:
    case 6:
      result=ARTILLERY_EFFECT; break;
    default:
      result=TANK_GUN_EFFECT; break;
  }

  if(attacker==true)
  {
    AttackerAttackType=result;
  }
  else
  {
    DefenderAttackType=result;
  }
}

void SetTerrainType(bool attacker,int terrain)
{
  int result=GRASSLAND;
  switch(terrain)
  {
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      result=ROAD; break;
    case 10:
      result=FOREST; break;
    default:
      result=GRASSLAND; break;
  }

  if(attacker==true)
  {
    LeftSceneTheme=result;
  }
  else
  {
    RightSceneTheme=result;
  }
}

void CalculateBattleResult()
{
  //TODO: Calculate damage
  ReducedAttackerHealth=8;
  ReducedDefenderHealth=4;
}

void BattleScene()
{
  if(debugRefresh==true)
  {
    PrepareBattleScene();
    debugRefresh=false;
  }
  animationFrames();
  drawBattleScene(Attacker.player,Attacker.unitId,Defender.player,Defender.unitId);
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
  else if(SceneState==SCENE_STATE_ATTACK)
  {
    if(frames==20)
    {
      frames=1;
      SceneState=SCENE_STATE_DEMOLITION;
    }
    else
    {
      frames++;
    }
  }
  else if(SceneState==SCENE_STATE_DEMOLITION)
  {
    if(frames==20)
    {
      frames=1;
      SceneState=SCENE_STATE_SUMMARY;
    }
    else
    {
      frames++;
    }
  }
  else
  {
    if(frames==100)
    {
      frames=1;
      SceneState=SCENE_STATE_IDLE;
      PrepareBattleScene();
    }
    else
    {
      if(frames%5==0)
      {
        UpdateHpCounters();
      }
      frames++;
    }
  }
}

void UpdateHpCounters()
{
  if(AttackerUnitHealth>ReducedAttackerHealth)
  {
    AttackerUnitHealth--;
  }
  if(DefenderUnitHealth>ReducedDefenderHealth)
  {
    DefenderUnitHealth--;
  }
}

