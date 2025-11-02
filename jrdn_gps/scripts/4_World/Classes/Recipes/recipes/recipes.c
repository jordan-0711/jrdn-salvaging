void TestSettings()
{
    float test = jrdn_settings.cut.baseChance;
    Print("Settings test: " + test);
}

class salvageWires extends RecipeBase
{
	override void Init()
	{
		// -------------------------------------------------------------------------------------------------
		// Common
		// -------------------------------------------------------------------------------------------------
		m_Name = "Cut wires";
		m_IsInstaRecipe = false;					// should this recipe be performed instantly without animation
		m_AnimationLength = 2;						// animation length in relative time units
		m_Specialty = 0;							// relates to the soft skills stats for players - recommended not to change

		// -------------------------------------------------------------------------------------------------
		// Conditions
		// -------------------------------------------------------------------------------------------------
		m_MinDamageIngredient[0]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[0] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[0]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[0] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[0]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[0]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.
		m_MinDamageIngredient[1]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[1] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[1]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[1] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[1]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[1]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.

		// -------------------------------------------------------------------------------------------------
		// Ingredient 1
		// -------------------------------------------------------------------------------------------------
		// PreferredTools
		InsertIngredient(0, "SteakKnife");
		InsertIngredient(0, "KitchenKnife");
		InsertIngredient(0, "CombatKnife");
		InsertIngredient(0, "HuntingKnife");
		InsertIngredient(0, "Cleaver");
		InsertIngredient(0, "AK_Bayonet");
		InsertIngredient(0, "M9A1_Bayonet");
		InsertIngredient(0, "SNAFU_Kabar");
		InsertIngredient(0, "Msp_VorpalKnife");
		InsertIngredient(0, "KukriKnife");
		InsertIngredient(0, "FangeKnife");
		InsertIngredient(0, "Mosin_Bayonet");
		InsertIngredient(0, "SNAFU_SKS_Bayonet");
		InsertIngredient(0, "Machete");
		InsertIngredient(0, "CrudeMachete");
		InsertIngredient(0, "OrientalMachete");
		// NotPreferredTools
		InsertIngredient(0, "Hatchet");
		InsertIngredient(0, "WoodAxe");
		InsertIngredient(0, "FirefighterAxe");
		InsertIngredient(0, "FirefighterAxe_Black");
		InsertIngredient(0, "FirefighterAxe_Green");
		InsertIngredient(0, "Pickaxe");
		InsertIngredient(0, "Iceaxe");
		InsertIngredient(0, "HandSaw");
		InsertIngredient(0, "Hacksaw");
		InsertIngredient(0, "Sword");

		m_IngredientAddHealth[0] = -10;// 0 = do nothing
        m_IngredientSetHealth[0] = -1; // -1 = do nothing
        m_IngredientAddQuantity[0] = 0;// 0 = do nothing
        m_IngredientDestroy[0] = false;//true = destroy, false = do nothing
        m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this ingredient


		// -------------------------------------------------------------------------------------------------
		// Ingredient 2
		// -------------------------------------------------------------------------------------------------
		InsertIngredient(1,"Spotlight");
		InsertIngredient(1,"CableReel");
		m_IngredientAddHealth[1] = 0;// 0 = do nothing
        m_IngredientSetHealth[1] = -1; // -1 = do nothing
        m_IngredientAddQuantity[1] = -1;// 0 = do nothing
        m_IngredientDestroy[1] = true;//true = destroy, false = do nothing
        m_IngredientUseSoftSkills[1] = false;// set 'true' to allow modification of the values by softskills on this 


		// -------------------------------------------------------------------------------------------------
		// Result
		// -------------------------------------------------------------------------------------------------
        AddResult("jrdn_gps_wire");//add results here
        m_ResultSetFullQuantity[0] = false;//true = set full quantity, false = do nothing
        m_ResultSetQuantity[0] = -1;//-1 = do nothing
        m_ResultSetHealth[0] = -1;//-1 = do nothing
        m_ResultInheritsHealth[0] = 0;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
        m_ResultInheritsColor[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
        m_ResultToInventory[0] = -2;//(value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
        m_ResultUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this result
        m_ResultReplacesIngredient[0] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
	}
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return true;
	}
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		super.Do(ingredients, player, results, specialty_weight);

		if (!GetGame() || !GetGame().IsServer())
			return;

		ItemBase tool   = ingredients[0];
		ItemBase target = ingredients[1];

		array<ItemBase> wet_sources = new array<ItemBase>;
		wet_sources.Insert(target);

		jrdnWetInfo env = new jrdnWetInfo;
		jrdn_helpers.buildWetInfo(wet_sources, env); // env.wet, env.wetThreshold ready

		// preferred tools for this recipe (same list)
		array<toolCategory> preferredTools = new array<toolCategory>;
		preferredTools.Insert(toolCategory.TOOL_SMALL_BLADE);
		preferredTools.Insert(toolCategory.TOOL_LARGE_BLADE);

		// === Cut risk (same logic, safer syntax for Enforce) ===
if (env.wet >= env.wetThreshold)
{
    // Inline PunishCut logic
    float baseChance = jrdn_settings.cut.baseChance;
    float wetnessScale = jrdn_settings.cut.wetnessScale;
    float healthPenaltyAbs = jrdn_settings.cut.healthPenaltyAbs;
    float preferredMultiplier = jrdn_settings.tools.preferredMul;
    float notPreferredMultiplier = jrdn_settings.tools.notPreferredMul;
    
    if (baseChance < 0.0) baseChance = 0.0;
    if (baseChance > 1.0) baseChance = 1.0;
    if (wetnessScale < 0.0) wetnessScale = 0.0;
    
    float wet = env.wet;
    if (wet < 0.0) wet = 0.0;
    if (wet > 1.0) wet = 1.0;
    if (healthPenaltyAbs < 0.0) healthPenaltyAbs = 0.0;
    
    toolCategory usedCategory;
    float toolMul = jrdn_helpers.ToolRiskMultiplier(tool, preferredTools, preferredMultiplier, notPreferredMultiplier, usedCategory);
    
    float gloveMitigation;
    ItemBase gloveItem;
    bool hasGloves = jrdn_helpers.HasGloveProtection(player, gloveMitigation, gloveItem);
    if (!hasGloves) gloveMitigation = 0.0;
    if (gloveMitigation < 0.0) gloveMitigation = 0.0;
    if (gloveMitigation > 1.0) gloveMitigation = 1.0;
    
    float finalChance = baseChance * (1.0 + (wet * wetnessScale));
    finalChance = finalChance * toolMul;
    finalChance = finalChance * (1.0 - gloveMitigation);
    if (finalChance > 1.0) finalChance = 1.0;
    
    float finalDamage = healthPenaltyAbs * toolMul * (1.0 - gloveMitigation);
    
    float roll = Math.RandomFloat(0.0, 1.0);
    bool didCut = false;
    if (roll <= finalChance)
    {
        if (finalDamage > 0.0) player.AddHealth("", "", -finalDamage);
        if (GetGame() && GetGame().IsServer()) jrdn_helpers.DropItemInHands(player);
        didCut = true;
    }
    
    if (didCut)
    {
        toolCategory usedCat = GetToolCategory(tool);
        string usedSelection;
        jrdn_helpers.TryApplyBleedForTool(player, usedCat, usedSelection);
    }
}

		// === Result penalties (same behavior the wrapper applied) ===
		// Compute wrong-tool status
		toolCategory usedCatTmp;
		bool isPreferred = jrdn_helpers.IsPreferredTool(tool, preferredTools, usedCatTmp);

		// Wet penalty (manual clamp like before; NO Math.Clamp here)
		float wetPenaltyAbs = 0.0;
		if (env.wet >= env.wetThreshold)
		{
			float tmp = env.wet * jrdn_settings.result.wetPenaltyScale;
			if (tmp < 0.0) tmp = 0.0;
			float maxP = jrdn_settings.result.wetPenaltyMax;
			if (tmp > maxP) tmp = maxP;
			wetPenaltyAbs = tmp;
		}

		// Wrong-tool flat penalty
		float wrongToolPenalty;
		if (isPreferred)
		{
			wrongToolPenalty = 0.0;
		}
		else
		{
			wrongToolPenalty = jrdn_settings.result.wrongToolPenaltyAbs;
		}

		// Apply to all result items (powerType=0 for this recipe)
		jrdn_DbgPenalty("Result penalties: wet=" + env.wet + " wetPenalty=" + wetPenaltyAbs + " wrongToolCheck=" + (!isPreferred) + " powerType=0");

		if (results)
		{
			for (int ri = 0; ri < results.Count(); ri++)
			{
				ItemBase r = results[ri];
				if (!r) continue;

				float curH = r.GetHealth("", "");
				float deltaTotal = wetPenaltyAbs + wrongToolPenalty /* + 0.0 poweredPenaltyAbs */;
				float newH = curH - deltaTotal;
				if (newH < 0.0) newH = 0.0;

				r.SetHealth("", "", newH);
			}
			jrdn_DbgPenalty("Result penalty applied to " + results.Count() + " item(s)");
		}

		// write wetness back to the result placeholder
		if (results && results.Count() > 0)
		{
			array<ItemBase> resArr = new array<ItemBase>;
			resArr.Insert(results[0]);
			jrdn_helpers.ApplyWet(resArr, env.wet);
		}
	}


};
class salvagePCBCasing extends RecipeBase
{
	override void Init()
	{
		// -------------------------------------------------------------------------------------------------
		// Common
		// -------------------------------------------------------------------------------------------------
		m_Name = "Salvage GPS parts";
		m_IsInstaRecipe = false;					// should this recipe be performed instantly without animation
		m_AnimationLength = 2;						// animation length in relative time units
		m_Specialty = 0;							// relates to the soft skills stats for players - recommended not to change
		//----------------------------------------------------------------------------------------------------------------------

		// -------------------------------------------------------------------------------------------------
		// Conditions
		// -------------------------------------------------------------------------------------------------
		m_MinDamageIngredient[0]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[0] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[0]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[0] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[0]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[0]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.
		m_MinDamageIngredient[1]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[1] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[1]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[1] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[1]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[1]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.

		// -------------------------------------------------------------------------------------------------
		// Ingredient 1
		// -------------------------------------------------------------------------------------------------
		// PreferredTools
		InsertIngredient(0, "Screwdriver");
		InsertIngredient(0, "Crowbar");
		InsertIngredient(0, "Pliers");

		// NotPreferredTools
		InsertIngredient(0, "SteakKnife");
		InsertIngredient(0, "KitchenKnife");
		InsertIngredient(0, "CombatKnife");
		InsertIngredient(0, "HuntingKnife");
		InsertIngredient(0, "Cleaver");
		InsertIngredient(0, "AK_Bayonet");
		InsertIngredient(0, "M9A1_Bayonet");
		InsertIngredient(0, "SNAFU_Kabar");
		InsertIngredient(0, "Msp_VorpalKnife");
		InsertIngredient(0, "KukriKnife");
		InsertIngredient(0, "FangeKnife");
		InsertIngredient(0, "Mosin_Bayonet");
		InsertIngredient(0, "SNAFU_SKS_Bayonet");
		InsertIngredient(0, "Machete");
		InsertIngredient(0, "CrudeMachete");
		InsertIngredient(0, "OrientalMachete");
		InsertIngredient(0, "Hatchet");
		InsertIngredient(0, "WoodAxe");
		InsertIngredient(0, "FirefighterAxe");
		InsertIngredient(0, "FirefighterAxe_Black");
		InsertIngredient(0, "FirefighterAxe_Green");
		InsertIngredient(0, "Pickaxe");
		InsertIngredient(0, "Iceaxe");
		InsertIngredient(0, "HandSaw");
		InsertIngredient(0, "Hacksaw");
		InsertIngredient(0, "Sword");
		m_IngredientAddHealth[0] = 0;// 0 = do nothing
        m_IngredientSetHealth[0] = -1; // -1 = do nothing
        m_IngredientAddQuantity[0] = -1;// 0 = do nothing
        m_IngredientDestroy[0] = false;//true = destroy, false = do nothing
        m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this 

		// -------------------------------------------------------------------------------------------------
		// Ingredient 2
		// -------------------------------------------------------------------------------------------------
		InsertIngredient(1, "BaseRadio");
		InsertIngredient(1, "PersonalRadio");
		m_IngredientAddHealth[1] = -10;// 0 = do nothing
        m_IngredientSetHealth[1] = -1; // -1 = do nothing
        m_IngredientAddQuantity[1] = 0;// 0 = do nothing
        m_IngredientDestroy[1] = true;//true = destroy, false = do nothing
        m_IngredientUseSoftSkills[1] = false;// set 'true' to allow modification of the values by softskills on this ingredient

		// -------------------------------------------------------------------------------------------------
		// Result
		// -------------------------------------------------------------------------------------------------
        AddResult("jrdn_gps_pcb");//add results here
        m_ResultSetFullQuantity[0] = false;//true = set full quantity, false = do nothing
        m_ResultSetQuantity[0] = -1;//-1 = do nothing
        m_ResultSetHealth[0] = -1;//-1 = do nothing
        m_ResultInheritsHealth[0] = 1;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
        m_ResultInheritsColor[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
        m_ResultToInventory[0] = -2;//(value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
        m_ResultUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this result
        m_ResultReplacesIngredient[0] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
	}
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return true;
	}
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		super.Do(ingredients, player, results, specialty_weight);

		if (!GetGame() || !GetGame().IsServer())
			return;

		ItemBase tool   = ingredients[0];
		ItemBase target = ingredients[1];

		// 1) Build result pool and pick a class
		TStringArray resultPool = new TStringArray;
		resultPool.Insert("jrdn_gps_pcb");
		resultPool.Insert("jrdn_gps_case");
		resultPool.Insert("jrdn_gps_wired_pcb");

		string pickedClass;
		jrdn_helpers.RandomResults_Single(resultPool, pickedClass);
		if (pickedClass == "")
			return;

		// 2) Build wetness context from the TARGET item
		array<ItemBase> inheritWetFrom = new array<ItemBase>;
		inheritWetFrom.Insert(target);

		jrdnWetInfo env = new jrdnWetInfo;
		jrdn_helpers.buildWetInfo(inheritWetFrom, env); // env.wet, env.wetThreshold ready

		// 3) Preferred tools (same categories for electronics work)
		array<toolCategory> preferredTools = new array<toolCategory>;
		preferredTools.Insert(toolCategory.TOOL_UTILITY_SCREW);
		preferredTools.Insert(toolCategory.TOOL_UTILITY_WRENCH);

		// 3b) Compute wrong-tool status for result penalties later
		toolCategory usedCatTmp2;
		bool isPreferred2 = jrdn_helpers.IsPreferredTool(tool, preferredTools, usedCatTmp2);

		// 4) Spawn final result at feet with inheritance (unchanged)
		ItemBase finalResult = jrdn_helpers.KeepOrSpawnRandomResult(pickedClass, results, player, "", inheritWetFrom, target);
		if (!finalResult)
			return;

		// 5) Power detection + SHOCK (direct core call)
		ItemBase foundPower;
		int powerType = jrdn_helpers.DetectPoweredIngredient(target, foundPower);
		if (powerType > 0)
		{
			bool isCarType = false;
			if (powerType == 2) isCarType = true;
			if (powerType == 3) isCarType = true;

			float base9V = jrdn_settings.power.base9V;
			float baseCar = jrdn_settings.power.baseCar;
			float baseTruck = jrdn_settings.power.baseTruck;
			float prefMul = jrdn_settings.tools.preferredMul;
			float notPrefMul = jrdn_settings.tools.notPreferredMul;
			float mismatchOffset = jrdn_settings.tools.notPreferredFixed;

			jrdn_helpers.PunishShock(player, env.wet, powerType, tool, preferredTools, isCarType, base9V, baseCar, baseTruck, prefMul, notPrefMul, mismatchOffset);

		}

		// 6) Result penalties (wet + wrong-tool + power), same as wrapper behavior

		// Wet penalty (use Math.Clamp here like the original WithPower path)
		float wetPenaltyAbs2 = 0.0;
		if (env.wet >= env.wetThreshold)
		{
			float wetScale = jrdn_settings.result.wetPenaltyScale;
			float tmpWet = env.wet * wetScale;
			if (tmpWet < 0.0) tmpWet = 0.0;
			float maxWet = jrdn_settings.result.wetPenaltyMax;
			if (tmpWet > maxWet) tmpWet = maxWet;
			wetPenaltyAbs2 = tmpWet;
		}

		// Wrong-tool flat penalty
		float wrongToolPenalty2;
		if (isPreferred2)
		{
			wrongToolPenalty2 = 0.0;
		}
		else
		{
			float wrongToolAbs = jrdn_settings.result.wrongToolPenaltyAbs;
			wrongToolPenalty2 = wrongToolAbs;
		}

		// Powered penalty (flat, only if powered)
		float poweredPenalty2;
		if (powerType > 0)
		{
			float poweredAbs = jrdn_settings.result.poweredPenaltyAbs;
			poweredPenalty2 = poweredAbs;
		}
		else
		{
			poweredPenalty2 = 0.0;
		}

		// Apply to the spawned result
		jrdn_DbgPenalty("Result penalties: wet=" + env.wet + " wetPenalty=" + wetPenaltyAbs2 + " wrongToolCheck=" + (!isPreferred2) + " powerType=" + powerType);

		if (finalResult)
		{
			float curH2 = finalResult.GetHealth("", "");
			float deltaTotal2 = wetPenaltyAbs2 + wrongToolPenalty2 + poweredPenalty2;
			float newH2 = curH2 - deltaTotal2;
			if (newH2 < 0.0) newH2 = 0.0;
			finalResult.SetHealth("", "", newH2);
		}

		// Optional ruin flags (unchanged behavior) when powered
		if (finalResult)
		{
			if (powerType == 2 && jrdn_settings.result.ruinOnCarBattery)
			{
				finalResult.SetHealth("", "", 0.0);
				jrdn_DbgPenalty("Result ruined due to CarBattery flag");
			}
			else if (powerType == 3 && jrdn_settings.result.ruinOnTruckBattery)
			{
				finalResult.SetHealth("", "", 0.0);
				jrdn_DbgPenalty("Result ruined due to TruckBattery flag");
			}
		}

		// 7) Ensure wetness is applied to the actual spawned item (redundant-safe)
		array<ItemBase> wetSingle = new array<ItemBase>;
		wetSingle.Insert(finalResult);
		jrdn_helpers.ApplyWet(wetSingle, env.wet);
	}
	};
	class craftWiredPCB extends RecipeBase
	{
		override void Init()
		{
			// -------------------------------------------------------------------------------------------------
			// Common
			// -------------------------------------------------------------------------------------------------
			m_Name = "Combine wires and PCB";
			m_IsInstaRecipe = false;					// should this recipe be performed instantly without animation
			m_AnimationLength = 2;						// animation length in relative time units
			m_Specialty = 0;							// relates to the soft skills stats for players - recommended not to change

			// -------------------------------------------------------------------------------------------------
			// Conditions
			// -------------------------------------------------------------------------------------------------
			m_MinDamageIngredient[0]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[0] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
			m_MaxDamageIngredient[0]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[0] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
			m_MinQuantityIngredient[0]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
			m_MaxQuantityIngredient[0]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.
			m_MinDamageIngredient[1]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[1] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
			m_MaxDamageIngredient[1]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[1] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
			m_MinQuantityIngredient[1]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
			m_MaxQuantityIngredient[1]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.

			// -------------------------------------------------------------------------------------------------
			// Ingredient 1
			// -------------------------------------------------------------------------------------------------
			InsertIngredient(0,"jrdn_gps_wire");
			m_IngredientAddHealth[0] = 0;// 0 = do nothing
			m_IngredientSetHealth[0] = -1; // -1 = do nothing
			m_IngredientAddQuantity[0] = -1;// 0 = do nothing
			m_IngredientDestroy[0] = true;//true = destroy, false = do nothing
			m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this 

			// -------------------------------------------------------------------------------------------------
			// Ingredient 2
			// -------------------------------------------------------------------------------------------------
			InsertIngredient(1, "jrdn_gps_pcb");
			m_IngredientAddHealth[1] = 0;// 0 = do nothing
			m_IngredientSetHealth[1] = -1; // -1 = do nothing
			m_IngredientAddQuantity[1] = 0; // 0 = do nothing
			m_IngredientDestroy[1] = true; //true = destroy, false = do nothing
			m_IngredientUseSoftSkills[1] = false; // set 'true' to allow modification of the values by softskills on this ingredient

			// -------------------------------------------------------------------------------------------------
			// Result
			// -------------------------------------------------------------------------------------------------
			AddResult("jrdn_gps_wired_pcb");//add results here
			m_ResultSetFullQuantity[0] = false;//true = set full quantity, false = do nothing
			m_ResultSetQuantity[0] = -1;//-1 = do nothing
			m_ResultSetHealth[0] = -1;//-1 = do nothing
			m_ResultInheritsHealth[0] = -2;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
			m_ResultInheritsColor[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
			m_ResultToInventory[0] = -2;//(value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
			m_ResultUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this result
			m_ResultReplacesIngredient[0] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value

		}
		override bool CanDo(ItemBase ingredients[], PlayerBase player)
		{
			return jrdn_helpers.CanCombine_WetCheck(ingredients[0], ingredients[1]);
		}
		override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
		{
			super.Do(ingredients, player, results, specialty_weight);

			array<ItemBase> ingredientArray = new array<ItemBase>;
			if (ingredients)
			{
				ingredientArray.Insert(ingredients[0]);
				ingredientArray.Insert(ingredients[1]);
			}

			float Wet_Read;
			jrdn_helpers.ReadWet(ingredientArray, Wet_Read);

			if (GetGame() && GetGame().IsServer())
				jrdn_helpers.ApplyWet(results, Wet_Read);
		}
	};
class craftGPS extends RecipeBase
{
	override void Init()
	{
		// -------------------------------------------------------------------------------------------------
		// Common
		// -------------------------------------------------------------------------------------------------
		m_Name = "Combine wires and PCB";
		m_IsInstaRecipe = false;					// should this recipe be performed instantly without animation
		m_AnimationLength = 2;						// animation length in relative time units
		m_Specialty = 0;							// relates to the soft skills stats for players - recommended not to change

		// -------------------------------------------------------------------------------------------------
		// Conditions
		// -------------------------------------------------------------------------------------------------
		m_MinDamageIngredient[0]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[0] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[0]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[0] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[0]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[0]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.
		m_MinDamageIngredient[1]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[1] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[1]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[1] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[1]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[1]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.

		// -------------------------------------------------------------------------------------------------
		// Ingredient 1
		// -------------------------------------------------------------------------------------------------
		InsertIngredient(0,"jrdn_gps_wired_pcb");
		m_IngredientAddHealth[0] = 0;// 0 = do nothing
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = -1;// 0 = do nothing
		m_IngredientDestroy[0] = true;//true = destroy, false = do nothing
		m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this 

		// -------------------------------------------------------------------------------------------------
		// Ingredient 2
		// -------------------------------------------------------------------------------------------------
		InsertIngredient(1, "jrdn_gps_case");
		m_IngredientAddHealth[1] = 0;// 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = 0; // 0 = do nothing
		m_IngredientDestroy[1] = true; //true = destroy, false = do nothing
		m_IngredientUseSoftSkills[1] = false; // set 'true' to allow modification of the values by softskills on this ingredient

		// -------------------------------------------------------------------------------------------------
		// Result
		// -------------------------------------------------------------------------------------------------
		AddResult("GPSReceiver");//add results here
		m_ResultSetFullQuantity[0] = false;//true = set full quantity, false = do nothing
		m_ResultSetQuantity[0] = -1;//-1 = do nothing
		m_ResultSetHealth[0] = -1;//-1 = do nothing
		m_ResultInheritsHealth[0] = -2;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
		m_ResultInheritsColor[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
		m_ResultToInventory[0] = -2;//(value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
		m_ResultUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this result
		m_ResultReplacesIngredient[0] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
	}
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		if (!ingredients) return false;
		return jrdn_helpers.CanCombine_WetCheck(ingredients[0], ingredients[1]);
	}
override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
{
    super.Do(ingredients, player, results, specialty_weight);

    if (!ingredients) return;
    if (!results) return;

    array<ItemBase> ingredientArray = new array<ItemBase>;
    if (ingredients)
    {
        ingredientArray.Insert(ingredients[0]);
        ingredientArray.Insert(ingredients[1]);
    }

    float Wet_Read;
    jrdn_helpers.ReadWet(ingredientArray, Wet_Read);

    if (GetGame() && GetGame().IsServer())
        jrdn_helpers.ApplyWet(results, Wet_Read);
}

};