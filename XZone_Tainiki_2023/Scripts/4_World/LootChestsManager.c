static ref LootChestsManager g_LootChestsManager;
static ref LootChestsManager GetLootChestsManager()
{
    if ( !g_LootChestsManager )
    {
         g_LootChestsManager = new ref LootChestsManager();
    }
    
    return g_LootChestsManager;
}
class LootChestsManager
{
	void LootChestsManager()
	{

		LCConfig config = GetDayZGame().GetLootChestsConfig();
		
		for(int i = 0; i < config.LootChestsLocations.Count(); i++)
		{
			string chestclass = config.LootChestsLocations.Get(i).chest;
			TStringArray positions =  config.LootChestsLocations.Get(i).pos;
			TStringArray loot = config.LootChestsLocations.Get(i).loot;
			int chestnum = config.LootChestsLocations.Get(i).number;
			if (chestnum <= positions.Count())
			{

				for (int j = 0; j< chestnum; j++)
				{

					int rndnum = Math.RandomIntInclusive(0, positions.Count() - 1);

					string posrot = positions.Get(rndnum);
					TStringArray loc = new TStringArray;
					posrot.Split( "|", loc );
					string pos = loc.Get(0);
					string rot = loc.Get(1);
					
					float lootrand = config.LootRandomization;
					
					CJ_LootChests.CreateLootChest( pos.ToVector(), rot.ToVector() , loot, chestclass, lootrand);
					LCLogger.Log("Created LootChest " + chestclass + " at " + pos);
					positions.RemoveOrdered(rndnum);
					
				}
			}

		}
		
	}
	
}