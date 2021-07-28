Image InfantryIdle(IMAGE_INFANTRY_IDLE);
Image InfantryAttack(IMAGE_INFANTRY_ATTACK);
Image MechInfantryIdle(IMAGE_MECH_INFANTRY_IDLE);
Image MechInfantryAttack(IMAGE_MECH_INFANTRY_ATTACK);
Image MediumTankIdle(IMAGE_MEDIUM_TANK_IDLE);
Image MediumTankAttack(IMAGE_MEDIUM_TANK_ATTACK);
Image HalfTruckIdle(IMAGE_HALF_TRUCK_IDLE);
Image HalfTruckAttack(IMAGE_HALF_TRUCK_ATTACK);
Image HeavyTankIdle(IMAGE_HEAVY_TANK_IDLE);
Image HeavyTankAttack(IMAGE_HEAVY_TANK_ATTACK);
Image TankDestroyerIdle(IMAGE_TANK_DESTROYER_IDLE);
Image TankDestroyerAttack(IMAGE_TANK_DESTROYER_ATTACK);
Image MobileArtilleryIdle(IMAGE_MOBILE_ARTILLERY_IDLE);
Image MobileArtilleryAttack(IMAGE_MOBILE_ARTILLERY_ATTACK);
Image MobileSSMIdle(IMAGE_MOBILE_SSM_IDLE);
Image MobileSSMAttack(IMAGE_MOBILE_SSM_ATTACK);

Image EffectExplosion(IMAGE_EFFECT_EXPLOSION); 
Image EffectGunExplosion(IMAGE_EFFECT_GUN_EXPLOSION);
Image EffectAutomaticGun(IMAGE_EFFECT_AUTOMATIC_GUN);

int selectionFrame=0;

void drawMainMenu(int posX, int posY)
{
  gb.display.drawImage(0,0,IMAGE_MAIN_THEME);
  gb.display.drawImage(0,0,IMAGE_TITLE_THEME);
  gb.display.setColor(WHITE);
  gb.display.setCursor(12,30);
  gb.display.println("TUTORIAL");
  gb.display.setCursor(12,44);
  gb.display.println("2 PLAYERS");
  gb.display.setCursor(12,58);
  gb.display.println("HIGH SCORES");
  if(SaveExist==false)
  {
    gb.display.setColor(BEIGE);
  }
  gb.display.setCursor(12,51);
  gb.display.println("CONTINUE");
  gb.display.setColor(BEIGE);
  gb.display.setCursor(12,37);
  gb.display.println("CAMPAIGN");
  
  gb.display.drawImage(posX,posY,Pointer);
}

void drawScenarioMenu(int posX, int posY)
{
  gb.display.drawImage(0,0,IMAGE_MAIN_THEME);
  gb.display.setColor(WHITE);
  gb.display.setCursor(2,3);
  gb.display.println("1. Lake valley");
  gb.display.setCursor(2,9);
  gb.display.println("2. Island");
  gb.display.setCursor(2,15);
  gb.display.println("3. Duel plains");
  gb.display.setCursor(2,21);
  gb.display.println("4. Mountain lake");
  gb.display.setCursor(2,27);
  gb.display.println("5. Canals");
  gb.display.setCursor(2,33);
  gb.display.println("6. Rocky pass");
  gb.display.setCursor(2,39);
  gb.display.println("7. Sea coast");
  gb.display.setCursor(2,45);
  gb.display.println("BACK");
  
  gb.display.drawImage(posX,posY,Pointer);
}

void drawTutorialMenu(int posX, int posY)
{
  gb.display.drawImage(0,0,IMAGE_MAIN_THEME);
  gb.display.setColor(WHITE);
  gb.display.setCursor(2,3);
  gb.display.println("1. Basic");
  gb.display.setCursor(2,9);
  gb.display.println("2. Advanced");
  gb.display.setCursor(2,15);
  gb.display.println("BACK");
  
  gb.display.drawImage(posX,posY,Pointer);
}

void drawMap()
{
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<6;j++)
    {
      GameTileStruct tile=CurrentBoard[j+sRowIdx][i+sColIdx];
      
      if(tile.player!=0)
      {
        if(tile.unitId!=0)
        {
          if(tile.active==1)
          {
            switch(tile.player)
            {
              case 1:
                gb.display.drawImage(i*10,j*10,IMAGE_PLAYER1_BOARD); break;
              case 2:
                gb.display.drawImage(i*10,j*10,IMAGE_PLAYER2_BOARD); break;
            }
          }
          else
          {
            gb.display.drawImage(i*10,j*10,IMAGE_DEACTIVATE_BOARD);
          }
          if(tile.moveGrid==2) // draw attack grid
          {
            gb.display.drawImage(i*10,j*10,IMAGE_ATTACK_GRID);
          }
          drawUnit(tile.unitId,tile.unitHp,i*10,j*10);
        }
      }
      else
      {
        if(tile.terrainTexture==11 || tile.terrainTexture==12 || tile.terrainTexture==25) //Base/Building belonging
        {
          if(tile.playerBuilding==PLAYER_1)
            gb.display.drawImage(i*10,j*10,IMAGE_PLAYER1_BOARD);
          else if(tile.playerBuilding==PLAYER_2)
            gb.display.drawImage(i*10,j*10,IMAGE_PLAYER2_BOARD);
          else
            gb.display.drawImage(i*10,j*10,IMAGE_DEACTIVATE_BOARD);
          drawTerrain(tile.terrainTexture,i*10,j*10);
        }
        else
        {
          drawTerrain(tile.terrainTexture,i*10,j*10);
        }
        if(tile.moveGrid==2) // draw attack grid
        {
          gb.display.drawImage(i*10,j*10,IMAGE_ATTACK_GRID);
        }
      }
      if(tile.moveGrid==1)
      {
        gb.display.drawImage(i*10,j*10,MovementGrid);
      }
    }
  }
  if(mapMode == TARGET_MODE)
  {
    gb.display.drawImage(posX,posY,CursorSelected);
  }
  else
  {
    gb.display.drawImage(posX,posY,IMAGE_CURSOR);
  }
}

void drawDropdownMenu(int posX,int posY,int selection)
{
  if(selectionFrame==0)
  {
    selectionFrame=1;
  }
  else
  {
    selectionFrame=0;
  }
  
  int fixedX=posX;
  int fixedY=posY;
  
  if(posX + 10 + 30 > 80)
  {
    fixedX-=30;
  }
  else
  {
    fixedX=posX+10;
  }
  if(posY + 30 > 64)
  {
    fixedY=posY-15;
  }
  
  gb.display.setColor(BEIGE);
  gb.display.drawImage(fixedX,fixedY,IMAGE_MENU_THEME);
  if(selectionFrame==1 && selection==ATTACK_ACTION)
    gb.display.setColor(RED);  
  else
    gb.display.setColor(BLACK); 
  gb.display.setCursor(fixedX+1,fixedY+1);
  gb.display.println("ATTACK");
  if(selectionFrame==1 && selection==STOP_ACTION)
    gb.display.setColor(RED);  
  else
    gb.display.setColor(BLACK);  
  gb.display.setCursor(fixedX+1,fixedY+7);
  gb.display.println("STOP");
  if(selectionFrame==1 && selection==CAPTURE_ACTION)
    gb.display.setColor(RED);  
  else
    gb.display.setColor(BLACK); 
  if(selectedUnit.unitId!=7 && selectedUnit.unitId!=8)
  {
    gb.display.setColor(BEIGE);
  }
  gb.display.setCursor(fixedX+1,fixedY+13);
  gb.display.println("CAPTURE");
  //if(selectionFrame==1 && selection==4)
  //  gb.display.setColor(RED);  
  //else
  //  gb.display.setColor(BLACK); 
  //gb.display.setCursor(fixedX+1,fixedY+19);
  //gb.display.println("LOAD");
}

void drawInfoMenu(int selection)
{
  if(selectionFrame==0)
  {
    selectionFrame=1;
  }
  else
  {
    selectionFrame=0;
  }
  gb.display.drawImage(0,0,IMAGE_INFO_THEME);
  if(CurrentPlayer->id==1)
  {
    gb.display.setColor(RED);
    gb.display.setCursor(2,2);
    gb.display.println("PLAYER 1");
  }
  else
  {
    gb.display.setColor(BLUE);
    gb.display.setCursor(2,2);
    gb.display.println("PLAYER 2");
  }
  gb.display.setColor(ORANGE);
  gb.display.setCursor(2,9);
  gb.display.println("Gd:");
  gb.display.setCursor(15,9);
  gb.display.println(CurrentPlayer->funds);
  //drawTerrain(3,2,16);
  //gb.display.drawImage(15,16,IMAGE_SHIELD);
  //gb.display.setColor(GRAY);
  //gb.display.setCursor(25,18);
  //gb.display.println("+2");
  //gb.display.setCursor(2,27);
  //gb.display.println("Road");
  
  if(selectionFrame==1 && infoSelection==RESUME_INFO_ACTION)
    gb.display.setColor(RED);  
  else
    gb.display.setColor(BLACK); 
  gb.display.setCursor(2,36);
  gb.display.println("RESUME");
  if(selectionFrame==1 && infoSelection==END_TURN_INFO_ACTION)
    gb.display.setColor(RED);  
  else
    gb.display.setColor(BLACK); 
  gb.display.setCursor(2,43);
  gb.display.println("END TURN");
  if(Tutorial==-1)
  {
    if(selectionFrame==1 && infoSelection==SAVE_INFO_ACTION)
      gb.display.setColor(RED);  
    else
      gb.display.setColor(BLACK);
  }
  else
     gb.display.setColor(BEIGE);
  gb.display.setCursor(2,50);
  gb.display.println("SAVE");
  if(selectionFrame==1 && infoSelection==QUIT_INFO_ACTION)
    gb.display.setColor(RED);  
  else
    gb.display.setColor(BLACK);  
  gb.display.setCursor(2,57);
  gb.display.println("QUIT");
}

void debug()
{
  gb.display.setColor(WHITE);
  gb.display.setCursor(3,3);
  gb.display.println(gb.getFreeRam());
  gb.display.setCursor(3,9);
  gb.display.println(gb.getCpuLoad());
}

void drawTerrain(int id,int posX,int posY)
{
  switch(id)
  {
    case 0:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_SEA,10,10); break;
    case 1:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_GRASS,10,10); break;
    case 2:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_MOUNTAIN,10,10); break;
    case 3:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_ROAD_HOR,10,10); break;
    case 4:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_ROAD_VER,10,10); break;
    case 5:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_ROAD_CROSS,10,10); break;
    case 6:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_ROAD_TURN,10,-10); break;
    case 7:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_ROAD_TURN,-10,-10); break;
    case 8:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_ROAD_TURN,10,10); break;
    case 9:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_ROAD_TURN,-10,10); break;
    case 10:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_FOREST,10,10); break;
    case 11:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BASE,10,10); break;
    case 12:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BUILDING,10,10); break;
    case 13:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BEACH_VER,10,10); break;
    case 14:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BEACH_VER,-10,10); break;
    case 15:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BEACH_HOR,10,-10); break;
    case 16:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BEACH_HOR,10,10); break;
    case 17:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BEACH_CORNER,10,-10); break;
    case 18:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BEACH_CORNER,10,10); break;
    case 19:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BEACH_CORNER,-10,-10); break;
    case 20:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BEACH_CORNER,-10,10); break;
    case 21:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BEACH_PEAK,10,-10); break;
    case 22:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BEACH_PEAK,10,10); break;
    case 23:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BEACH_PEAK,-10,-10); break;
    case 24:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BEACH_PEAK,-10,10); break;
    case 25:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_CAPITAL,10,10); break;
    case 26:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_ROAD_END,10,10); break;
    case 27:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_ROAD_END,-10,10); break;
    case 28:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BRIDGE_HOR,10,10); break;
    case 29:
      gb.display.drawImage(posX,posY,IMAGE_TERRAIN_BRIDGE_VER,10,10); break;
  }
}

void drawUnit(int idx, int hp, int posX, int posY)
{
  switch(idx)
  {
    case 1:
      gb.display.drawImage(posX,posY,UHalfTruck,10,10); break;
    case 2:
      gb.display.drawImage(posX,posY,UMediumTank,10,10); break;
    case 3:
      gb.display.drawImage(posX,posY,UHeavyTank,10,10); break;
    case 4:
      gb.display.drawImage(posX,posY,UTankDestroyer,10,10); break;
    case 5:
      gb.display.drawImage(posX,posY,UMobileArtillery,10,10); break;
    case 6:
      gb.display.drawImage(posX,posY,UMobileSSM,10,10); break; 
    case 7:
      gb.display.drawImage(posX,posY,UInfantry,10,10); break; 
    case 8:
      gb.display.drawImage(posX,posY,UMechInfantry,10,10); break; 
  }
  if(hp<10)
  {
    gb.display.setColor(WHITE);
    gb.display.setCursor(posX,posY);
    gb.display.println(hp);  
  }
}

//Battle Scene

void drawBattleScene(int attacker,int attackUnitId,int defender,int defenderUnitId)
{
  drawLeftBattleScene(attacker,attackUnitId);
  drawRightBattleScene(defender,defenderUnitId);
  gb.display.setColor(BLACK);
  gb.display.drawLine(40,0,40,32);
  gb.display.drawLine(39,33,39,64);
}

void drawLeftBattleScene(int player, int unitId)
{
  drawBackgroundScene(true);
  int hp=10;
  switch(unitId)
  {
    case 1:
      drawHalfTruck(true); break;
    case 2:
      drawMediumTank(true); break;
    case 3:
      drawHeavyTank(true); break;
    case 4:
      drawTankDestroyer(true); break;
    case 5:
      drawMobileArtillery(true); break;
    case 6:
      drawMobileSSM(true); break;
    case 7:
      drawInfantry(true); break;
    case 8:
      drawMechInfantry(true); break;
  }
  if(SceneState==SCENE_STATE_DEMOLITION)
  {
    if(unitId==7 || unitId==8)
    {
      drawDemolitionAnimation(true,true);
    }
    else
    {
      drawDemolitionAnimation(true,false);
    }
  }
  if(player==1)
  {
    gb.display.drawImage(0,54,IMAGE_PLAYER1_BOARD,10,10);
    gb.display.drawImage(10,54,IMAGE_PLAYER1_BOARD,10,10);
    gb.display.drawImage(20,54,IMAGE_PLAYER1_BOARD,10,10);
    gb.display.drawImage(25,54,IMAGE_PLAYER1_BOARD,10,10);
  }
  else
  {
    gb.display.drawImage(0,54,IMAGE_PLAYER2_BOARD,10,10);
    gb.display.drawImage(10,54,IMAGE_PLAYER2_BOARD,10,10);
    gb.display.drawImage(20,54,IMAGE_PLAYER2_BOARD,10,10);
    gb.display.drawImage(25,54,IMAGE_PLAYER2_BOARD,10,10);
  }
  gb.display.drawImage(25,55,IMAGE_SHIELD);
  gb.display.setColor(BLACK);
  gb.display.setCursor(28,56);
  gb.display.println(AttackerTerrainBonus);
  gb.display.setColor(ORANGE);
  gb.display.setFontSize(1);
  gb.display.setCursor(2,55);
  gb.display.println(AttackerUnitHealth);
  for(int i=0;i<AttackerUnitHealth*2;i++)
  {
    gb.display.drawImage(2+i,61,IMAGE_HP_BAR,1,2);
  }
}

void drawRightBattleScene(int player, int unitId)
{
  drawBackgroundScene(false);
  int hp=10;
  switch(unitId)
  {
    case 1:
      drawHalfTruck(false); break;
    case 2:
      drawMediumTank(false); break;
    case 3:
      drawHeavyTank(false); break;
    case 4:
      drawTankDestroyer(false); break;
    case 5:
      drawMobileArtillery(false); break;
    case 6:
      drawMobileSSM(false); break;
    case 7:
      drawInfantry(false); break;
    case 8:
      drawMechInfantry(false); break;
  }
  if(SceneState==SCENE_STATE_DEMOLITION)
  {
    if(unitId==7 || unitId==8)
    {
      drawDemolitionAnimation(false,true);
    }
    else
    {
      drawDemolitionAnimation(false,false);
    }
  }
  if(player==1)
  {
    gb.display.drawImage(45,0,IMAGE_PLAYER1_BOARD,10,10);
    gb.display.drawImage(55,0,IMAGE_PLAYER1_BOARD,10,10);
    gb.display.drawImage(65,0,IMAGE_PLAYER1_BOARD,10,10);
    gb.display.drawImage(70,0,IMAGE_PLAYER1_BOARD,10,10);
  }
  else
  {
    gb.display.drawImage(45,0,IMAGE_PLAYER2_BOARD,10,10);
    gb.display.drawImage(55,0,IMAGE_PLAYER2_BOARD,10,10);
    gb.display.drawImage(65,0,IMAGE_PLAYER2_BOARD,10,10);
    gb.display.drawImage(70,0,IMAGE_PLAYER2_BOARD,10,10);
  }
  gb.display.drawImage(70,1,IMAGE_SHIELD);
  gb.display.setColor(BLACK);
  gb.display.setCursor(73,2);
  gb.display.println(DefenderTerrainBonus);
  gb.display.setColor(ORANGE);
  gb.display.setFontSize(1);
  gb.display.setCursor(47,1);
  gb.display.println(DefenderUnitHealth);
  for(int i=0;i<DefenderUnitHealth*2;i++)
  {
    gb.display.drawImage(47+i,7,IMAGE_HP_BAR,1,2);
  }
}

void drawBackgroundScene(bool attacker)
{
  if(attacker==true)
  {
    if(LeftSceneTheme==GRASSLAND)
    {
      gb.display.drawImage(0,0,IMAGE_SCENE_GRASS,40,64);
    }
    else if(LeftSceneTheme==ROAD)
    {
      gb.display.drawImage(0,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(0,44,IMAGE_SCENE_ROAD,40,20);
    }
    else if(LeftSceneTheme==FOREST)
    {
      gb.display.drawImage(0,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(0,0,IMAGE_SCENE_FOREST,40,20);
    }
    else if(LeftSceneTheme==BUILDING)
    {
      gb.display.drawImage(0,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(0,0,IMAGE_SCENE_BUILDING,40,20);
    }
    else if(LeftSceneTheme==BASE)
    {
      gb.display.drawImage(0,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(0,0,IMAGE_SCENE_BASE,40,20);
    }
    else if(LeftSceneTheme==COASTLINE)
    {
      gb.display.drawImage(0,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(0,4,IMAGE_SCENE_COAST,40,32);
    }
    else if(LeftSceneTheme==MOUNTAINS)
    {
      gb.display.drawImage(0,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(0,0,IMAGE_SCENE_MOUNTAINS,40,20);
    }
    else if(LeftSceneTheme==BRIDGE)
    {
      gb.display.drawImage(0,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(0,27,IMAGE_SCENE_ROAD,40,18);
      gb.display.drawImage(0,44,IMAGE_SCENE_ROAD,40,20);
      gb.display.drawImage(0,8,IMAGE_SCENE_BRIDGE,40,20);
    }
  }
  else
  {
    if(RightSceneTheme==GRASSLAND)
    {
      gb.display.drawImage(40,0,IMAGE_SCENE_GRASS,40,64);
    }
    else if(RightSceneTheme==ROAD)
    {
      gb.display.drawImage(40,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(40,44,IMAGE_SCENE_ROAD,40,20);
    }
    else if(RightSceneTheme==FOREST)
    {
      gb.display.drawImage(40,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(40,0,IMAGE_SCENE_FOREST,40,20);
    }
    else if(RightSceneTheme==BUILDING)
    {
      gb.display.drawImage(40,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(40,0,IMAGE_SCENE_BUILDING,40,20);
    }
    else if(RightSceneTheme==BASE)
    {
      gb.display.drawImage(40,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(40,0,IMAGE_SCENE_BASE,40,20);
    }
    else if(RightSceneTheme==COASTLINE)
    {
      gb.display.drawImage(40,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(40,4,IMAGE_SCENE_COAST,40,32);
    }
    else if(RightSceneTheme==MOUNTAINS)
    {
      gb.display.drawImage(40,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(40,0,IMAGE_SCENE_MOUNTAINS,40,20);
    }
    else if(RightSceneTheme==BRIDGE)
    {
      gb.display.drawImage(40,0,IMAGE_SCENE_GRASS,40,64);
      gb.display.drawImage(40,27,IMAGE_SCENE_ROAD,40,18);
      gb.display.drawImage(40,44,IMAGE_SCENE_ROAD,40,20);
      gb.display.drawImage(40,8,IMAGE_SCENE_BRIDGE,40,20);
    }
  }
}

void drawInfantry(bool attacker)
{
  if(attacker==true)
  {
    if(SceneState==SCENE_STATE_ATTACK)
    {
      if(AttackerUnitHealth>8)
        gb.display.drawImage(20,5,InfantryAttack,10,15);
      if(AttackerUnitHealth>6)
        gb.display.drawImage(5,8,InfantryAttack,10,15);
      if(AttackerUnitHealth>4)
        gb.display.drawImage(16,22,InfantryAttack,10,15);
      if(AttackerUnitHealth>2)
        gb.display.drawImage(1,28,InfantryAttack,10,15);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(20,38,InfantryAttack,10,15);
    }
    else
    {
      if(AttackerUnitHealth>8)
        gb.display.drawImage(20,5,InfantryIdle,10,15);
      if(AttackerUnitHealth>6)
        gb.display.drawImage(5,8,InfantryIdle,10,15);
      if(AttackerUnitHealth>4)
        gb.display.drawImage(16,22,InfantryIdle,10,15);
      if(AttackerUnitHealth>2)
        gb.display.drawImage(1,28,InfantryIdle,10,15);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(20,38,InfantryIdle,10,15);
    }
  }
  else
  {
    if(SceneState==SCENE_STATE_ATTACK && Attacker->unitId!=5 && Attacker->unitId!=6)
    {
      if(DefenderUnitHealth>8)
        gb.display.drawImage(45,15,InfantryAttack,-10,15);
      if(DefenderUnitHealth>6)
        gb.display.drawImage(60,18,InfantryAttack,-10,15);
      if(DefenderUnitHealth>4)
        gb.display.drawImage(48,32,InfantryAttack,-10,15);
      if(DefenderUnitHealth>2)
        gb.display.drawImage(64,38,InfantryAttack,-10,15);
      if(DefenderUnitHealth>0)
        gb.display.drawImage(45,48,InfantryAttack,-10,15);
    }
    else
    {
      if(DefenderUnitHealth>8)
        gb.display.drawImage(45,15,InfantryIdle,-10,15);
      if(DefenderUnitHealth>6)
        gb.display.drawImage(60,18,InfantryIdle,-10,15);
      if(DefenderUnitHealth>4)
        gb.display.drawImage(48,32,InfantryIdle,-10,15);
      if(DefenderUnitHealth>2)
        gb.display.drawImage(64,38,InfantryIdle,-10,15);
      if(DefenderUnitHealth>0)
        gb.display.drawImage(45,48,InfantryIdle,-10,15);
    }
  }
}

void drawMechInfantry(bool attacker)
{
  if(attacker==true)
  {
    if(SceneState==SCENE_STATE_ATTACK)
    {
      if(AttackerUnitHealth>8)
        gb.display.drawImage(20,10,MechInfantryAttack,15,12);
      if(AttackerUnitHealth>6)
        gb.display.drawImage(3,14,MechInfantryAttack,15,12);
      if(AttackerUnitHealth>4)
        gb.display.drawImage(16,25,MechInfantryAttack,15,12);
      if(AttackerUnitHealth>2)
        gb.display.drawImage(1,32,MechInfantryAttack,15,12);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(20,40,MechInfantryAttack,15,12);
    }
    else
    {
      if(AttackerUnitHealth>8)
        gb.display.drawImage(20,10,MechInfantryIdle,15,12);
      if(AttackerUnitHealth>6)
        gb.display.drawImage(3,14,MechInfantryIdle,15,12);
      if(AttackerUnitHealth>4)
        gb.display.drawImage(16,25,MechInfantryIdle,15,12);
      if(AttackerUnitHealth>2)
        gb.display.drawImage(1,32,MechInfantryIdle,15,12);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(20,40,MechInfantryIdle,15,12);
    }
  }
  else
  {
    if(SceneState==SCENE_STATE_ATTACK && Attacker->unitId!=5 && Attacker->unitId!=6)
    {
      if(DefenderUnitHealth>8)
        gb.display.drawImage(45,20,MechInfantryAttack,-15,12);
      if(DefenderUnitHealth>6)
        gb.display.drawImage(62,24,MechInfantryAttack,-15,12);
      if(DefenderUnitHealth>4)
        gb.display.drawImage(49,35,MechInfantryAttack,-15,12);
      if(DefenderUnitHealth>2)
        gb.display.drawImage(64,42,MechInfantryAttack,-15,12);
      if(DefenderUnitHealth>0)
        gb.display.drawImage(45,50,MechInfantryAttack,-15,12);
    }
    else
    {
      if(DefenderUnitHealth>8)
        gb.display.drawImage(45,20,MechInfantryIdle,-15,12);
      if(DefenderUnitHealth>6)
        gb.display.drawImage(62,24,MechInfantryIdle,-15,12);
      if(DefenderUnitHealth>4)
        gb.display.drawImage(49,35,MechInfantryIdle,-15,12);
      if(DefenderUnitHealth>2)
        gb.display.drawImage(64,42,MechInfantryIdle,-15,12);
      if(DefenderUnitHealth>0)
        gb.display.drawImage(45,50,MechInfantryIdle,-15,12);
    }
  }
}

void drawMediumTank(bool attacker)
{
  if(attacker==true)
  {
    if(SceneState==SCENE_STATE_ATTACK)
    {
      if(AttackerUnitHealth>5)
        gb.display.drawImage(1,14,MediumTankAttack,25,15);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(5,34,MediumTankAttack,25,15);
    }
    else
    {
      if(AttackerUnitHealth>5)
        gb.display.drawImage(1,14,MediumTankIdle,25,15);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(5,34,MediumTankIdle,25,15);
    }
  }
  else
  {
    if(SceneState==SCENE_STATE_ATTACK && Attacker->unitId!=5 && Attacker->unitId!=6)
    {
      if(DefenderUnitHealth>5)
        gb.display.drawImage(54,24,MediumTankAttack,-25,15);
      if(DefenderUnitHealth>0)
        gb.display.drawImage(50,44,MediumTankAttack,-25,15);
    }
    else
    {
      if(DefenderUnitHealth>5)
        gb.display.drawImage(54,24,MediumTankIdle,-25,15);
      if(DefenderUnitHealth>0)
        gb.display.drawImage(50,44,MediumTankIdle,-25,15);
    }
  }
}

void drawHeavyTank(bool attacker)
{
  if(attacker==true)
  {
    if(SceneState==SCENE_STATE_ATTACK)
    {
      if(AttackerUnitHealth>5)
        gb.display.drawImage(1,14,HeavyTankAttack,25,15);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(5,34,HeavyTankAttack,25,15);
    }
    else
    {
      if(AttackerUnitHealth>5)
        gb.display.drawImage(1,14,HeavyTankIdle,25,15);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(5,34,HeavyTankIdle,25,15);
    }
  }
  else
  {
    if(SceneState==SCENE_STATE_ATTACK && Attacker->unitId!=5 && Attacker->unitId!=6)
    {
      if(DefenderUnitHealth>5)
        gb.display.drawImage(54,24,HeavyTankAttack,-25,15);
      if(DefenderUnitHealth>0)
        gb.display.drawImage(50,44,HeavyTankAttack,-25,15);
    }
    else
    {
      if(DefenderUnitHealth>5)
        gb.display.drawImage(54,24,HeavyTankIdle,-25,15);
      if(DefenderUnitHealth>0)
        gb.display.drawImage(50,44,HeavyTankIdle,-25,15);
    }
  }
}

void drawTankDestroyer(bool attacker)
{
  if(attacker==true)
  {
    if(SceneState==SCENE_STATE_ATTACK)
    {
      if(AttackerUnitHealth>5)
        gb.display.drawImage(1,14,TankDestroyerAttack,25,15);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(5,34,TankDestroyerAttack,25,15);
    }
    else
    {
      if(AttackerUnitHealth>5)
        gb.display.drawImage(1,14,TankDestroyerIdle,25,15);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(5,34,TankDestroyerIdle,25,15);
    }
  }
  else
  {
    if(SceneState==SCENE_STATE_ATTACK && Attacker->unitId!=5 && Attacker->unitId!=6)
    {
      if(DefenderUnitHealth>5)
        gb.display.drawImage(54,24,TankDestroyerAttack,-25,15);
      if(DefenderUnitHealth>0)
        gb.display.drawImage(50,44,TankDestroyerAttack,-25,15);
    }
    else
    {
      if(DefenderUnitHealth>5)
        gb.display.drawImage(54,24,TankDestroyerIdle,-25,15);
      if(DefenderUnitHealth>0)
        gb.display.drawImage(50,44,TankDestroyerIdle,-25,15);
    }
  }
}

void drawHalfTruck(bool attacker)
{
  if(attacker==true)
  {
    if(SceneState==SCENE_STATE_ATTACK)
    {
      if(AttackerUnitHealth>5)
        gb.display.drawImage(1,14,HalfTruckAttack,30,15);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(5,34,HalfTruckAttack,30,15);
    }
    else
    {
      if(AttackerUnitHealth>5)
        gb.display.drawImage(1,14,HalfTruckIdle,30,15);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(5,34,HalfTruckIdle,30,15);
    }
  }
  else
  {
    if(SceneState==SCENE_STATE_ATTACK && Attacker->unitId!=5 && Attacker->unitId!=6)
    {
      if(DefenderUnitHealth>5)
        gb.display.drawImage(49,24,HalfTruckAttack,-30,15);
      if(DefenderUnitHealth>0)
        gb.display.drawImage(45,44,HalfTruckAttack,-30,15);
    }
    else
    {
      if(DefenderUnitHealth>5)
        gb.display.drawImage(49,24,HalfTruckIdle,-30,15);
      if(DefenderUnitHealth>0)
        gb.display.drawImage(45,44,HalfTruckIdle,-30,15);
    }
  }
}

void drawMobileArtillery(bool attacker)
{
  if(attacker==true)
  {
    if(SceneState==SCENE_STATE_ATTACK)
    {
      if(AttackerUnitHealth>5)
        gb.display.drawImage(1,9,MobileArtilleryAttack,30,20);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(5,32,MobileArtilleryAttack,30,20);
    }
    else
    {
      if(AttackerUnitHealth>5)
        gb.display.drawImage(1,9,MobileArtilleryIdle,30,20);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(5,32,MobileArtilleryIdle,30,20);
    }
  }
  else
  {
    if(DefenderUnitHealth>5)
      gb.display.drawImage(49,19,MobileArtilleryIdle,-30,20);
    if(DefenderUnitHealth>0)
      gb.display.drawImage(45,42,MobileArtilleryIdle,-30,20);
  }
}

void drawMobileSSM(bool attacker)
{
  if(attacker==true)
  {
    if(SceneState==SCENE_STATE_ATTACK)
    {
      if(AttackerUnitHealth>5)
        gb.display.drawImage(1,9,MobileSSMAttack,30,20);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(5,32,MobileSSMAttack,30,20);
    }
    else
    {
      if(AttackerUnitHealth>5)
        gb.display.drawImage(1,9,MobileSSMIdle,30,20);
      if(AttackerUnitHealth>0)
        gb.display.drawImage(5,32,MobileSSMIdle,30,20);
    }
  }
  else
  {
    if(DefenderUnitHealth>5)
      gb.display.drawImage(49,19,MobileSSMIdle,-30,20);
    if(DefenderUnitHealth>0)
      gb.display.drawImage(45,42,MobileSSMIdle,-30,20);
  }
}

void drawDemolitionAnimation(bool attacker, bool infantry)
{
  if(attacker==true)
  {
    if(DefenderAttackType==ARTILLERY_EFFECT)
    {
      if(DefenderUnitHealth > 5)
      {
        gb.display.drawImage(5,10,EffectExplosion,20,20);
      }
      gb.display.drawImage(10,30,EffectExplosion,20,20);
    }
    else if(DefenderAttackType==TANK_GUN_EFFECT)
    {
      if(DefenderUnitHealth > 5)
      {
        gb.display.drawImage(10,15,EffectGunExplosion,9,9);
      }
      gb.display.drawImage(15,35,EffectGunExplosion,9,9);
    }
    else if(DefenderAttackType==AUTOMATIC_GUN_EFFECT)
    {
      if(infantry==true)
      {
        if(DefenderUnitHealth > 8)
          gb.display.drawImage(22,18,EffectAutomaticGun,8,2);
        if(DefenderUnitHealth > 6)
          gb.display.drawImage(7,21,EffectAutomaticGun,8,2);
        if(DefenderUnitHealth > 4)
          gb.display.drawImage(18,35,EffectAutomaticGun,8,2);
        if(DefenderUnitHealth > 2)
          gb.display.drawImage(3,41,EffectAutomaticGun,8,2);
        gb.display.drawImage(22,51,EffectAutomaticGun,8,2);
      }
      else
      {
        if(DefenderUnitHealth > 5)
        {
          gb.display.drawImage(10,25,EffectAutomaticGun,8,2);
        }
        gb.display.drawImage(15,45,EffectAutomaticGun,8,2);
      }
    }
  }
  else
  {
    if(AttackerAttackType==ARTILLERY_EFFECT)
    {
      if(AttackerUnitHealth > 5)
      {
        gb.display.drawImage(55,20,EffectExplosion,20,20);
      }
      gb.display.drawImage(50,40,EffectExplosion,20,20);
    }
    else if(AttackerAttackType==TANK_GUN_EFFECT)
    {
      if(AttackerUnitHealth > 5)
      {
        gb.display.drawImage(60,25,EffectGunExplosion,9,9);
      }
      gb.display.drawImage(55,45,EffectGunExplosion,9,9);
    }
    else if(AttackerAttackType==AUTOMATIC_GUN_EFFECT)
    {
      if(infantry==true)
      {
        if(AttackerUnitHealth > 8)
          gb.display.drawImage(47,28,EffectAutomaticGun,8,2);
        if(AttackerUnitHealth > 6)
          gb.display.drawImage(62,31,EffectAutomaticGun,8,2);
        if(AttackerUnitHealth > 4)
          gb.display.drawImage(50,45,EffectAutomaticGun,8,2);
        if(AttackerUnitHealth > 2)
          gb.display.drawImage(66,51,EffectAutomaticGun,8,2);
        gb.display.drawImage(47,61,EffectAutomaticGun,8,2);
      }
      else
      {
        if(AttackerUnitHealth > 5)
        {
          gb.display.drawImage(60,35,EffectAutomaticGun,8,2);
        }
        gb.display.drawImage(55,55,EffectAutomaticGun,8,2);
      }
    }
  }
}

//Base scene

void drawBaseScreen(int posX, int posY)
{
  gb.display.drawImage(0,0,IMAGE_INFO_THEME);
  gb.display.drawImage(40,0,IMAGE_INFO_THEME);
  drawUnitField(2,2,7,100);
  if(CurrentPlayer->baseLevel>=2)
    drawUnitField(2,12,8,200);
  else
    gb.display.drawImage(2,12,IMAGE_QUESTION_MARK);
  if(CurrentPlayer->baseLevel>=3)
    drawUnitField(2,22,1,300);
  else
    gb.display.drawImage(2,22,IMAGE_QUESTION_MARK);
  if(CurrentPlayer->baseLevel>=4)
    drawUnitField(2,32,2,500);
  else
    gb.display.drawImage(2,32,IMAGE_QUESTION_MARK);
  if(CurrentPlayer->baseLevel>=5)
    drawUnitField(42,2,5,450);
  else
    gb.display.drawImage(42,2,IMAGE_QUESTION_MARK);
  if(CurrentPlayer->baseLevel>=6)
    drawUnitField(42,12,3,800);
  else
    gb.display.drawImage(42,12,IMAGE_QUESTION_MARK);
  if(CurrentPlayer->baseLevel>=7)
    drawUnitField(42,22,6,750);
  else
    gb.display.drawImage(42,22,IMAGE_QUESTION_MARK);
  if(CurrentPlayer->baseLevel>=8)
    drawUnitField(42,32,4,900);
  else
    gb.display.drawImage(42,32,IMAGE_QUESTION_MARK);
  gb.display.setColor(GREEN); 
  gb.display.setCursor(3,44);
  gb.display.println("UP");
  int baseCost = 50 + (CurrentPlayer->baseLevel * 100);
  gb.display.setColor(ORANGE); 
  gb.display.setCursor(14,44);
  gb.display.println(baseCost);
  
  gb.display.setColor(BLACK);
  gb.display.drawLine(41,43,78,43);  
  gb.display.setColor(ORANGE);
  gb.display.setCursor(43,47);
  gb.display.println("Gd");
  gb.display.setCursor(57,47);
  gb.display.println(CurrentPlayer->funds);
  gb.display.setColor(BLACK);
  gb.display.setCursor(43,54);
  gb.display.println("Lvl");
  gb.display.setCursor(57,54);
  gb.display.println(CurrentPlayer->baseLevel);

  gb.display.drawImage(posY,posX,Pointer);
}

void drawUnitField(int posX,int posY,int unitId,int price)
{
  drawUnit(unitId, 10, posX, posY);
  gb.display.setColor(ORANGE);
  gb.display.setCursor(posX+12,posY+2);
  gb.display.println(price);
}

void drawEndGameScreen()
{
  gb.display.drawImage(0,0,IMAGE_MAIN_THEME);
  gb.display.drawImage(2,1,IMAGE_MENU_THEME,0,0,29,17);
  gb.display.drawImage(29,1,IMAGE_MENU_THEME,1,0,22,17);
  gb.display.drawImage(49,1,IMAGE_MENU_THEME,1,0,29,17);
  gb.display.setCursor(14,8);
  if(CurrentPlayer->id==1)
  {
    gb.display.setColor(RED);
    gb.display.println("PLAYER 1 WINS!");
  }
  else
  {
    gb.display.setColor(BLUE);
    gb.display.println("PLAYER 2 WINS!");
  }
  String strScore="Score: " + (String)CurrentPlayer->points;
  gb.display.setColor(ORANGE);
  gb.display.setCursor(19,44);
  gb.display.println(strScore);
}

void drawHighScoreScreen()
{
  gb.display.drawImage(0,0,IMAGE_MAIN_THEME);
  gb.display.drawImage(2,1,IMAGE_MENU_THEME,0,0,29,17);
  gb.display.drawImage(29,1,IMAGE_MENU_THEME,1,0,22,17);
  gb.display.drawImage(49,1,IMAGE_MENU_THEME,1,0,29,17);
  gb.display.setCursor(19,8);
  gb.display.setColor(BLACK);
  gb.display.println("HIGH SCORES");
  gb.display.setFontSize(1);
  gb.display.setColor(ORANGE);
  for(int i=0;i<5;i++)
  {
    String scoreStr=scoreStrMod(ScoreBoard[i]);
    String index=(String)(i+1);
    scoreStr=index + ". " + scoreStr;
    gb.display.setCursor(20, 22 +(i*6));
    gb.display.println(scoreStr);
  }
  gb.display.setColor(WHITE);  
  gb.display.setCursor(20, 56);
  gb.display.println("BACK");
  gb.display.drawImage(50,54,Pointer);
}

String scoreStrMod(int score)
{
  String result=String(score);
  int count=result.length();
  if(count<6)
  {
    String spaces="";
    for(int i=count;i<=6;i++)
    {
          spaces+=" ";
    }
    result=spaces + result;
  }
  return result;
}

void drawTutorialScreen()
{
  gb.display.setColor(BEIGE); 
  if(Tutorial==0)
  {
    if(TurnCount==0)
    {
      gb.display.setCursor(0, 2);
      gb.display.println("Use arrows to switchmap tiles. Tap A on unit to move it. Taptwice to select     action without move.Tap B to cancel     action.To end turn  tap HOME and select END TURN.");
    }
    else if(TurnCount==1)
    {
      gb.display.setCursor(0, 2);
      gb.display.println("Glowing fields showsunit movement range.It can be reduced byother units or by   terrain restrictions( mountains, sea ).");
    }
    else if(TurnCount==2)
    {
      gb.display.setCursor(0, 2);
      gb.display.println("To attack unit, movenext to it, select  attack action and   point target ( red  fields are attackingunit range ). Tap A to fire.");
    }
    else if(TurnCount==3)
    {
      gb.display.setCursor(0, 2);
      gb.display.println("To capture building,move unit into it   and select capture  action. Tap A to    confirm. This can bedone by Infantry or AT Infantry.");
    }
    else if(TurnCount==4)
    {
      gb.display.setCursor(5, 5);
      gb.display.setColor(GREEN); 
      gb.display.println("MISSION:");
      gb.display.setCursor(0, 15);
      gb.display.setColor(RED); 
      gb.display.println("Capture enemy HQ");
      gb.display.setColor(BEIGE); 
      gb.display.setCursor(0, 30);
      gb.display.println("TIP: Only Infantry  and AT Infantry     can cross mountains and capture building");
    }
  }
  else if(Tutorial==1)
  {
    if(TurnCount==0)
    {
      gb.display.setCursor(0, 2);
      gb.display.println("Mobile Artillery andMobile SSM Units canonly perform one    action at time: MOVEor ATTACK. Those    units cannot defend,but their attacks   are not countered.");
    }
    else if(TurnCount==1)
    {
      gb.display.setCursor(0, 2);
      gb.display.println("Captured building   grants 100 funds    every turn. You can use it to buy new   units in the        captured base.");
    }
    else if(TurnCount==2)
    {
      gb.display.setCursor(0, 2);
      gb.display.println("Tap A on the        captured base to    enter Base Screen.  Select unit you wantto train and tap A  to buy it. Upgrade  your base to unlock stronger units.");
    }
    else if(TurnCount==3)
    {
      gb.display.setCursor(0, 2);
      gb.display.println("Each player can onlyhave max 25 units onthe field. If you   exceed limit, you   won't be able to    recruit new ones.");
    }
    else if(TurnCount==4)
    {
      gb.display.setCursor(5, 5);
      gb.display.setColor(GREEN); 
      gb.display.println("MISSION:");
      gb.display.setCursor(0, 15);
      gb.display.setColor(RED); 
      gb.display.println("Capture 8 buildings.");
    }
  }
  else
  {
    if(TurnCount==0)
    {
      if(GameMode==CONQUEST_MODE)
      {
        gb.display.setCursor(5, 5);
        gb.display.setColor(GREEN); 
        gb.display.println("MISSION:");
        gb.display.setCursor(0, 15);
        gb.display.setColor(RED); 
        gb.display.println("Capture enemy HQ.");
      }
      else
      {
        gb.display.setCursor(5, 5);
        gb.display.setColor(GREEN); 
        gb.display.println("MISSION:");
        gb.display.setCursor(0, 15);
        gb.display.setColor(RED); 
        gb.display.println("Capture 8 buildings.");
      }
    }
  }
  gb.display.setColor(WHITE);  
  gb.display.setCursor(20, 56);
  gb.display.println("CONFIRM");
  gb.display.drawImage(50,54,Pointer);
}
