class CfgPatches
{
	class XZone_Tainiki_2023
	{
		requiredAddons[] = {"DZ_Data","DZ_Characters"};
		units[] = {};
		weapons[] = {};
	};
};
class CfgMods
{
	class XZone_Tainiki_2023
	{
		type = "mod";
		author = "Fox";
		dir = "XZone_Tainiki_2023";
		name = "XZone_Tainiki_2023";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				files[] = {"XZone_Tainiki_2023/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				files[] = {"XZone_Tainiki_2023/Scripts/4_World"};
			};
			class missionScriptModule
			{
				files[] = {"XZone_Tainiki_2023/Scripts/5_Mission"};
			};
		};
	};
};
