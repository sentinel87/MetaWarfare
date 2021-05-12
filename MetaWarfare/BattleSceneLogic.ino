#define GRASSLAND 1
#define ROAD 2
#define FOREST 3
#define COASTLINE 4
#define BUILDING 5
#define BASE 6

#define ARTILLERY_EFFECT 1
#define TANK_GUN_EFFECT 2
#define AUTOMATIC_GUN_EFFECT 3
#define NONE_EFFECT 4

#define SCENE_STATE_IDLE 1
#define SCENE_STATE_ATTACK 2
#define SCENE_STATE_DEMOLITION 3
#define SCENE_STATE_SUMMARY 4

int LeftSceneTheme=FOREST;
int RightSceneTheme=FOREST;

//GameTileStruct Attacker={12,1,6,10,0,0};
int AttackerAttackType=TANK_GUN_EFFECT;
//GameTileStruct Defender={12,2,6,10,0,0};
int DefenderAttackType=TANK_GUN_EFFECT;

int SceneState=SCENE_STATE_IDLE;
int frames=0;

int AttackerUnitHealth=0;
int DefenderUnitHealth=0;
int ReducedAttackerHealth=10;
int ReducedDefenderHealth=10;

bool debugRefresh=false;

void PrepareBattleScene()
{
  ReducedAttackerHealth=10;
  ReducedDefenderHealth=10;
  SceneState=SCENE_STATE_IDLE;
  AttackerUnitHealth=Attacker.unitHp;
  DefenderUnitHealth=Defender.unitHp;
  SetAttackType(true,Attacker.unitId);
  SetTerrainType(true,Attacker.terrainTexture);
  SetAttackType(false,Defender.unitId);
  SetTerrainType(false,Defender.terrainTexture);
  if(Attacker.unitId==5 || Attacker.unitId==6)
  {
    DefenderAttackType=NONE_EFFECT;
  }
  if(Defender.unitId==5 || Defender.unitId==6)
  {
    DefenderAttackType=NONE_EFFECT;
  }
  CalculateBattleResult();
}

void SetAttackType(bool attacker,int unitId)
{
  int result=AUTOMATIC_GUN_EFFECT;
  
  switch(unitId)
  {
    case 1:
      result=AUTOMATIC_GUN_EFFECT; break;
    case 2:
      result=TANK_GUN_EFFECT; break;
    case 3:
      result=TANK_GUN_EFFECT; break;
    case 4:
      result=TANK_GUN_EFFECT; break;
    case 5:
      result=ARTILLERY_EFFECT; break;
    case 6:
      result=ARTILLERY_EFFECT; break;
    case 7:
      result=AUTOMATIC_GUN_EFFECT; break;
    case 8:
      result=TANK_GUN_EFFECT; break;
    default:
      result=NONE_EFFECT; break;
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
    case 11:
      result=BASE; break;
    case 12:
      result=BUILDING; break;
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
      result=COASTLINE; break;
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
  if(Attacker.unitId==5 || Attacker.unitId==6) // Artillery attack
  {
    ReducedDefenderHealth=4;
  }
  else
  {
    if(Defender.unitId==5 || Defender.unitId==6) // Artillery defend
    {
      ReducedDefenderHealth=7;
    }
    else
    {
      ReducedAttackerHealth=8;
      ReducedDefenderHealth=4; 
    }
  }
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
    if(frames==50)
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
    if(frames==70)
    {
      frames=1;
      SceneState=SCENE_STATE_IDLE;
      //PrepareBattleScene();
      SceneMode=MAP_MODE;
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
