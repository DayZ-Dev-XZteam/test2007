class CJ_LootChests
{
	static Weapon_Base CreateWeaponWithMagazine( string sWeapon, string sMagazine )
	{
	
	    Weapon_Base oWpn = Weapon_Base.Cast(GetGame().CreateObject( sWeapon , "0 0 0" ));
	
	    if ( !oWpn )
	        return NULL;
	
		int stateId = -1;
	
		if ( oWpn.IsInherited( SKS_Base ) )
			return oWpn;
		else if ( oWpn.IsInherited( BoltActionRifle_InnerMagazine_Base ) )
			return oWpn;
		else if ( oWpn.IsInherited( DoubleBarrel_Base ) )
			return oWpn;
		else if ( oWpn.IsInherited( Pistol_Base ) )
			stateId = PistolStableStateID.CLO_DIS_BU0_MA1;
		else if ( oWpn.IsInherited( Repeater_Base ) )
			return oWpn;
		else if ( oWpn.IsInherited( RifleBoltFree_Base ) )
			stateId = RBFStableStateID.RBF_CLO_BU0_MA1;
		else if ( oWpn.IsInherited( RifleBoltLock_Base ) )
			stateId = RBLStableStateID.RBL_OPN_BU0_MA1;
		else if ( oWpn.IsInherited( Mp133Shotgun_Base ) )
			return oWpn;
	
		InventoryLocation mag_il = new InventoryLocation;
		mag_il.SetAttachment( oWpn, NULL, InventorySlots.MAGAZINE );
		Magazine oMag = Magazine.Cast( SpawnEntity( sMagazine, mag_il, ECE_IN_INVENTORY, RF_DEFAULT ) );
	    if ( !oMag )
	        return oWpn;
	    
		GetGame().RemoteObjectDelete( oWpn );
		GetGame().RemoteObjectDelete( oMag );
	    
	
		pushToChamberFromAttachedMagazine( oWpn, oWpn.GetCurrentMuzzle() );
	
		ScriptReadWriteContext ctx = new ScriptReadWriteContext;
		ctx.GetWriteContext().Write( stateId );
		oWpn.LoadCurrentFSMState( ctx.GetReadContext(), GetGame().SaveVersion() );
	

		GetGame().RemoteObjectCreate( oWpn );
		GetGame().RemoteObjectCreate( oMag );
		  
	    return oWpn;
	}
	
	static Weapon_Base CreateWeapon(string predefinedname)
	{
		Weapon_Base weapon;
		ItemBase optic;
		LCConfig config = GetDayZGame().GetLootChestsConfig();
		ref LCPredefinedWeapon wpname;
		
		if ( predefinedname.Contains("LC_predefined") )
		{
					for (int wp = 0; wp < config.LCPredefinedWeapons.Count(); wp++)
				{
					wpname = config.LCPredefinedWeapons.Get(wp);
					if (wpname.defname == predefinedname)
					{
						if (!wpname.magazine)
						{
							weapon = Weapon_Base.Cast(GetGame().CreateObject( wpname.weapon , "0 0 0" ));
						} else {
							weapon = CreateWeaponWithMagazine( wpname.weapon, wpname.magazine );
						}
						if (wpname.attachments.Count()>0 )
						{
							for (int attch = 0; attch < wpname.attachments.Count(); attch++)
							{
								weapon.GetInventory().CreateAttachment( wpname.attachments.Get(attch) );
							}	
						}
						if (wpname.optic !="")
						{
							optic = weapon.GetInventory().CreateAttachment( wpname.optic );
							if (wpname.opticbattery == true	)
							{
								optic.GetInventory().CreateAttachment("Battery9V");
							}
						}
					//LCLogger.Log("predefined weapon " + weapon);
					
					return weapon;	
					}
						
				}
		}
		
		weapon = Weapon_Base.Cast(GetGame().CreateObject( predefinedname , "0 0 0" ));

		return weapon;
		
	}
	
	static void FillLootChest(EntityAI lootchestContainer)
	{
		string itemtesting;
		Weapon_Base oWpn1;
		ItemBase optic;
		TStringArray items;
		ref LootChestsPlace m_LootChestsPlace;
		LCConfig config = GetDayZGame().GetLootChestsConfig();
		float lootrand = config.LootRandomization;
		int endlocation = config.LootChestsLocations.Count() - 1;
		int rndLoot = Math.RandomInt(0, endlocation );
		rndLoot = Math.RandomInt(0, endlocation );
		for (int i = 0; i < config.LootChestsLocations.Count(); i++)
		{
			m_LootChestsPlace = config.LootChestsLocations.Get(i);
			if (i == rndLoot )
			{
				items = m_LootChestsPlace.loot;
			}
		}
		
		ref LCPredefinedWeapon wpname;
		float rand;
		int randi;
		int j;
		InventoryLocation wpn_il = new InventoryLocation;
		string randwpn;	
		lootchestContainer.GetInventory();
		
		for( i = 0; i < items.Count(); i++)
		    {
				itemtesting = items.Get(i);
				if ( itemtesting.Contains("LC_Table") )
				{
					
					switch (itemtesting)
					{
						case "LC_Table_Weapons_Police":
							//LCLogger.Log("nahodna pistol " + config.LootCategories.Get(0).Loot.GetRandomElement());
							randwpn = config.LootCategories.Get(0).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(0).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING WEAPON : " + oWpn1);
						break;
						
						case "LC_Table_Weapons_Army":
							randwpn = config.LootCategories.Get(1).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(1).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING WEAPON : " + oWpn1);
						break;
						
						case "LC_Table_Ammo_Police":
							randwpn = config.LootCategories.Get(2).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(2).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING AMMUNITION : " + oWpn1);
						break;
						
						case "LC_Table_Ammo_Army":
							randwpn = config.LootCategories.Get(3).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(3).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING AMMUNITION : " + oWpn1);
						break;
						
						case "LC_Table_Magazines_Police":
							randwpn = config.LootCategories.Get(4).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(4).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING MAGAZINE : " + oWpn1);
						break;
						
						case "LC_Table_Magazines_Army":
							randwpn = config.LootCategories.Get(5).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(5).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING MAGAZINE : " + oWpn1);
						break;
						
						case "LC_Table_Attachments_Police":
							randwpn = config.LootCategories.Get(6).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(6).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING ATTACHMENT : " + oWpn1);
						break;
						
						case "LC_Table_Attachments_Army":
							randwpn = config.LootCategories.Get(7).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(7).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING ATTACHMENT : " + oWpn1);
						break;
						
						case "LC_Table_Gear_Police":
							randwpn = config.LootCategories.Get(8).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(8).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING GEAR : " + oWpn1);
						break;
						
						case "LC_Table_Gear_Army":
							randwpn = config.LootCategories.Get(9).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(9).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING GEAR : " + oWpn1);
						break;
						
						case "LC_Table_Extra":
							randwpn = config.LootCategories.Get(10).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(10).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING SPECIAL LOOT : " + oWpn1);
						break;		
						
						case "LC_Table_Safe_Lvl1":
							randwpn = config.LootCategories.Get(11).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(11).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING SPECIAL LOOT : " + oWpn1);
						break;			
						
						case "LC_Table_Safe_Lvl2":
							randwpn = config.LootCategories.Get(12).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(12).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING SPECIAL LOOT : " + oWpn1);
						break;		
						
						case "LC_Table_Safe_Lvl3":
							randwpn = config.LootCategories.Get(13).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(13).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING SPECIAL LOOT : " + oWpn1);
						break;		
						
						case "LC_Table_Safe_Lvl4":
							randwpn = config.LootCategories.Get(14).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(14).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING SPECIAL LOOT : " + oWpn1);
						break;		
						
						case "LC_Table_Safe_Lvl5":
							randwpn = config.LootCategories.Get(15).Loot.GetRandomElement();
							oWpn1 = CreateWeapon( config.LootCategories.Get(15).Loot.GetRandomElement() );
							//LCLogger.Log("THIS CRATE GET FOLLOWING SPECIAL LOOT : " + oWpn1);
						break;
					}
					oWpn1.Update();
					lootchestContainer.GetInventory().AddEntityToInventory(oWpn1);
				} else if (itemtesting.Contains("LC_predefined")) {
					
					
					oWpn1 = CreateWeapon(itemtesting);
					oWpn1.Update();
					lootchestContainer.GetInventory().AddEntityToInventory(oWpn1);
		
				} else {
					
					rand = Math.RandomFloatInclusive(0.0, 1.0);
					if (rand > lootrand)
					{
						
						lootchestContainer.GetInventory().CreateEntityInCargo(items.Get(i));
						
					}
					
				}
						
			}
		
		lootchestContainer.GetInventory();
		
		
	}
	
	static void CreateLootChest(vector position, vector rotation, TStringArray items, string containertype, float lootrand)
	{
	EntityAI lootchestContainer = EntityAI.Cast(GetGame().CreateObject(containertype, position)); //CreateObjectEx
	string itemtesting;
	Weapon_Base oWpn1;
	ItemBase optic;
	LCConfig config = GetDayZGame().GetLootChestsConfig();
	ref LCPredefinedWeapon wpname;
	float rand;
	int randi;
	int j;
	InventoryLocation wpn_il = new InventoryLocation;
	string randwpn;	
	lootchestContainer.GetInventory();
		
	for(int i = 0; i < items.Count(); i++)
	    {
			itemtesting = items.Get(i);
			if ( itemtesting.Contains("LC_Table") )
			{
				
				switch (itemtesting)
				{

					case "LC_Table_Weapons_Army":
						randwpn = config.LootCategories.Get(0).Loot.GetRandomElement();
						oWpn1 = CreateWeapon( config.LootCategories.Get(1).Loot.GetRandomElement() );
						lootchestContainer.GetInventory().AddEntityToInventory(oWpn1);
					break;
					case "LC_Table_Weapons_Police":
						randwpn = config.LootCategories.Get(1).Loot.GetRandomElement();
						oWpn1 = CreateWeapon( config.LootCategories.Get(0).Loot.GetRandomElement() );
						lootchestContainer.GetInventory().AddEntityToInventory(oWpn1);
					break;
					case "LC_Table_Ammo_Police":
						randwpn = config.LootCategories.Get(2).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(2).Loot.GetRandomElement() );
					break;
					
					case "LC_Table_Ammo_Army":
						randwpn = config.LootCategories.Get(3).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(3).Loot.GetRandomElement() );
					break;
					
					case "LC_Table_Magazines_Police":
						randwpn = config.LootCategories.Get(4).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(4).Loot.GetRandomElement() );
					break;
					
					case "LC_Table_Magazines_Army":
						randwpn = config.LootCategories.Get(5).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(5).Loot.GetRandomElement() );
					break;
					
					case "LC_Table_Attachments_Police":
						randwpn = config.LootCategories.Get(6).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(6).Loot.GetRandomElement() );
					break;
					
					case "LC_Table_Attachments_Army":
						randwpn = config.LootCategories.Get(7).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(7).Loot.GetRandomElement() );
					break;
					
					case "LC_Table_Gear_Police":
						randwpn = config.LootCategories.Get(8).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(8).Loot.GetRandomElement() );
					break;
					
					case "LC_Table_Gear_Army":
						randwpn = config.LootCategories.Get(9).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(9).Loot.GetRandomElement() );
					break;
					
					case "LC_Table_Extra":
						randwpn = config.LootCategories.Get(10).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(10).Loot.GetRandomElement() );
					break;	
					
					case "LC_Table_Safe_Lvl1":
						randwpn = config.LootCategories.Get(11).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(11).Loot.GetRandomElement() );
					break;	
					
					case "LC_Table_Safe_Lvl2":
						randwpn = config.LootCategories.Get(12).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(12).Loot.GetRandomElement() );
					break;	
					
					case "LC_Table_Safe_Lvl3":
						randwpn = config.LootCategories.Get(13).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(13).Loot.GetRandomElement() );
					break;	
					
					case "LC_Table_Safe_Lvl4":
						randwpn = config.LootCategories.Get(14).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(14).Loot.GetRandomElement() );
					break;	
					
					case "LC_Table_Safe_Lvl5":
						randwpn = config.LootCategories.Get(15).Loot.GetRandomElement();
						lootchestContainer.GetInventory().CreateEntityInCargo( config.LootCategories.Get(15).Loot.GetRandomElement() );
					break;	
				}

				
			} else if (itemtesting.Contains("LC_predefined")) {
				
				
				oWpn1 = CreateWeapon(itemtesting);
				LCLogger.Log("fill predefined weapon " + oWpn1);
				lootchestContainer.GetInventory().AddEntityToInventory(oWpn1);
	
			} else {
				
				rand = Math.RandomFloatInclusive(0.0, 1.0);
				if (rand > lootrand)
				{
					
					lootchestContainer.GetInventory().CreateEntityInCargo(items.Get(i));
					
				}
				
			}
					
		}
	
	lootchestContainer.GetInventory();
	lootchestContainer.SetOrientation(rotation);

	}
}
