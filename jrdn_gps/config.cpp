#define _ARMA_

class CfgPatches
{
	class jrdn_gps
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Scripts","DZ_Gear_Camping","DZ_Gear_Navigation","DZ_Radio"};
	};
};

class CfgMods
{
	class jrdn_gps
	{
		dir = "jrdn_gps";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "Jordan's GPS";
		credits = "Jordan";
		author = "Jordan";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game", "World", "Mission"};
		class defs
		{   
            class gameScriptModule
			{
				value = "";
				files[] = {"jrdn_gps/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"jrdn_gps/Scripts/4_World"};
			};
            class missionScriptModule
			{
				value = "";
				files[] = {"jrdn_gps/Scripts/5_Mission"};
			};
		};
	};
};

class CfgVehicles
{
	class ItemBase;
	class Inventory_Base;
	class CableReel: Inventory_Base
	{
		absorbency = 0.5;
		varWetMax = 0.8;
	};
	class Spotlight: Inventory_Base
	{
		absorbency = 0.5;
		varWetMax = 0.8;
	};
	class jrdn_gps_wire: Inventory_Base
	{
		scope = 2;
        displayName = "Wire cuttings";
        descriptionShort = "3 electrical wires crudely cut from a cable reel.";
        model = "jrdn_gps\data\textures\gps_cable\jrdn_gps_cable.p3d";
		repairableWithKits[] = {7,8};
		repairCosts[] = {10.0,15.0};
        weight = 10;
        itemSize[] = {1,2};
		animClass = "Knife";
        absorbency = 0.1;
		varWetMax = 0.8; 
		fragility = 0.001;
		lootCategory = "Crafted";
		itemBehaviour = 1;
        rotationFlags = 17;
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 50;
                    healthLevels[] =
                    {
                        {1.0, {"jrdn_gps\data\textures\gps_cable\jrdn_gps_cable.rvmat"}},
                        {0.7, {"jrdn_gps\data\textures\gps_cable\jrdn_gps_cable.rvmat"}},
                        {0.5, {"jrdn_gps\data\textures\gps_cable\jrdn_gps_cable_damage.rvmat"}},
                        {0.3, {"jrdn_gps\data\textures\gps_cable\jrdn_gps_cable_damage.rvmat"}},
                        {0.0, {"jrdn_gps\data\textures\gps_cable\jrdn_gps_cable_destruct.rvmat"}}
                    };
                };
            };
        };
        soundImpactType = "plastic";
        isMeleeWeapon = 1;
        class MeleeModes
        {
            class Default { ammo = "MeleeSharpLight_4"; range = 1.2; };
            class Heavy   { ammo = "MeleeSharpHeavy_4"; range = 1.2; };
            class Sprint  { ammo = "MeleeSharpHeavy_4"; range = 3.3; };
        };
    };
	class jrdn_gps_pcb: Inventory_Base
	{
		scope = 2;
        displayName = "Salvaged PCB";
        descriptionShort = "A salvaged PCB, looks like it has been taken from some sort of radio. It's marked with the logo of a soviet satellite company.";
        model = "jrdn_gps\data\textures\gps_pcb\jrdn_gps_pcb.p3d";
		repairableWithKits[] = {7,8};
		repairCosts[] = {10.0,15.0};
        weight = 10;
        itemSize[] = {1,2};
		animClass = "Knife";
        absorbency = 0.1;
		varWetMax = 0.8; 
		fragility = 0.001;
		lootCategory = "Crafted";
		itemBehaviour = 1;
        rotationFlags = 17;
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 50;
                    healthLevels[] =
                    {
                        {1.0, {"jrdn_gps\data\textures\gps_pcb\jrdn_gps_pcb.rvmat"}},
                        {0.7, {"jrdn_gps\data\textures\gps_pcb\jrdn_gps_pcb.rvmat"}},
                        {0.5, {"jrdn_gps\data\textures\gps_pcb\jrdn_gps_pcb_damage.rvmat"}},
                        {0.3, {"jrdn_gps\data\textures\gps_pcb\jrdn_gps_pcb_damage.rvmat"}},
                        {0.0, {"jrdn_gps\data\textures\gps_pcb\jrdn_gps_pcb_destruct.rvmat"}}
                    };
                };
            };
        };
        soundImpactType = "plastic";
    };
    class jrdn_gps_wired_pcb: jrdn_gps_pcb
    {
        scope = 2;
        displayName = "Wired PCB";
        descriptionShort = "A wired PCB, it has a strange sticky substance holding the wires together. It's marked with the logo of a soviet satellite company.";
        model = "jrdn_gps\data\textures\gps_wired_pcb\jrdn_gps_wired_pcb.p3d";
		repairableWithKits[] = {7,8};
		repairCosts[] = {10.0,15.0};
        weight = 10;
        itemSize[] = {1,2};
		animClass = "Knife";
        absorbency = 0.1;
		varWetMax = 0.8; 
		fragility = 0.001;
		lootCategory = "Crafted";
		itemBehaviour = 1;
        rotationFlags = 17;
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 50;
                    healthLevels[] =
                    {
                        {1.0, {"jrdn_gps\data\textures\gps_wired_pcb\jrdn_gps_wired_pcb.rvmat"}},
                        {0.7, {"jrdn_gps\data\textures\gps_wired_pcb\jrdn_gps_wired_pcb.rvmat"}},
                        {0.5, {"jrdn_gps\data\textures\gps_wired_pcb\jrdn_gps_wired_pcb_damage.rvmat"}},
                        {0.3, {"jrdn_gps\data\textures\gps_wired_pcb\jrdn_gps_wired_pcb_damage.rvmat"}},
                        {0.0, {"jrdn_gps\data\textures\gps_wired_pcb\jrdn_gps_wired_pcb_destruct.rvmat"}}
                    };
                };
            };
        };
        soundImpactType = "plastic";
    };
    class jrdn_gps_case: Inventory_Base
	{
		scope = 2;
        displayName = "Salvaged GPS Case";
        descriptionShort = "A salvaged GPS Case. It's marked with the logo of a soviet satellite company.";
        model = "jrdn_gps\data\textures\gps_case\jrdn_gps_case.p3d";
		repairableWithKits[] = {7,8};
		repairCosts[] = {10.0,15.0};
        weight = 10;
        itemSize[] = {1,2};
		animClass = "Knife";
		varWetMax = 0.8; 
		fragility = 0.01;
		absorbency = 0.5;
		lootCategory = "Crafted";
		itemBehaviour = 1;
        rotationFlags = 17;
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 50;
                    healthLevels[] =
                    {
                        {1.0, {"jrdn_gps\data\textures\gps_case\jrdn_gps_case.rvmat"}},
                        {0.7, {"jrdn_gps\data\textures\gps_case\jrdn_gps_case.rvmat"}},
                        {0.5, {"jrdn_gps\data\textures\gps_case\jrdn_gps_case_damage.rvmat"}},
                        {0.3, {"jrdn_gps\data\textures\gps_case\jrdn_gps_case_damage.rvmat"}},
                        {0.0, {"jrdn_gps\data\textures\gps_case\jrdn_gps_case_destruct.rvmat"}}
                    };
                };
            };
        };
        soundImpactType = "plastic";
    };
    class Transmitter_Base;
    class PersonalRadio: Transmitter_Base
	{
		absorbency = 0.1;
		varWetMax = 0.8;
	};
    class BaseRadio: Transmitter_Base
	{
		absorbency = 0.1;
		varWetMax = 0.8;
	};
};
