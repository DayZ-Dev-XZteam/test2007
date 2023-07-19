modded class MissionServer
{
	void MissionServer()
    {
		LCConfig config;
        LootChestsConfig.UpgradeConfig("XZone_Tainiki.json", config);
		LootChestsConfig.LoadConfig("XZone_Tainiki.json", config);
        GetDayZGame().SetLootChestsConfig(config);
		
		if (GetGame().IsServer()) 
        {
		    g_LootChestsManager = null;
            GetLootChestsManager();
        }

    }
}