// ---------------------------------------------------------------------
// Debug toggles (self-contained, vanilla Print(); OFF by default)
// ---------------------------------------------------------------------
class jrdn_debug
{
    static bool Enable = true;
    static bool TraceWet = true;
    static bool TraceTools = true;
    static bool TracePower = true;
    static bool TracePenalties = true;

    // JSON-ready hook (no-op for now)
    static void LoadFromConfig() {}
}

// Small helpers
static bool jrdn_IsServer()
{
    return (GetGame() && GetGame().IsServer());
}

static void jrdn_Dbg(string msg)
{
    if (!jrdn_debug.Enable) return;
    Print("[JGPS] " + msg);
}
static void jrdn_DbgWet(string msg)
{
    if (!jrdn_debug.Enable || !jrdn_debug.TraceWet) return;
    Print("[JGPS][WET] " + msg);
}
static void jrdn_DbgTool(string msg)
{
    if (!jrdn_debug.Enable || !jrdn_debug.TraceTools) return;
    Print("[JGPS][TOOL] " + msg);
}
static void jrdn_DbgPower(string msg)
{
    if (!jrdn_debug.Enable || !jrdn_debug.TracePower) return;
    Print("[JGPS][POWER] " + msg);
}
static void jrdn_DbgPenalty(string msg)
{
    if (!jrdn_debug.Enable || !jrdn_debug.TracePenalties) return;
    Print("[JGPS][PENALTY] " + msg);
}

// Load-once safety (no need for server init)
static bool jrdn__dbg_loaded = true;
static void jrdn_DebugLoadOnce()
{
    if (jrdn__dbg_loaded) return;
    jrdn__dbg_loaded = true;
    jrdn_debug.LoadFromConfig(); // does nothing today; JSON-ready
}
// ---------------------------------------------------------------------
// Context holders
// ---------------------------------------------------------------------
class jrdnWetInfo
{
    float wet;           // normalized wetness (0..1); 0 if not available
    float wetThreshold;  // threshold used for “is wet enough to matter?” checks
}

class jrdnToolInfo
{
    ItemBase tool;                       // the tool used in the recipe
    ref array<toolCategory> preferred;   // preferred tool categories for this recipe
    toolCategory usedCat;                // detected category of the tool
    float preferredMul;                  // jrdn_settings.tools.preferredMul
    float notPreferredMul;               // jrdn_settings.tools.notPreferredMul
}

// ---------------------------------------------------------------------
// ENUMs
// ---------------------------------------------------------------------
enum toolCategory
{
    TOOL_SMALL_BLADE,
    TOOL_LARGE_BLADE,
    TOOL_AXE,
    TOOL_SAW,
    TOOL_HAMMER,
    TOOL_UTILITY_SCREW,
    TOOL_UTILITY_WRENCH,
    TOOL_BLUNT,
    TOOL_LONG
};
// ---------------------------------------------------------------------
// toolCategory helper for preferred tool mapping
// ---------------------------------------------------------------------
toolCategory GetToolCategory(ItemBase tool)
{
    if (!tool) return toolCategory.TOOL_SMALL_BLADE;

    string toolName = tool.GetType();

    // Small blades
    if (toolName == "KitchenKnife")
        return toolCategory.TOOL_SMALL_BLADE;
    if (toolName == "SteakKnife")
        return toolCategory.TOOL_SMALL_BLADE;
    if (toolName == "CombatKnife")
        return toolCategory.TOOL_SMALL_BLADE;
    if (toolName == "HuntingKnife")
        return toolCategory.TOOL_SMALL_BLADE;
    if (toolName == "Cleaver")
        return toolCategory.TOOL_SMALL_BLADE;
    if (toolName == "AK_Bayonet")
        return toolCategory.TOOL_SMALL_BLADE;
    if (toolName == "M9A1_Bayonet")
        return toolCategory.TOOL_SMALL_BLADE;
    if (toolName == "SNAFU_Kabar")
        return toolCategory.TOOL_SMALL_BLADE;

    // Large blades
    if (toolName == "Msp_VorpalKnife")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "KukriKnife")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "FangeKnife")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "Mosin_Bayonet")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "SNAFU_SKS_Bayonet")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "Machete")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "CrudeMachete")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "OrientalMachete")
        return toolCategory.TOOL_LARGE_BLADE;

    // Axes
    if (toolName == "Hatchet")
        return toolCategory.TOOL_AXE;
    if (toolName == "WoodAxe")
        return toolCategory.TOOL_AXE;
    if (toolName == "FirefighterAxe")
        return toolCategory.TOOL_AXE;
    if (toolName == "FirefighterAxe_Black")
        return toolCategory.TOOL_AXE;
    if (toolName == "FirefighterAxe_Green")
        return toolCategory.TOOL_AXE;
    if (toolName == "Pickaxe")
        return toolCategory.TOOL_AXE;
    if (toolName == "Iceaxe")
        return toolCategory.TOOL_AXE;
    // Saws
    if (toolName == "HandSaw")
        return toolCategory.TOOL_SAW;
    if (toolName == "Hacksaw")
        return toolCategory.TOOL_SAW;
     // Hammers
    if (toolName == "Hammer")
        return toolCategory.TOOL_HAMMER;
    if (toolName == "MeatTenderizer")
        return toolCategory.TOOL_HAMMER;
    if (toolName == "SledgeHammer")
        return toolCategory.TOOL_HAMMER;
     // Utility SCREW/PRY ETC
    if (toolName == "Screwdriver")
        return toolCategory.TOOL_UTILITY_SCREW;
    if (toolName == "Pliers")
        return toolCategory.TOOL_UTILITY_SCREW;
    if (toolName == "Crowbar")
        return toolCategory.TOOL_UTILITY_SCREW;
    // Utility wrench
    if (toolName == "LugWrench")
        return toolCategory.TOOL_UTILITY_WRENCH;
    if (toolName == "Wrench")
        return toolCategory.TOOL_UTILITY_WRENCH;
    if (toolName == "PipeWrench")
        return toolCategory.TOOL_UTILITY_WRENCH;
    // Blunt
    if (toolName == "BaseballBat")
        return toolCategory.TOOL_BLUNT;
    if (toolName == "BarbedBaseballBat")
        return toolCategory.TOOL_BLUNT;
    if (toolName == "NailedBaseballBat")
        return toolCategory.TOOL_BLUNT;
    if (toolName == "FryingPan")
        return toolCategory.TOOL_BLUNT;
    if (toolName == "Mace")
        return toolCategory.TOOL_BLUNT;
    if (toolName == "Pipe")
        return toolCategory.TOOL_BLUNT;
    // Long
    if (toolName == "FarmingHoe")
        return toolCategory.TOOL_LONG;
    if (toolName == "Shovel")
        return toolCategory.TOOL_LONG;
    if (toolName == "FieldShovel")
        return toolCategory.TOOL_LONG;
    if (toolName == "Pitchfork")
        return toolCategory.TOOL_LONG;
    if (toolName == "Sword")
        return toolCategory.TOOL_LONG;
    // Default
    return toolCategory.TOOL_SMALL_BLADE;
}

// ---------------------------------------------------------------------
// Tool noun replacement for Punish Messages
// ---------------------------------------------------------------------
string toolNoun(toolCategory cat)
{
    switch (cat)
    {
        case toolCategory.TOOL_SMALL_BLADE:
            return "knife blade";
        case toolCategory.TOOL_LARGE_BLADE:
            return "large blade";
        case toolCategory.TOOL_AXE:
            return "axe head";
        case toolCategory.TOOL_SAW:
            return "saw blade";
        case toolCategory.TOOL_HAMMER:
            return "Hammer";
        case toolCategory.TOOL_UTILITY_SCREW:
            return "tool";
        case toolCategory.TOOL_UTILITY_WRENCH:
            return "wrench";
        case toolCategory.TOOL_BLUNT:
            return "weapon";
        case toolCategory.TOOL_LONG:
            return "long tool";
        default:
            return "blade";
    }
    return "blade";
}

// -------------------------------------------------------------------------------------------------
// Shared helpers used on recipes
// -------------------------------------------------------------------------------------------------
class jrdn_helpers
{
    // ---------------------------------------------------------------------
    // RandomResults_Single
    // ---------------------------------------------------------------------
    static void RandomResults_Single(TStringArray resultPool, out string pickResult)
    {
        pickResult = "";

        if (!resultPool || resultPool.Count() == 0)
            return;

        int index = Math.RandomInt(0, resultPool.Count());
        pickResult = resultPool.Get(index);
    }

    // ---------------------------------------------------------------------
    // RandomResults_Multi
    // ---------------------------------------------------------------------
    static void RandomResults_Multi(TStringArray resultPool, float pickAmountModifier, out TStringArray pickResult)
    {
        if (!pickResult) pickResult = new TStringArray; else pickResult.Clear();
        if (!resultPool || resultPool.Count() == 0) return;
        if (pickAmountModifier < 0.0) pickAmountModifier = 0.0;
        if (pickAmountModifier > 1.0) pickAmountModifier = 1.0;

        int resultPoolCount = resultPool.Count();
        int maxPossiblePick = Math.Floor(resultPoolCount * pickAmountModifier);
        if (maxPossiblePick < 1) maxPossiblePick = 1;
        if (maxPossiblePick > resultPoolCount) maxPossiblePick = resultPoolCount;

        int toPick = Math.RandomInt(1, maxPossiblePick + 1);

        TStringArray pickedResults = new TStringArray;
        pickedResults.Copy(resultPool);

        for (int i = pickedResults.Count() - 1; i > 0; i--)
        {
            int j = Math.RandomInt(0, i + 1);
            string tmp = pickedResults[i];
            pickedResults[i] = pickedResults[j];
            pickedResults[j] = tmp;
        }

        for (int k = 0; k < toPick; k++)
        {
            pickResult.Insert(pickedResults.Get(k));
        }
    }

    // ---------------------------------------------------------------------
    // Read Highest Wetness from ItemBase
    // ---------------------------------------------------------------------
    static void ReadWet(array<ItemBase> items, out float wetnessValue_Read)
    {
        wetnessValue_Read = -1.0;
        if (!items) return;

        float wettestItem = -1.0;

        for (int i = 0; i < items.Count(); i++)
        {
            ItemBase itemCount = items[i];
            if (!itemCount) continue;

            float wetItem = itemCount.GetWet();
            if (wetItem >= 0.0)
            {
                if (wettestItem < 0.0)
                {
                    wettestItem = wetItem;
                }
                else
                {
                    if (wetItem > wettestItem)
                        wettestItem = wetItem;
                }
            }
        }
        wetnessValue_Read = wettestItem;
    }

    // ---------------------------------------------------------------------
    // Write item wetness
    // ---------------------------------------------------------------------
    static void ApplyWet(array<ItemBase> results, float wetnessValue_Write)
    {
        if (!results) return;
        if (wetnessValue_Write < 0.0) return;

        for (int i = 0; i < results.Count(); i++)
        {
            ItemBase foundResults = results[i];
            if (!foundResults) continue;
            foundResults.SetWet(wetnessValue_Write);
        }
    }

    // ---------------------------------------------------------------------
    // read wetness & set a working threshold
    // ---------------------------------------------------------------------
    static void buildWetInfo(array<ItemBase> items, out jrdnWetInfo env)
    {
        jrdn_DebugLoadOnce();

        if (!env) env = new jrdnWetInfo();

        float wet_read = -1.0;
        ReadWet(items, wet_read);

        if (wet_read < 0.0) wet_read = 0.0; // normalize invalid to 0
        env.wet = wet_read;

        // This recipe family uses "DAMP" as the threshold for risk/effects
        env.wetThreshold = GameConstants.STATE_DAMP;

        // --- debug (no Format)
        jrdn_DbgWet("buildWetInfo wet=" + env.wet + " threshold=" + env.wetThreshold);
    }

    // ---------------------------------------------------------------------
    // Read item health
    // ---------------------------------------------------------------------
    static void ReadHealth(ItemBase src, out float baseHealth)
    {
        baseHealth = -1.0;

        if (!src)
            return;

        float maxHealth = src.GetMaxHealth("", "");
        if (maxHealth > 0.0)
        {
            float currentHealth = src.GetHealth("", "");
            baseHealth = currentHealth / maxHealth;
        }
    }
    // ---------------------------------------------------------------------
    // Write item health
    // ---------------------------------------------------------------------
    static void ApplyHealth(ItemBase item, float itemHealth)
    {
        if (!item)
            return;

        if (itemHealth < 0.0)
            return;

        float maxHealth = item.GetMaxHealth("", "");
        if (maxHealth <= 0.0)
            return;

        float applyItemHealth = maxHealth * itemHealth;
        item.SetHealth("", "", applyItemHealth);
    }
    // ---------------------------------------------------------------------
    // Duplicate item spawn check
    // ---------------------------------------------------------------------
    static ItemBase KeepOrSpawnRandomResult(string pickClass, array<ItemBase> results, PlayerBase player, string placeholderClass, array<ItemBase> inheritFromItems, ItemBase healthSource)
    {
        if (!GetGame() || !GetGame().IsServer())
            return null;

        if (pickClass == "")
            return null;

        if (!results || results.Count() == 0)
            return null;

        if (!player)
            return null;

        ItemBase placeholderItem = results[0];
        ItemBase finalItem = null;

        if (placeholderItem && placeholderItem.IsKindOf(pickClass))
        {
            finalItem = placeholderItem;
        }
        else
        {
            if (placeholderItem)
                placeholderItem.Delete();

            finalItem = SpawnAtFeet(pickClass, player);
        }

        float inheritHealthValue;
        ReadHealth(healthSource, inheritHealthValue);

        float inheritWetValue;
        jrdn_helpers.ReadWet(inheritFromItems, inheritWetValue);

        if (finalItem && inheritHealthValue >= 0.0)
            ApplyHealth(finalItem, inheritHealthValue);

        if (inheritWetValue >= 0.0)
            jrdn_helpers.ApplyWet(results, inheritWetValue);

        return finalItem;
    }
    // ---------------------------------------------------------------------
    // Spawn RandomResult at feet
    // ---------------------------------------------------------------------
    static ItemBase SpawnAtFeet(string className, PlayerBase player)
    {
        if (!GetGame() || !GetGame().IsServer())
            return null;

        if (className == "")
            return null;

        if (!player)
            return null;

        vector playerPosition = player.GetPosition();

        EntityAI createItemSurface = EntityAI.Cast(GetGame().CreateObjectEx(className, playerPosition, ECE_PLACE_ON_SURFACE));
        ItemBase spawnItemWorld = ItemBase.Cast(createItemSurface);

        if (!spawnItemWorld)
        {
            if (createItemSurface)
                createItemSurface.Delete();
            return null;
        }

        return spawnItemWorld;
    }
    // ---------------------------------------------------------------------
    // Ingredient Wetness check for CanDo methods
    // ---------------------------------------------------------------------
    static bool CanCombine_WetCheck(ItemBase ingredient0, ItemBase ingredient1)
    {
        if (!ingredient0 || !ingredient1)
            return false;

        float wetThreshold = jrdn_settings.wet.combineDryThreshold;

        toolCategory ingredient0Category = GetToolCategory(ingredient0);
        toolCategory ingredient1Category = GetToolCategory(ingredient1);

        // Check if ingredient0 is a tool
        bool ingredient0IsTool = false;
        if (ingredient0Category == toolCategory.TOOL_SMALL_BLADE) ingredient0IsTool = true;
        if (ingredient0Category == toolCategory.TOOL_LARGE_BLADE) ingredient0IsTool = true;
        if (ingredient0Category == toolCategory.TOOL_AXE) ingredient0IsTool = true;
        if (ingredient0Category == toolCategory.TOOL_SAW) ingredient0IsTool = true;
        if (ingredient0Category == toolCategory.TOOL_HAMMER) ingredient0IsTool = true;
        if (ingredient0Category == toolCategory.TOOL_UTILITY_SCREW) ingredient0IsTool = true;
        if (ingredient0Category == toolCategory.TOOL_UTILITY_WRENCH) ingredient0IsTool = true;
        if (ingredient0Category == toolCategory.TOOL_BLUNT) ingredient0IsTool = true;
        if (ingredient0Category == toolCategory.TOOL_LONG) ingredient0IsTool = true;

        // Check if ingredient1 is a tool
        bool ingredient1IsTool = false;
        if (ingredient1Category == toolCategory.TOOL_SMALL_BLADE) ingredient1IsTool = true;
        if (ingredient1Category == toolCategory.TOOL_LARGE_BLADE) ingredient1IsTool = true;
        if (ingredient1Category == toolCategory.TOOL_AXE) ingredient1IsTool = true;
        if (ingredient1Category == toolCategory.TOOL_SAW) ingredient1IsTool = true;
        if (ingredient1Category == toolCategory.TOOL_HAMMER) ingredient1IsTool = true;
        if (ingredient1Category == toolCategory.TOOL_UTILITY_SCREW) ingredient1IsTool = true;
        if (ingredient1Category == toolCategory.TOOL_UTILITY_WRENCH) ingredient1IsTool = true;
        if (ingredient1Category == toolCategory.TOOL_BLUNT) ingredient1IsTool = true;
        if (ingredient1Category == toolCategory.TOOL_LONG) ingredient1IsTool = true;

        if (ingredient0IsTool && !ingredient1IsTool)
        {
            float ingredient1_Wetness = ingredient1.GetWet();
            if (ingredient1_Wetness <= wetThreshold)
                return true;
            return false;
        }
        
        if (!ingredient0IsTool && ingredient1IsTool)
        {
            float ingredient0_Wetness = ingredient0.GetWet();
            if (ingredient0_Wetness <= wetThreshold)
                return true;
            return false;
        }
        
        float ingredient0_NonToolWetness = ingredient0.GetWet();
        float ingredient1_NonToolWetness = ingredient1.GetWet();

        if (ingredient0_NonToolWetness <= wetThreshold && ingredient1_NonToolWetness <= wetThreshold)
            return true;

        return false;
    }

    // ---------------------------------------------------------------------
    // Detect powered ingredients
    // ---------------------------------------------------------------------
    static int DetectPoweredIngredient(ItemBase ingredientItem, out ItemBase foundPowerOut)
    {
        foundPowerOut = null;

        if (!ingredientItem)
            return 0;

        EntityAI ingredientAI = EntityAI.Cast(ingredientItem);
        if (!ingredientAI)
            return 0;

        if (!ingredientAI.GetInventory())
            return 0;

        int count = ingredientAI.GetInventory().AttachmentCount();
        for (int i = 0; i < count; i++)
        {
            EntityAI poweredAttachment = ingredientAI.GetInventory().GetAttachmentFromIndex(i);
            if (!poweredAttachment)
                continue;

            ItemBase poweredAttachmentFound = ItemBase.Cast(poweredAttachment);
            if (!poweredAttachmentFound)
                continue;

            if (poweredAttachmentFound.IsKindOf("Battery9V"))
            {
                foundPowerOut = poweredAttachmentFound;
                return 1;
            }
            if (poweredAttachmentFound.IsKindOf("CarBattery"))
            {
                foundPowerOut = poweredAttachmentFound;
                return 2;
            }
            if (poweredAttachmentFound.IsKindOf("TruckBattery"))
            {
                foundPowerOut = poweredAttachmentFound;
                return 3;
            }
        }

        return 0;
    }
    // ---------------------------------------------------------------------
    // Preferred Recipe Tool
    // ---------------------------------------------------------------------
    static bool IsPreferredTool(ItemBase usedTool, array<toolCategory> preferredToolList, out toolCategory usedCategory)
    {
        usedCategory = toolCategory.TOOL_SMALL_BLADE;

        if (!usedTool)
            return false;

        usedCategory = GetToolCategory(usedTool);

        if (!preferredToolList)
            return false;

        for (int i = 0; i < preferredToolList.Count(); i++)
        {
            if (usedCategory == preferredToolList[i])
                return true;
        }
        return false;
    }

    // ---------------------------------------------------------------------
    // Wrong tool risk modifier
    // ---------------------------------------------------------------------
    static float ToolRiskMultiplier(ItemBase usedTool, array<toolCategory> preferredToolList, float preferredMultiplier, float notPreferredMultiplier, out toolCategory usedCategory)
    {
        usedCategory = toolCategory.TOOL_SMALL_BLADE;

        if (preferredMultiplier < 0.0) preferredMultiplier = 0.0;
        if (notPreferredMultiplier < 0.0) notPreferredMultiplier = 0.0;

        bool isPreferred = IsPreferredTool(usedTool, preferredToolList, usedCategory);
        if (isPreferred)
            return preferredMultiplier;

        return notPreferredMultiplier;
    }

    // ---------------------------------------------------------------------
    // Drop item if punished
    // ---------------------------------------------------------------------
    static void DropItemInHands(PlayerBase player)
    {
        if (!player) return;
        EntityAI inHands = player.GetItemInHands();
        if (inHands && player.GetHumanInventory())
            player.GetHumanInventory().DropEntity(InventoryMode.SERVER, player, inHands);
    }

    // ---------------------------------------------------------------------
    // Punishment Protection
    // Only applies to gloves for now
    // ---------------------------------------------------------------------
    static bool HasGloveProtection(PlayerBase player, out float mitigation, out ItemBase foundGloves)
    {
        mitigation = jrdn_settings.gear.gloveMitigation;
        foundGloves = null;
        if (!player)
            return false;

        EntityAI pe = EntityAI.Cast(player);
        if (!pe || !pe.GetInventory())
            return false;

        int ac = pe.GetInventory().AttachmentCount();
        for (int i = 0; i < ac; i++)
        {
            EntityAI att = pe.GetInventory().GetAttachmentFromIndex(i);
            if (!att)
                continue;

            ItemBase itm = ItemBase.Cast(att);
            if (!itm)
                continue;

            if (itm.IsKindOf("Gloves"))
            {
                foundGloves = itm;
                mitigation = jrdn_settings.gear.gloveMitigation;
                return true;
            }
        }
        return false;
    }

    // ---------------------------------------------------------------------
    // Reusable selection pools for Punish
    // ---------------------------------------------------------------------
    protected static ref map<string, ref TStringArray> injuryPools;
    protected static ref map<int, ref TStringArray> toolCategoryTags;
    protected static ref set<int> traumaOnly;
    protected static void BuildInjuryData()
    {
        if (injuryPools)
        {
            return;
        }

        injuryPools   = new map<string, ref TStringArray>;
        toolCategoryTags = new map<int, ref TStringArray>;
        traumaOnly = new set<int>;

        // --------------------------------------
        // Classing injury
        // --------------------------------------
        ref TStringArray cutArms = new TStringArray;
        cutArms.Insert("LeftForeArmRoll");
        cutArms.Insert("RightForeArmRoll");
        cutArms.Insert("LeftArmRoll");
        cutArms.Insert("RightArmRoll");
        injuryPools.Insert("cutArms", cutArms);

        ref TStringArray cutLegs = new TStringArray;
        cutLegs.Insert("LeftLeg");
        cutLegs.Insert("RightLeg");
        cutLegs.Insert("LeftLegRoll");
        cutLegs.Insert("RightLegRoll");
        cutLegs.Insert("LeftUpLeg");
        cutLegs.Insert("RightUpLeg");
        injuryPools.Insert("cutLegs", cutLegs);

        ref TStringArray cutFeet = new TStringArray;
        cutFeet.Insert("LeftFoot");
        cutFeet.Insert("RightFoot");
        injuryPools.Insert("cutFeet", cutFeet);

        ref TStringArray cutToes = new TStringArray;
        cutToes.Insert("LeftToeBase");
        cutToes.Insert("RightToeBase");
        injuryPools.Insert("cutToes", cutToes);

        ref TStringArray cutBody = new TStringArray;
        cutBody.Insert("Head");
        cutBody.Insert("Neck");
        cutBody.Insert("Pelvis");
        injuryPools.Insert("cutBody", cutBody);

        // --------------------------------------
        // Injury classes to Tool Category
        // --------------------------------------
        ref TStringArray toolSmallBlade = new TStringArray;
        toolSmallBlade.Insert("cutArms");
        toolCategoryTags.Insert(toolCategory.TOOL_SMALL_BLADE, toolSmallBlade);

        ref TStringArray toolLargeBlade = new TStringArray;
        toolLargeBlade.Insert("cutArms");
        toolLargeBlade.Insert("cutLegs");
        toolLargeBlade.Insert("cutFeet");
        toolCategoryTags.Insert(toolCategory.TOOL_LARGE_BLADE, toolLargeBlade);

        ref TStringArray toolAxe = new TStringArray;
        toolAxe.Insert("cutFeet");
        toolAxe.Insert("cutToes");
        toolAxe.Insert("cutLegs");
        toolAxe.Insert("cutBody");
        toolCategoryTags.Insert(toolCategory.TOOL_AXE, toolAxe);

        ref TStringArray toolSaw = new TStringArray;
        toolSaw.Insert("cutLegs");
        toolSaw.Insert("cutFeet");
        toolCategoryTags.Insert(toolCategory.TOOL_SAW, toolSaw);

        ref TStringArray toolLong = new TStringArray;
        toolLong.Insert("cutFeet");
        toolLong.Insert("cutToes");
        toolLong.Insert("cutLegs");
        toolLong.Insert("cutBody");
        toolCategoryTags.Insert(toolCategory.TOOL_LONG, toolLong);

        traumaOnly.Insert(toolCategory.TOOL_HAMMER);
        traumaOnly.Insert(toolCategory.TOOL_BLUNT);
    }

    // ---------------------------------------------------------------------
    // Bleed selection per toolCategory
    // ---------------------------------------------------------------------
    static bool PickBleedSelectionForTool(toolCategory cat, out string outSelection)
    {
        outSelection = "";

        BuildInjuryData();

        // Check if cat is in traumaOnly set
        bool isTraumaOnly = false;
        if (traumaOnly)
        {
            for (int t = 0; t < traumaOnly.Count(); t++)
            {
                toolCategory traumaCat = traumaOnly.Get(t);
                if (traumaCat == cat)
                {
                    isTraumaOnly = true;
                    break;
                }
            }
        }

        if (isTraumaOnly)
        {
            return false;
        }

        TStringArray tagList = toolCategoryTags.Get(cat);
        if (!tagList || tagList.Count() == 0)
        {
            return false;
        }

        TStringArray bleedPool = new TStringArray;
        for (int i = 0; i < tagList.Count(); i++)
        {
            string tagName = tagList.Get(i);
            TStringArray selectionPool = injuryPools.Get(tagName);
            if (selectionPool && selectionPool.Count() > 0)
            {
                for (int j = 0; j < selectionPool.Count(); j++)
                {
                    bleedPool.Insert(selectionPool.Get(j));
                }
            }
        }

        if (bleedPool.Count() == 0)
        {
            return false;
        }

        int idx = Math.RandomInt(0, bleedPool.Count());
        outSelection = bleedPool.Get(idx);
        return true;
    }

    // ---------------------------------------------------------------------
    // Apply bleed for tool
    // ---------------------------------------------------------------------
    static bool TryApplyBleedForTool(PlayerBase player, toolCategory cat, out string usedSelection)
    {
        usedSelection = "";

        if (!player)
            return false;

        string pick;
        bool hasBleed = PickBleedSelectionForTool(cat, pick);
        if (!hasBleed)
            return false;

        usedSelection = pick;

        return ApplyBleed(player, usedSelection);
    }

    // ---------------------------------------------------------------------
    // Apply bleed
    // ---------------------------------------------------------------------
    static bool ApplyBleed(PlayerBase player, string selection)
    {
        if (!player)
            return false;

        if (!player.m_BleedingManagerServer)
            return false;

        return player.m_BleedingManagerServer.AttemptAddBleedingSourceBySelection(selection);
    }

    // ---------------------------------------------------------------------
    // PunishShock
    // ---------------------------------------------------------------------
    static void PunishShock(PlayerBase player, float wetnessValue_Read, int powerType, ItemBase usedTool, array<toolCategory> preferredToolList, bool isCarType, float base9V, float baseCar, float baseTruck, float preferredMultiplier, float notPreferredMultiplier, float mismatchTargetOffset)
    {
        if (!player) return;
        if (powerType <= 0) return;

        toolCategory usedCategory;
        float toolMul = ToolRiskMultiplier(usedTool, preferredToolList, preferredMultiplier, notPreferredMultiplier, usedCategory);
        bool toolPreferred = IsPreferredTool(usedTool, preferredToolList, usedCategory);

        float shockWetMultiplier = jrdn_settings.power.baseMultiplyDry;
        if (wetnessValue_Read >= GameConstants.STATE_DAMP && wetnessValue_Read < GameConstants.STATE_WET)
            shockWetMultiplier = jrdn_settings.power.baseMultiplyDamp;
        else if (wetnessValue_Read >= GameConstants.STATE_WET && wetnessValue_Read < GameConstants.STATE_SOAKING_WET)
            shockWetMultiplier = jrdn_settings.power.baseMultiplyWet;
        else if (wetnessValue_Read >= GameConstants.STATE_SOAKING_WET && wetnessValue_Read < GameConstants.STATE_DRENCHED)
            shockWetMultiplier = jrdn_settings.power.baseMultiplySoaking;
        else if (wetnessValue_Read >= GameConstants.STATE_DRENCHED)
            shockWetMultiplier = jrdn_settings.power.baseMultiplyDrenched;

        if (isCarType && (powerType == 2 || powerType == 3))
        {
            float cur = player.GetHealth("", "Shock");
            float max = player.GetMaxHealth("", "Shock");
            if (max <= 0.0) return;

            float dryTarget = jrdn_settings.power.baseDry;
            float wetTarget = jrdn_settings.power.baseWet;

            if (!toolPreferred)
            {
                dryTarget = dryTarget + jrdn_settings.tools.notPreferredFixed;
                wetTarget = wetTarget + jrdn_settings.tools.notPreferredFixed;

                if (dryTarget < 0.0) dryTarget = 0.0;
                if (wetTarget < 0.0) wetTarget = 0.0;
            }

            float target = dryTarget;
            if (wetnessValue_Read >= GameConstants.STATE_WET) target = wetTarget;
            if (target > max) target = max;

            float delta = target - cur;
            player.AddHealth("", "Shock", delta);

            if (GetGame() && GetGame().IsServer()) DropItemInHands(player);
            return;
        }

        float baseMag = 0.0;
        if (powerType == 1) baseMag = base9V;
        else if (powerType == 2) baseMag = baseCar;
        else if (powerType == 3) baseMag = baseTruck;

        if (baseMag <= 0.0) return;

        baseMag = baseMag * toolMul;
        float shockDelta = baseMag * shockWetMultiplier;
        player.AddHealth("", "Shock", -shockDelta);

        if (GetGame() && GetGame().IsServer()) DropItemInHands(player);
    }

    // ---------------------------------------------------------------------
    // PunishCut
    // ---------------------------------------------------------------------
    static bool PunishCut(
        PlayerBase player,
        ItemBase usedTool,
        array<toolCategory> preferredToolList,
        float wetnessValue_Read,
        float baseChance,
        float wetnessScale,
        float healthPenaltyAbs,
        float preferredMultiplier
    )
    {
        float notPreferredMultiplier = jrdn_settings.tools.notPreferredMul;
        
        if (!player) return false;
        if (baseChance < 0.0) baseChance = 0.0;
        if (baseChance > 1.0) baseChance = 1.0;
        if (wetnessScale < 0.0) wetnessScale = 0.0;
        if (wetnessValue_Read < 0.0) wetnessValue_Read = 0.0;
        if (wetnessValue_Read > 1.0) wetnessValue_Read = 1.0;
        if (healthPenaltyAbs < 0.0) healthPenaltyAbs = 0.0;

        toolCategory usedCategory;
        float toolMul = ToolRiskMultiplier(usedTool, preferredToolList, preferredMultiplier, notPreferredMultiplier, usedCategory);

        float gloveMitigation;
        ItemBase gloveItem;
        bool hasGloves = HasGloveProtection(player, gloveMitigation, gloveItem);
        if (!hasGloves) gloveMitigation = 0.0;
        if (gloveMitigation < 0.0) gloveMitigation = 0.0;
        if (gloveMitigation > 1.0) gloveMitigation = 1.0;

        float finalChance = baseChance * (1.0 + (wetnessValue_Read * wetnessScale));
        finalChance = finalChance * toolMul;
        finalChance = finalChance * (1.0 - gloveMitigation);
        if (finalChance > 1.0) finalChance = 1.0;

        float finalDamage = healthPenaltyAbs * toolMul * (1.0 - gloveMitigation);

        float roll = Math.RandomFloat(0.0, 1.0);
        if (roll <= finalChance)
        {
            if (finalDamage > 0.0) player.AddHealth("", "", -finalDamage);
            if (GetGame() && GetGame().IsServer()) DropItemInHands(player);
            return true;
        }
        return false;
    }

    // ---------------------------------------------------------------------
    // Recipe result condition based punishments
    // ---------------------------------------------------------------------
    static void PunishResults(array<ItemBase> results, float wetnessValue_Read, float wetThreshold, int powerType, ItemBase usedTool, array<toolCategory> preferredToolList, float wetPenalty, float poweredPenaltyAbs, float wrongToolPenaltyAbs)
    {
        if (!results) return;
        float totalPenalty = 0.0;
        if (wetnessValue_Read >= 0.0 && wetnessValue_Read >= wetThreshold) totalPenalty = totalPenalty + wetPenalty;
        if (powerType > 0) totalPenalty = totalPenalty + poweredPenaltyAbs;
        if (usedTool)
        {
            toolCategory usedCategory;
            bool preferred = IsPreferredTool(usedTool, preferredToolList, usedCategory);
            if (!preferred) totalPenalty = totalPenalty + wrongToolPenaltyAbs;
        }
        if (totalPenalty <= 0.0) return;
        for (int i = 0; i < results.Count(); i++)
        {
            ItemBase r = results[i];
            if (!r) continue;
            r.AddHealth("", "", -totalPenalty);
        }
    }
}
