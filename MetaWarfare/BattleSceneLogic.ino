#include <math.h>

#define GRASSLAND 1
#define ROAD 2
#define FOREST 3
#define COASTLINE 4
#define BUILDING 5
#define BASE 6
#define MOUNTAINS 7
#define BRIDGE 8

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
int AttackerTerrainBonus=0;
int DefenderUnitHealth=0;
int DefenderTerrainBonus=0;
int ReducedAttackerHealth=10;
int ReducedDefenderHealth=10;

bool debugRefresh=false;

double attackArray[9][9]
{
  {0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00},
  {0.00,0.50,0.21,0.11,0.11,0.30,0.30,0.75,0.65},
  {0.00,0.70,0.50,0.35,0.35,0.60,0.60,0.70,0.60},
  {0.00,0.80,0.70,0.50,0.50,0.70,0.70,1.00,0.70},
  {0.00,0.80,0.70,0.50,0.50,0.70,0.70,1.00,0.70},
  {0.00,0.70,0.60,0.60,0.60,0.60,0.60,0.80,0.80},
  {0.00,0.80,0.80,0.80,0.80,0.60,0.60,0.90,0.90},
  {0.00,0.10,0.05,0.02,0.02,0.20,0.20,0.50,0.40},
  {0.00,0.70,0.50,0.40,0.40,0.60,0.60,0.65,0.50}
};

void BattleScene()
{
  if(debugRefresh==true)
  {
    PrepareBattleScene();
    debugRefresh=false;
  }
  animationFrames();
  drawBattleScene(Attacker->player,Attacker->unitId,Defender->player,Defender->unitId);
}

void PrepareBattleScene()
{
  ReducedAttackerHealth=10;
  ReducedDefenderHealth=10;
  SceneState=SCENE_STATE_IDLE;
  AttackerUnitHealth=Attacker->unitHp;
  AttackerTerrainBonus=GetTerrainDefBonus(Attacker->terrainTexture);
  DefenderUnitHealth=Defender->unitHp;
  DefenderTerrainBonus=GetTerrainDefBonus(Defender->terrainTexture);
  SetAttackType(true,Attacker->unitId);
  SetTerrainType(true,Attacker->terrainTexture);
  SetAttackType(false,Defender->unitId);
  SetTerrainType(false,Defender->terrainTexture);
  if(Attacker->unitId==5 || Attacker->unitId==6)
  {
    DefenderAttackType=NONE_EFFECT;
  }
  if(Defender->unitId==5 || Defender->unitId==6)
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
    case 2:
      result=MOUNTAINS; break;
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
    case 26:
    case 27:
      result=ROAD; break;
    case 28:
    case 29:
      result=BRIDGE; break;
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

int GetTerrainDefBonus(int id)
{
  int bonus = 0;
  switch(id)
  {
    case 0:
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
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
    case 26:
    case 27:
    case 28:
    case 29:
      bonus = 0; break;
    case 2:
      bonus = 4; break;
    case 10:
      bonus = 1; break;
    case 11:
    case 12:
    case 25:
      bonus = 2; break;
    default:
      bonus = 0;
  }
  return bonus;
}

void CalculateBattleResult()
{
  if(Attacker->unitId==5 || Attacker->unitId==6) // Artillery attack
  {
    double baseAttacker = attackArray[Attacker->unitId][Defender->unitId];
    baseAttacker -= (DefenderTerrainBonus*0.02);
    double totalAttacker = nearbyint(baseAttacker * Attacker->unitHp);
    ReducedDefenderHealth = Defender->unitHp-(int)totalAttacker;
    ReducedAttackerHealth = Attacker->unitHp;
  }
  else
  {
    if(Defender->unitId==5 || Defender->unitId==6) // Artillery defend
    {
      double baseAttacker = attackArray[Attacker->unitId][Defender->unitId];
      baseAttacker -= (DefenderTerrainBonus*0.02);
      double totalAttacker = baseAttacker * Attacker->unitHp;
      if(Attacker->unitId==4 && AttackerTerrainBonus>0) //TD bonus
        totalAttacker+=(AttackerTerrainBonus*0.02);
      totalAttacker=nearbyint(totalAttacker);
      ReducedDefenderHealth = Defender->unitHp-(int)totalAttacker;
      ReducedAttackerHealth = Attacker->unitHp;
    }
    else
    {
      double baseAttacker = attackArray[Attacker->unitId][Defender->unitId];
      baseAttacker += (0.10-(DefenderTerrainBonus*0.02)); //Bonus for initiative
      double baseDefender = attackArray[Defender->unitId][Attacker->unitId];
      baseDefender -= (0.20+(AttackerTerrainBonus*0.02)); //Penalty for ambush
      if(baseDefender<0)
      {
        baseDefender=0;
      }

      double totalAttacker = baseAttacker * Attacker->unitHp;
      if(Attacker->unitId==4 && AttackerTerrainBonus>0) //TD bonus
        totalAttacker+=(AttackerTerrainBonus*0.02);
      totalAttacker=nearbyint(totalAttacker);
      double totalDefender = nearbyint(baseDefender * Defender->unitHp);
      ReducedAttackerHealth = Attacker->unitHp-(int)totalDefender;
      ReducedDefenderHealth = Defender->unitHp-(int)totalAttacker; 
    }
  }
  if(ReducedAttackerHealth<0)
  {
    ReducedAttackerHealth=0;
  }
  if(ReducedDefenderHealth<0)
  {
    ReducedDefenderHealth=0;
  }
}

void updateMapTiles()
{
  Attacker->unitHp = ReducedAttackerHealth;
  if(ReducedAttackerHealth==0)
  {
    Attacker->unitId = 0;
    Attacker->player = 0;
    Attacker->active = 0;
  }
  Defender->unitHp = ReducedDefenderHealth;
  if(ReducedDefenderHealth==0)
  {
    Defender->unitId = 0;
    Defender->player = 0;
    Defender->active = 0;
  }
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
      if(AttackerAttackType==TANK_GUN_EFFECT || DefenderAttackType==TANK_GUN_EFFECT)
      {
        gb.sound.fx(cannonExplosionSound);
      }
      else if(AttackerAttackType==ARTILLERY_EFFECT || DefenderAttackType==ARTILLERY_EFFECT)
      {
        gb.sound.fx(artilleryExplosionSound);
      }
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
      updateMapTiles();
      Attacker = &None;
      Defender = &None;
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
