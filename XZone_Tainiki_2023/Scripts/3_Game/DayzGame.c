modded class DayZGame
{	
	protected ref LCConfig m_LootChestsConfig;

	
    void SetLootChestsConfig(LCConfig config)
    {
        m_LootChestsConfig = config;
    }

    LCConfig GetLootChestsConfig()
    {
		return m_LootChestsConfig;
    }
};