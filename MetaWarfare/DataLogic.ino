
bool LoadGame()
{
  MapId=0;
  loadMapConfig();
  if(loadMap()==true)
  {
    clearMap();
    //TODO: Load player and map params
    BaseLocation = &None;
    Attacker = &None;
    Defender = &None;
    Player_1.baseLevel = 1;
    Player_1.funds = 0;
    Player_1.totalUnits = 0;
    Player_2.baseLevel = 1;
    Player_2.funds = 0;
    Player_2.totalUnits = 0;
    CurrentPlayer=&Player_1;
    countPlayerStats();
    return true;
  }

  return false;
}

void loadMapConfig()
{
  char RawMapData[9];
  gb.save.get(0, RawMapData);
  String MapConfig(RawMapData);
  MapId = MapConfig.substring(0,5).toInt();
}

bool loadMap()
{
  bool result=false;
  switch(MapId)
  {
    case 1:
    {
      memcpy(CurrentBoard, Board1, sizeof(CurrentBoard));
      result=true;
    }
    break;
    default:
    {
      result=false;
    }
    break;
  }
}

bool clearMap()
{
  for(int i=0;i<16;i++)
  {
    for(int j=0;j<16;j++)
    {
      CurrentBoard[i][j].unitId = 0;
      CurrentBoard[i][j].unitHp = 0;
      CurrentBoard[i][j].player = 0;
      CurrentBoard[i][j].active = 0;
      if(CurrentBoard[i][j].terrainTexture==11 || CurrentBoard[i][j].terrainTexture==12)
      {
        CurrentBoard[i][j].playerBuilding=0;
      }
    }
  }
}

void SaveGame()
{
  if(saveMapConfig()==false)
  {
    gb.gui.popup("ERROR: SAVE MPCON",50);
    return;
  }
  if(savePlayerStats()==false)
  {
    gb.gui.popup("ERROR: SAVE PLSTA",50);
    return;
  }
  if(saveTilesParams()==false)
  {
    return;
  }
  gb.save.set(7,1);
  SaveExist=true;
  gb.gui.popup("GAME SAVED!",50);
}

bool saveMapConfig()
{
  String strData="";
  strData+=returnDecimalStringFive(MapId);
  strData+="2"; //Improve when number of players will change
  strData+=(String)CurrentPlayer->id;
  strData+="0"; //Improve if game mode will change
  strData+=" ";
  if(strData.length()==9)
  {
    saveDataToBlock(0,strData,9);
    return true;
  }
  else
  {
    return false;
  }
}

bool savePlayerStats()
{
  String strData="";
  
  strData+=returnDecimalStringFive(Player_1.funds);
  strData+=(String)Player_1.baseLevel;
  strData+=returnDecimalStringTwo(Player_1.totalUnits);
  strData+=returnDecimalStringFive(Player_1.points);
  
  strData+=returnDecimalStringFive(Player_2.funds);
  strData+=(String)Player_2.baseLevel;
  strData+=returnDecimalStringTwo(Player_2.totalUnits);
  strData+=returnDecimalStringFive(Player_2.points);
  
  strData+=" ";
  if(strData.length()==27)
  {
    saveDataToBlock(1,strData,27);
    return true;
  }
  else
  {
    return false;
  }
}

bool saveTilesParams()
{
  String strDataUnitsId="";
  String strDataUnitsHp="";
  String strDataUnitsOwner="";
  String strDataUnitsStatus="";
  String strBuildingsOwner="";
  
  for(int i=0;i<16;i++)
  {
    for(int j=0;j<16;j++)
    {
      strDataUnitsId += returnDecimalStringTwo(CurrentBoard[i][j].unitId);
      strDataUnitsHp += returnDecimalStringTwo(CurrentBoard[i][j].unitHp);
      strDataUnitsOwner += (String)CurrentBoard[i][j].player;
      strDataUnitsStatus += (String)CurrentBoard[i][j].active;
      strBuildingsOwner += (String)CurrentBoard[i][j].playerBuilding;
    }
  }
  
  strDataUnitsId+=" ";
  strDataUnitsHp+=" ";
  strDataUnitsOwner+=" ";
  strDataUnitsStatus+=" ";
  strBuildingsOwner+=" ";
  
  if(strDataUnitsId.length()==513)
  {
    saveDataToBlock(2,strDataUnitsId,513);
  }
  else
  {
    gb.gui.popup("ERROR: SAVE MPUID",50);
    return false;
  }
  if(strDataUnitsHp.length()==513)
  {
    saveDataToBlock(3,strDataUnitsHp,513);
  }
  else
  {
    gb.gui.popup("ERROR: SAVE MPUHP",50);
    return false;
  }
  if(strDataUnitsOwner.length()==257)
  {
    saveDataToBlock(4,strDataUnitsOwner,257);
  }
  else
  {
    gb.gui.popup("ERROR: SAVE MPUOW",50);
    return false;
  }
  if(strDataUnitsStatus.length()==257)
  {
    saveDataToBlock(5,strDataUnitsStatus,257);
  }
  else
  {
    gb.gui.popup("ERROR: SAVE MPUST",50);
    return false;
  }
  if(strBuildingsOwner.length()==257)
  {
    saveDataToBlock(6,strBuildingsOwner,257);
  }
  else
  {
    gb.gui.popup("ERROR: SAVE MPBOW",50);
    return false;
  }
  return true;
}

void saveDataToBlock(uint16_t block,String data,int bufferSize)
{
  char Buffer[bufferSize];
  data.toCharArray(Buffer,bufferSize);
  gb.save.set(block,Buffer);
}

//---------------HELPERS---------------------------------

String returnDecimalStringTwo(int number)
{
  if(number<100 && number>9)
    return (String)number;
  else if(number>=0)
    return "0" + (String)number;
  else
    return "00";  
}

String returnDecimalStringFive(int number)
{
  if(number<10000 && number>999)
    return "0"+(String)number;
  else if(number<1000 && number>99)
    return "00"+(String)number;
  else if(number<100 && number>9)
    return "000"+(String)number;
  else if(number>=0)
    return "0000" + (String)number;
  else
    return "00000";  
}
