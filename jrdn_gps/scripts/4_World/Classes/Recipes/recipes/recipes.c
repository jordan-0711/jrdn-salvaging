// ===================================================================================
// recipes.c
// Simple recipe definitions that call helper processors
// ===================================================================================

class salvageWires extends RecipeBase
{
    override void Init()
    {
        m_Name = "Cut wires";
        m_IsInstaRecipe = false;
        m_AnimationLength = 2;
        m_Specialty = 0;

        m_MinDamageIngredient[0] = -1;
        m_MaxDamageIngredient[0] = 3;
        m_MinQuantityIngredient[0] = -1;
        m_MaxQuantityIngredient[0] = -1;
        m_MinDamageIngredient[1] = -1;
        m_MaxDamageIngredient[1] = 3;
        m_MinQuantityIngredient[1] = -1;
        m_MaxQuantityIngredient[1] = -1;

        InsertIngredientEx(0, "SteakKnife", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "KitchenKnife", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "CombatKnife", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "HuntingKnife", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "Cleaver", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "AK_Bayonet", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "M9A1_Bayonet", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "SNAFU_Kabar", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "Msp_VorpalKnife", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "KukriKnife", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "FangeKnife", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "Mosin_Bayonet", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "SNAFU_SKS_Bayonet", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "Machete", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "CrudeMachete", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "OrientalMachete", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, true);
        InsertIngredientEx(0, "Hatchet", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "WoodAxe", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "FirefighterAxe", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "FirefighterAxe_Black", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "FirefighterAxe_Green", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "Pickaxe", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "Iceaxe", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "HandSaw", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "Hacksaw", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "Sword", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);

        m_IngredientAddHealth[0] = -10;
        m_IngredientSetHealth[0] = -1;
        m_IngredientAddQuantity[0] = 0;
        m_IngredientDestroy[0] = false;
        m_IngredientUseSoftSkills[0] = false;

        InsertIngredient(1, "Spotlight");
        InsertIngredient(1, "CableReel");
        
        m_IngredientAddHealth[1] = 0;
        m_IngredientSetHealth[1] = -1;
        m_IngredientAddQuantity[1] = -1;
        m_IngredientDestroy[1] = true;
        m_IngredientUseSoftSkills[1] = false;

        AddResult("jrdn_gps_wire");
        m_ResultSetFullQuantity[0] = false;
        m_ResultSetQuantity[0] = -1;
        m_ResultSetHealth[0] = -1;
        m_ResultInheritsHealth[0] = 0;
        m_ResultInheritsColor[0] = -1;
        m_ResultToInventory[0] = -2;
        m_ResultUseSoftSkills[0] = false;
        m_ResultReplacesIngredient[0] = -1;
    }

    override bool CanDo(ItemBase ingredients[], PlayerBase player)
    {
        return true;
    }

    override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
    {
        super.Do(ingredients, player, results, specialty_weight);
        
        array<int> preferredTools = new array<int>;
        preferredTools.Insert(toolCategory.TOOL_SMALL_BLADE);
        preferredTools.Insert(toolCategory.TOOL_LARGE_BLADE);
        
        ProcessCuttingRecipe(ingredients, player, results, preferredTools, "salvageWires");
    }
}

class salvagePCBCasing extends RecipeBase
{
    override void Init()
    {
        m_Name = "Salvage GPS parts";
        m_IsInstaRecipe = false;
        m_AnimationLength = 2;
        m_Specialty = 0;

        m_MinDamageIngredient[0] = -1;
        m_MaxDamageIngredient[0] = 3;
        m_MinQuantityIngredient[0] = -1;
        m_MaxQuantityIngredient[0] = -1;
        m_MinDamageIngredient[1] = -1;
        m_MaxDamageIngredient[1] = 3;
        m_MinQuantityIngredient[1] = -1;
        m_MaxQuantityIngredient[1] = -1;

        InsertIngredientEx(0, "Screwdriver", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "Crowbar", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "Pliers", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "SteakKnife", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "KitchenKnife", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "CombatKnife", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "HuntingKnife", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "Cleaver", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "AK_Bayonet", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "M9A1_Bayonet", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "SNAFU_Kabar", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "Msp_VorpalKnife", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "KukriKnife", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "FangeKnife", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "Mosin_Bayonet", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "SNAFU_SKS_Bayonet", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "Machete", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "CrudeMachete", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "OrientalMachete", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_PLACING_HEAVY, true);
        InsertIngredientEx(0, "Hatchet", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "WoodAxe", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "FirefighterAxe", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "FirefighterAxe_Black", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "FirefighterAxe_Green", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "Pickaxe", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_MINEROCK, true);
        InsertIngredientEx(0, "Iceaxe", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_MINEROCK, true);
        InsertIngredientEx(0, "HandSaw", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "Hacksaw", "FirewoodSplit_Saw", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);
        InsertIngredientEx(0, "Sword", "FirewoodSplit_Axe", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);

        m_IngredientAddHealth[0] = 0;
        m_IngredientSetHealth[0] = -1;
        m_IngredientAddQuantity[0] = -1;
        m_IngredientDestroy[0] = false;
        m_IngredientUseSoftSkills[0] = false;

        InsertIngredient(1, "BaseRadio");
        InsertIngredient(1, "PersonalRadio");
        
        m_IngredientAddHealth[1] = -10;
        m_IngredientSetHealth[1] = -1;
        m_IngredientAddQuantity[1] = 0;
        m_IngredientDestroy[1] = true;
        m_IngredientUseSoftSkills[1] = false;

        AddResult("jrdn_gps_pcb");
        m_ResultSetFullQuantity[0] = false;
        m_ResultSetQuantity[0] = -1;
        m_ResultSetHealth[0] = -1;
        m_ResultInheritsHealth[0] = 1;
        m_ResultInheritsColor[0] = -1;
        m_ResultToInventory[0] = -2;
        m_ResultUseSoftSkills[0] = false;
        m_ResultReplacesIngredient[0] = -1;
    }

    override bool CanDo(ItemBase ingredients[], PlayerBase player)
    {
        return true;
    }

    override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
    {
        super.Do(ingredients, player, results, specialty_weight);
        
        array<int> preferredTools = new array<int>;
        preferredTools.Insert(toolCategory.TOOL_UTILITY_SCREW);
        preferredTools.Insert(toolCategory.TOOL_UTILITY_WRENCH);
        
        TStringArray possibleResults = new TStringArray;
        possibleResults.Insert("jrdn_gps_pcb");
        possibleResults.Insert("jrdn_gps_case");
        possibleResults.Insert("jrdn_gps_wired_pcb");
        
        ProcessElectronicsRecipe(ingredients, player, results, preferredTools, possibleResults, "salvagePCBCasing");
    }
}

class craftWiredPCB extends RecipeBase
{
    override void Init()
    {
        m_Name = "Combine wires and PCB";
        m_IsInstaRecipe = false;
        m_AnimationLength = 2;
        m_Specialty = 0;

        m_MinDamageIngredient[0] = -1;
        m_MaxDamageIngredient[0] = 3;
        m_MinQuantityIngredient[0] = -1;
        m_MaxQuantityIngredient[0] = -1;
        m_MinDamageIngredient[1] = -1;
        m_MaxDamageIngredient[1] = 3;
        m_MinQuantityIngredient[1] = -1;
        m_MaxQuantityIngredient[1] = -1;

        InsertIngredient(0, "jrdn_gps_wire");
        m_IngredientAddHealth[0] = 0;
        m_IngredientSetHealth[0] = -1;
        m_IngredientAddQuantity[0] = -1;
        m_IngredientDestroy[0] = true;
        m_IngredientUseSoftSkills[0] = false;

        InsertIngredient(1, "jrdn_gps_pcb");
        m_IngredientAddHealth[1] = 0;
        m_IngredientSetHealth[1] = -1;
        m_IngredientAddQuantity[1] = 0;
        m_IngredientDestroy[1] = true;
        m_IngredientUseSoftSkills[1] = false;

        AddResult("jrdn_gps_wired_pcb");
        m_ResultSetFullQuantity[0] = false;
        m_ResultSetQuantity[0] = -1;
        m_ResultSetHealth[0] = -1;
        m_ResultInheritsHealth[0] = -2;
        m_ResultInheritsColor[0] = -1;
        m_ResultToInventory[0] = -2;
        m_ResultUseSoftSkills[0] = false;
        m_ResultReplacesIngredient[0] = -1;
    }

    override bool CanDo(ItemBase ingredients[], PlayerBase player)
    {
        return CanCombineWet(ingredients[0], ingredients[1]);
    }

    override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
    {
        super.Do(ingredients, player, results, specialty_weight);
        ProcessCombineRecipe(ingredients, player, results, "craftWiredPCB");
    }
}

class craftGPS extends RecipeBase
{
    override void Init()
    {
        m_Name = "Craft GPS receiver";
        m_IsInstaRecipe = false;
        m_AnimationLength = 2;
        m_Specialty = 0;

        m_MinDamageIngredient[0] = -1;
        m_MaxDamageIngredient[0] = 3;
        m_MinQuantityIngredient[0] = -1;
        m_MaxQuantityIngredient[0] = -1;
        m_MinDamageIngredient[1] = -1;
        m_MaxDamageIngredient[1] = 3;
        m_MinQuantityIngredient[1] = -1;
        m_MaxQuantityIngredient[1] = -1;

        InsertIngredient(0, "jrdn_gps_wired_pcb");
        m_IngredientAddHealth[0] = 0;
        m_IngredientSetHealth[0] = -1;
        m_IngredientAddQuantity[0] = -1;
        m_IngredientDestroy[0] = true;
        m_IngredientUseSoftSkills[0] = false;

        InsertIngredient(1, "jrdn_gps_case");
        m_IngredientAddHealth[1] = 0;
        m_IngredientSetHealth[1] = -1;
        m_IngredientAddQuantity[1] = 0;
        m_IngredientDestroy[1] = true;
        m_IngredientUseSoftSkills[1] = false;

        AddResult("GPSReceiver");
        m_ResultSetFullQuantity[0] = false;
        m_ResultSetQuantity[0] = -1;
        m_ResultSetHealth[0] = -1;
        m_ResultInheritsHealth[0] = -2;
        m_ResultInheritsColor[0] = -1;
        m_ResultToInventory[0] = -2;
        m_ResultUseSoftSkills[0] = false;
        m_ResultReplacesIngredient[0] = -1;
    }

    override bool CanDo(ItemBase ingredients[], PlayerBase player)
    {
        if (!ingredients) return false;
        return CanCombineWet(ingredients[0], ingredients[1]);
    }

    override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
    {
        super.Do(ingredients, player, results, specialty_weight);
        
        if (!ingredients) return;
        if (!results) return;
        
        ProcessCombineRecipe(ingredients, player, results, "craftGPS");
    }
}