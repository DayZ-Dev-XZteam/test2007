class LootChestsPlace
{
    string name;
	int number;
	ref TStringArray pos;
    string chest;
	ref TStringArray loot;

    void LootChestsPlace(string nam, int num, ref TStringArray xz, string cont, ref TStringArray lt) 
	{
        name = nam;
		number = num;
		pos = xz;
		chest = cont;
		loot = lt; 
    }
}

class LCLootCategory
{
    string name;
    ref TStringArray Loot;

    void LCLootCategory( string nam, ref TStringArray loot )
    {
        name = nam;
        Loot = loot;
    }
}

class LCPredefinedWeapon
{
	string defname;
	string weapon;
	string magazine;
	ref TStringArray attachments;
	string optic;
	bool opticbattery;
	
	void LCPredefinedWeapon( string def, string weap, string mag, ref TStringArray att, string opt, bool batt)
	{
		defname = def;
		weapon = weap;
		magazine = mag;
		attachments = att;
		optic = opt;
		opticbattery = batt;
	}
	
}

class LCConfig
{
	// udelat kategorie
	float LootRandomization;
	ref array< ref LootChestsPlace > LootChestsLocations;
	ref array< ref LCPredefinedWeapon > LCPredefinedWeapons;
	ref array< ref LCLootCategory > LootCategories;
	void LCConfig()
	{
		LootChestsLocations = new ref array< ref LootChestsPlace >;
		LCPredefinedWeapons = new ref array< ref LCPredefinedWeapon >;
		LootCategories = new ref array< ref LCLootCategory >;
	}

}

class LootChestsConfig
{

    protected const static string m_ConfigRoot = "$profile:\\XZone_Tainiki\\";

    static void LoadConfig(string configName, out LCConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(configPath))
        {
            LCLogger.Log("'" + configName + "'конфигурации не существует, создание конфигурации по умолчанию");
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }

        JsonFileLoader<LCConfig>.JsonLoadFile(configPath, configData);
        LCLogger.Log("'" + configName + "' найдено, загружается существующий конфиг");

    }

    protected static void SaveConfig(string configName, LCConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(m_ConfigRoot))
        {
            LCLogger.Log("'" + m_ConfigRoot + "' не существует, создание каталога");
            MakeDirectory(m_ConfigRoot);
        }

        JsonFileLoader<LCConfig>.JsonSaveFile(configPath, configData);
    }
	
	static void UpgradeConfig(string configName, out LCConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(configPath))
        {
            LCLogger.Log("'"  + configName + "' не существует, создание конфигурации по умолчанию");
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }
		JsonFileLoader<LCConfig>.JsonLoadFile(configPath, configData);
		
		//upgrades...
			
        JsonFileLoader<LCConfig>.JsonSaveFile(configPath, configData);
    }

    protected static void CreateDefaultConfig(out LCConfig configData)
    {
        configData = new LCConfig();
		configData.LootRandomization = 0.5;
		configData.LootChestsLocations.Insert( new ref LootChestsPlace("Мёртвый город", 1, { "2670.465576 136.427200 8302.381836|75 0 0"}, "Fox_boX", {"Hammer",  "NailBox", "NailBox", "NailBox", "CombatKnife", "Rags", "HandSaw", "Hammer"} ) );
		configData.LootChestsLocations.Insert( new ref LootChestsPlace("Янтарь", 1, {"2672.859375 136.427200 8337.175781|-15 0 0"}, "Fox_boX", {"BandageDressing", "NVGHeadstrap", "TTSKOPants", "TTsKOJacket_Camo", "TacticalBaconCan", "NVGoggles" ,"Mag_SVD_10Rnd", "Mag_SVD_10Rnd", "LC_predefined_SVD"} ) );
		configData.LootChestsLocations.Insert( new ref LootChestsPlace("Свалка", 1, {"2746.794189 136.435760 8265.651367|-105 0 0"}, "Fox_boX", {"LC_predefined_AKM", "Mag_AKM_30Rnd", "Mag_AKM_30Rnd", "Mag_AKM_30Rnd", "LC_predefined_AK74", "Mag_AK74_30Rnd", "Mag_AK74_30Rnd", "AmmoBox_545x39_20Rnd", "AmmoBox_545x39_20Rnd", "AmmoBox_545x39_20Rnd", "AmmoBox_762x39_20Rnd", "AmmoBox_762x39_20Rnd", "AmmoBox_762x39_20Rnd", "AmmoBox_762x39_20Rnd", "AmmoBox_762x39_20Rnd", "BandageDressing", "WeaponCleaningKit"} ) );
		configData.LootChestsLocations.Insert( new ref LootChestsPlace("Агропром", 1, { "2670.465576 136.427200 8302.381836|75 0 0"}, "Fox_boX", {"Hammer",  "NailBox", "NailBox", "NailBox", "CombatKnife", "Rags", "HandSaw", "Hammer"} ) );
		configData.LootChestsLocations.Insert( new ref LootChestsPlace("Болото", 1, { "2670.465576 136.427200 8302.381836|75 0 0"}, "Fox_boX", {"Hammer",  "NailBox", "NailBox", "NailBox", "CombatKnife", "Rags", "HandSaw", "Hammer"} ) );
		
		configData.LCPredefinedWeapons.Insert(new ref LCPredefinedWeapon("LC_predefined_SVD", "SVD", "Mag_SVD_10Rnd", { "AK_Suppressor" }, "PSO11Optic", true ));
		configData.LCPredefinedWeapons.Insert(new ref LCPredefinedWeapon("LC_predefined_VSS", "VSS", "Mag_VSS_10Rnd", { "AK_Suppressor" }, "PSO11Optic", true ));
		configData.LCPredefinedWeapons.Insert(new ref LCPredefinedWeapon("LC_predefined_Tundra", "Winchester70", "", { "" }, "HuntingOptic", false ));
		configData.LCPredefinedWeapons.Insert(new ref LCPredefinedWeapon("LC_predefined_Blaze", "B95", "", { "" }, "HuntingOptic", false ));
		configData.LCPredefinedWeapons.Insert(new ref LCPredefinedWeapon("LC_predefined_M4", "M4A1", "Mag_STANAG_30Rnd", { "M4_Suppressor", "M4_RISHndgrd_Black" ,"M4_MPBttstck_Black" }, "ACOGOptic", false ));
		configData.LCPredefinedWeapons.Insert(new ref LCPredefinedWeapon("LC_predefined_SKS", "SKS", "", { "" }, "PUScopeOptic", false ));
		configData.LCPredefinedWeapons.Insert(new ref LCPredefinedWeapon("LC_predefined_CZ527", "CZ527", "Mag_CZ527_5rnd", { "" }, "HuntingOptic", false ));
		configData.LCPredefinedWeapons.Insert(new ref LCPredefinedWeapon("LC_predefined_AKM", "AKM", "Mag_AKM_30Rnd", { "AK_Suppressor", "AK_WoodHndgrd" ,"AK_WoodBttstck" }, "PSO11Optic", true ));
		configData.LCPredefinedWeapons.Insert(new ref LCPredefinedWeapon("LC_predefined_AK74", "AK74", "Mag_AK74_30Rnd", { "AK_Suppressor", "AK74_Hndgrd", "AK74_WoodBttstck" }, "PSO11Optic", true ));
		configData.LCPredefinedWeapons.Insert(new ref LCPredefinedWeapon("LC_predefined_AK101", "AK101", "Mag_AK101_30Rnd", { "AK_Suppressor", "AK_PlasticHndgrd", "AK_PlasticBttstck" }, "PSO11Optic", true ));
		configData.LCPredefinedWeapons.Insert(new ref LCPredefinedWeapon("LC_predefined_FAL", "FAL", "Mag_FAL_20Rnd", { "Fal_OeBttstck" }, "ACOGOptic", false ));
		
		configData.LootCategories.Insert(new ref LCLootCategory("LC_Table_Pistols", { "LC_predefined_Glock19", "LC_predefined_M1911", "LC_predefined_IJ70", "Glock19", "M1911", "IJ70"} ));
		configData.LootCategories.Insert(new ref LCLootCategory("LC_Table_Rifles", { "LC_predefined_M4A1", "LC_predefined_AKM", "LC_predefined_MP5K"} ));

	}
}
