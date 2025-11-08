static void jrdn_Dbg(string msg)
{
    if (!GetJRDNConfig().DebugSettings.Enable) return;
    Print("[JRDN] " + msg);
}

static void jrdn_DbgWet(string msg)
{
    if (!GetJRDNConfig().DebugSettings.Enable || !GetJRDNConfig().DebugSettings.TraceWet) return;
    Print("[JRDN] " + msg);
}

static void jrdn_DbgTool(string msg)
{
    if (!GetJRDNConfig().DebugSettings.Enable || !GetJRDNConfig().DebugSettings.TraceTools) return;
    Print("[JRDN] " + msg);
}

static void jrdn_DbgPower(string msg)
{
    if (!GetJRDNConfig().DebugSettings.Enable || !GetJRDNConfig().DebugSettings.TracePower) return;
    Print("[JRDN] " + msg);
}

static void jrdn_DbgPenalty(string msg)
{
    if (!GetJRDNConfig().DebugSettings.Enable || !GetJRDNConfig().DebugSettings.TracePenalties) return;
    Print("[JRDN] " + msg);
}

static void jrdn_DbgRecipe(string msg)
{
    if (!GetJRDNConfig().DebugSettings.Enable || !GetJRDNConfig().DebugSettings.TraceRecipes) return;
    Print("[JRDN] " + msg);
}

enum ERPCsCustom
{
    RPC_JRDN_PLAY_SOUND = 20000,
}

static void PlaySoundOnClients(PlayerBase player, string soundName)
{
    if (!player) return;
    if (!GetGame()) return;
    if (!GetGame().IsServer()) return;
    
    ScriptRPC rpc = new ScriptRPC();
    rpc.Write(soundName);
    rpc.Send(player, ERPCsCustom.RPC_JRDN_PLAY_SOUND, true, player.GetIdentity());
}

// Tool Categories
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
}

toolCategory GetToolCategory(ItemBase tool)
{
    if (!tool) return toolCategory.TOOL_SMALL_BLADE;
    
    string toolName = tool.GetType();
    jrdn_gps_config cfg = GetJRDNConfig();
    jrdn_ToolCategoryAssignments cats = cfg.ToolCategories;
    
    // Check each category from config
    if (cats.SMALL_BLADE && cats.SMALL_BLADE.Find(toolName) >= 0) return toolCategory.TOOL_SMALL_BLADE;
    if (cats.LARGE_BLADE && cats.LARGE_BLADE.Find(toolName) >= 0) return toolCategory.TOOL_LARGE_BLADE;
    if (cats.AXE && cats.AXE.Find(toolName) >= 0) return toolCategory.TOOL_AXE;
    if (cats.SAW && cats.SAW.Find(toolName) >= 0) return toolCategory.TOOL_SAW;
    if (cats.HAMMER && cats.HAMMER.Find(toolName) >= 0) return toolCategory.TOOL_HAMMER;
    if (cats.UTILITY_SCREW && cats.UTILITY_SCREW.Find(toolName) >= 0) return toolCategory.TOOL_UTILITY_SCREW;
    if (cats.UTILITY_WRENCH && cats.UTILITY_WRENCH.Find(toolName) >= 0) return toolCategory.TOOL_UTILITY_WRENCH;
    if (cats.BLUNT && cats.BLUNT.Find(toolName) >= 0) return toolCategory.TOOL_BLUNT;
    if (cats.LONG && cats.LONG.Find(toolName) >= 0) return toolCategory.TOOL_LONG;
    
    return toolCategory.TOOL_SMALL_BLADE;
}

string GetToolCategoryName(toolCategory cat)
{
    if (cat == toolCategory.TOOL_SMALL_BLADE) return "SMALL_BLADE";
    if (cat == toolCategory.TOOL_LARGE_BLADE) return "LARGE_BLADE";
    if (cat == toolCategory.TOOL_AXE) return "AXE";
    if (cat == toolCategory.TOOL_SAW) return "SAW";
    if (cat == toolCategory.TOOL_HAMMER) return "HAMMER";
    if (cat == toolCategory.TOOL_UTILITY_SCREW) return "UTILITY_SCREW";
    if (cat == toolCategory.TOOL_UTILITY_WRENCH) return "UTILITY_WRENCH";
    if (cat == toolCategory.TOOL_BLUNT) return "BLUNT";
    if (cat == toolCategory.TOOL_LONG) return "LONG";
    return "UNKNOWN";
}

class jrdn_helpers
{
    static void PlaySoundOnClients(PlayerBase player, string soundName)
    {
        if (!player) return;
        if (!GetGame()) return;
        if (!GetGame().IsServer()) return;
        
        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(soundName);
        rpc.Send(player, ERPCsCustom.RPC_JRDN_PLAY_SOUND, true, player.GetIdentity());
    }

    static float GetHighestWetness(array<ItemBase> items)
    {
        if (!items) return 0.0;
        
        float highest = 0.0;
        for (int i = 0; i < items.Count(); i++)
        {
            ItemBase item = items[i];
            if (!item) continue;
            
            float wet = item.GetWet();
            if (wet > highest) highest = wet;
        }
        
        return highest;
    }
    
    static bool HasGloves(PlayerBase player)
    {
        if (!player) return false;
        
        EntityAI pe = EntityAI.Cast(player);
        if (!pe || !pe.GetInventory()) return false;
        
        int ac = pe.GetInventory().AttachmentCount();
        for (int i = 0; i < ac; i++)
        {
            EntityAI att = pe.GetInventory().GetAttachmentFromIndex(i);
            if (!att) continue;
            
            ItemBase itm = ItemBase.Cast(att);
            if (!itm) continue;
            
            if (itm.IsKindOf("Gloves"))
                return true;
        }
        
        return false;
    }
    
    static int DetectPowerSource(ItemBase target)
    {
        if (!target) return 0;
        
        EntityAI targetAI = EntityAI.Cast(target);
        if (!targetAI || !targetAI.GetInventory()) return 0;
        
        int count = targetAI.GetInventory().AttachmentCount();
        for (int i = 0; i < count; i++)
        {
            EntityAI attachment = targetAI.GetInventory().GetAttachmentFromIndex(i);
            if (!attachment) continue;
            
            ItemBase attachItem = ItemBase.Cast(attachment);
            if (!attachItem) continue;
            
            if (attachItem.IsKindOf("Battery9V")) return 1;
            if (attachItem.IsKindOf("CarBattery")) return 2;
            if (attachItem.IsKindOf("TruckBattery")) return 3;
        }
        
        return 0;
    }
    
    static void DropItemInHands(PlayerBase player)
    {
        if (!player) return;
        if (!GetGame() || !GetGame().IsServer()) return;
        
        EntityAI inHands = player.GetItemInHands();
        if (!inHands) return;
        
        if (player.ServerDropEntity(inHands))
        {
            jrdn_DbgPower("| > SOUND: Sending combatknife_drop_SoundSet to client");
            PlaySoundOnClients(player, "combatknife_drop_SoundSet");
            
            jrdn_DbgPower("| > Dropped tool from hands: " + inHands.GetType());
        }
        else
        {
            jrdn_DbgPower("| > FAILED to drop tool: " + inHands.GetType());
        }
    }
}

class jrdn_BleedSystem
{
    static ref map<string, ref TStringArray> injuryPools;
    static ref map<int, ref TStringArray> toolCategoryTags;
    static ref array<int> traumaOnlyTools;
    static bool initialized = false;
    
    static void Initialize()
    {
        if (initialized) return;
        initialized = true;
        
        injuryPools = new map<string, ref TStringArray>;
        toolCategoryTags = new map<int, ref TStringArray>;
        traumaOnlyTools = new array<int>;
        
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
        
        ref TStringArray smallBlade = new TStringArray;
        smallBlade.Insert("cutArms");
        toolCategoryTags.Insert(toolCategory.TOOL_SMALL_BLADE, smallBlade);
        
        ref TStringArray largeBlade = new TStringArray;
        largeBlade.Insert("cutArms");
        largeBlade.Insert("cutLegs");
        largeBlade.Insert("cutFeet");
        toolCategoryTags.Insert(toolCategory.TOOL_LARGE_BLADE, largeBlade);
        
        ref TStringArray axe = new TStringArray;
        axe.Insert("cutFeet");
        axe.Insert("cutToes");
        axe.Insert("cutLegs");
        axe.Insert("cutBody");
        toolCategoryTags.Insert(toolCategory.TOOL_AXE, axe);
        
        ref TStringArray saw = new TStringArray;
        saw.Insert("cutLegs");
        saw.Insert("cutFeet");
        toolCategoryTags.Insert(toolCategory.TOOL_SAW, saw);
        
        ref TStringArray longTool = new TStringArray;
        longTool.Insert("cutFeet");
        longTool.Insert("cutToes");
        longTool.Insert("cutLegs");
        longTool.Insert("cutBody");
        toolCategoryTags.Insert(toolCategory.TOOL_LONG, longTool);
        
        traumaOnlyTools.Insert(toolCategory.TOOL_HAMMER);
        traumaOnlyTools.Insert(toolCategory.TOOL_BLUNT);
    }
    
    static bool CanCauseBleed(toolCategory cat)
    {
        Initialize();
        
        for (int i = 0; i < traumaOnlyTools.Count(); i++)
        {
            if (traumaOnlyTools[i] == cat)
                return false;
        }
        
        return true;
    }
    
    static string GetRandomBleedLocation(toolCategory cat)
    {
        Initialize();
        
        if (!CanCauseBleed(cat)) return "";
        
        TStringArray tagList = toolCategoryTags.Get(cat);
        if (!tagList || tagList.Count() == 0) return "";
        
        TStringArray bleedPool = new TStringArray;
        for (int i = 0; i < tagList.Count(); i++)
        {
            string tagName = tagList.Get(i);
            TStringArray selections = injuryPools.Get(tagName);
            if (selections && selections.Count() > 0)
            {
                for (int j = 0; j < selections.Count(); j++)
                {
                    bleedPool.Insert(selections.Get(j));
                }
            }
        }
        
        if (bleedPool.Count() == 0) return "";
        
        int idx = Math.RandomInt(0, bleedPool.Count());
        return bleedPool.Get(idx);
    }
    
    static bool ApplyBleed(PlayerBase player, string selection)
    {
        if (!player) return false;
        if (selection == "") return false;
        if (!player.m_BleedingManagerServer) return false;
        
        return player.m_BleedingManagerServer.AttemptAddBleedingSourceBySelection(selection);
    }
}

static void ProcessCutRisk(PlayerBase player, ItemBase tool, float wetness, string recipeName, out bool hadCut, out string bleedLocation)
{
    hadCut = false;
    bleedLocation = "";
    
    if (!player) return;
    if (!tool) return;
    if (wetness < GameConstants.STATE_DAMP) return;
    
    jrdn_gps_config cfg = GetJRDNConfig();
    
    toolCategory usedCat = GetToolCategory(tool);
    bool hasGloves = jrdn_helpers.HasGloves(player);
    
    jrdn_DbgRecipe(">>>>>>>>>>>>>>>>>>>>");
    jrdn_DbgRecipe("| Cut risk check for " + recipeName);
    jrdn_DbgTool("| > Tool: " + tool.GetType() + " (" + GetToolCategoryName(usedCat) + ")");
    jrdn_DbgTool("| > Gloves: " + hasGloves);
    jrdn_DbgWet("| > Wetness: " + wetness + " (threshold: " + GameConstants.STATE_DAMP + ")");
    
    float gloveMitigation = 0.0;
    if (hasGloves) gloveMitigation = cfg.GearSettings.gloveMitigation;
    
    float baseChance = cfg.CutSettings.baseChance;
    float wetScale = cfg.CutSettings.wetnessScale;
    
    float finalChance = baseChance * (1.0 + (wetness * wetScale));
    finalChance = finalChance * (1.0 - gloveMitigation);
    if (finalChance > 1.0) finalChance = 1.0;
    
    jrdn_DbgPenalty("| > Cut chance: " + (finalChance * 100.0) + "%");
    jrdn_DbgPenalty("| > Base: " + (baseChance * 100.0) + "%");
    jrdn_DbgPenalty("| > Glove mitigation: " + (gloveMitigation * 100.0) + "%");
    
    float roll = Math.RandomFloat(0.0, 1.0);
    if (roll > finalChance)
    {
        jrdn_DbgPenalty("| > No cut (rolled " + (roll * 100.0) + "%)");
        return;
    }
    
    jrdn_DbgPenalty("| > CUT! (rolled " + (roll * 100.0) + "%)");
    hadCut = true;
    
    float damage = cfg.CutSettings.healthPenalty * (1.0 - gloveMitigation);
    if (damage > 0.0)
    {
        player.AddHealth("", "", -damage);
        jrdn_DbgPenalty("| > Applied " + damage + " damage to player");
    }
    
    bleedLocation = jrdn_BleedSystem.GetRandomBleedLocation(usedCat);
    if (bleedLocation != "")
    {
        bool bled = jrdn_BleedSystem.ApplyBleed(player, bleedLocation);
        if (bled)
            jrdn_DbgPenalty("| > Applied bleed at: " + bleedLocation);
    }
    
    jrdn_helpers.DropItemInHands(player);
    jrdn_DbgRecipe(">>>>>>>>>>>>>>>>>>>>");
}

static void ProcessShockRisk(PlayerBase player, ItemBase tool, ItemBase target, float wetness, string recipeName, out bool hadShock, out int powerType)
{
    hadShock = false;
    powerType = 0;
    
    if (!player) return;
    if (!target) return;
    
    powerType = jrdn_helpers.DetectPowerSource(target);
    if (powerType == 0)
    {
        jrdn_DbgPower("| > No power source detected");
        return;
    }
    
    hadShock = true;
    
    jrdn_gps_config cfg = GetJRDNConfig();
    
    string powerName = "Unknown";
    if (powerType == 1) powerName = "Battery9V";
    if (powerType == 2) powerName = "CarBattery";
    if (powerType == 3) powerName = "TruckBattery";

    jrdn_DbgPenalty(">>>>>>>>>>>>>>>>>>>>");
    jrdn_DbgRecipe("| Shock risk check for " + recipeName);
    jrdn_DbgPower("| > Power source: " + powerName + " (type " + powerType + ")");
    jrdn_DbgWet("| > Wetness: " + wetness);
    
    toolCategory usedCat = GetToolCategory(tool);
    jrdn_DbgTool("| > Tool: " + tool.GetType() + " (" + GetToolCategoryName(usedCat) + ")");
    
    float baseShock = 0.0;
    if (powerType == 1) baseShock = cfg.PowerSettings.base9V;
    if (powerType == 2) baseShock = cfg.PowerSettings.baseCar;
    if (powerType == 3) baseShock = cfg.PowerSettings.baseTruck;
    
    float wetMul = cfg.PowerSettings.multiplyDry;
    if (wetness >= GameConstants.STATE_DAMP && wetness < GameConstants.STATE_WET)
        wetMul = cfg.PowerSettings.multiplyDamp;
    else if (wetness >= GameConstants.STATE_WET && wetness < GameConstants.STATE_SOAKING_WET)
        wetMul = cfg.PowerSettings.multiplyWet;
    else if (wetness >= GameConstants.STATE_SOAKING_WET && wetness < GameConstants.STATE_DRENCHED)
        wetMul = cfg.PowerSettings.multiplySoaking;
    else if (wetness >= GameConstants.STATE_DRENCHED)
        wetMul = cfg.PowerSettings.multiplyDrenched;
    
    if (powerType == 2 || powerType == 3)
    {
        jrdn_DbgPower("| > SOUND: Sending defibrillator_shock_SoundSet to client");
        PlaySoundOnClients(player, "defibrillator_shock_SoundSet");
        
        float currentShock = player.GetHealth("", "Shock");
        float maxShock = player.GetMaxHealth("", "Shock");
        
        float targetShock = cfg.PowerSettings.baseDry;
        if (wetness >= GameConstants.STATE_WET) targetShock = cfg.PowerSettings.baseWet;
        
        if (targetShock < 0.0) targetShock = 0.0;
        if (targetShock > maxShock) targetShock = maxShock;
        
        float delta = targetShock - currentShock;
        
        jrdn_DbgPower("| > Car/Truck SET shock: " + currentShock + "->" + targetShock + " (delta:" + delta + ")");
        
        player.SetHealth("", "Shock", targetShock);
    }
    else
    {
        jrdn_DbgPower("| > SOUND: Sending defibrillator_shock_SoundSet to client");
        PlaySoundOnClients(player, "defibrillator_shock_SoundSet");
        
        float shockDamage = baseShock * wetMul;
        jrdn_DbgPower("| > 9V shock: Base:" + baseShock + " WetMul:" + wetMul + "x Damage:" + shockDamage);
        player.AddHealth("", "Shock", -shockDamage);

        float shockAfter = player.GetHealth("", "Shock");
        jrdn_DbgPower("| > Player shock after: " + shockAfter + "/100");
    }
    
    jrdn_DbgPower("| > Applied shock to player");
    
    jrdn_helpers.DropItemInHands(player);
    jrdn_DbgPenalty(">>>>>>>>>>>>>>>>>>>>");
}

static void ProcessCuttingRecipe(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, string recipeName)
{
    if (!GetGame() || !GetGame().IsServer()) return;
    if (!player) return;
    if (!ingredients) return;
    
    ItemBase tool = ingredients[0];
    ItemBase target = ingredients[1];
    
    if (!tool || !target)
    {
        jrdn_DbgRecipe("| > Recipe aborted: missing tool or target");
        return;
    }
    
    float targetHealth = target.GetHealth("", "");
    float targetMaxHealth = target.GetMaxHealth("", "");
    array<ItemBase> wetCheck = new array<ItemBase>;
    wetCheck.Insert(target);
    float wetness = jrdn_helpers.GetHighestWetness(wetCheck);

    jrdn_DbgRecipe("<<<<<<<<<<<<<<< " + recipeName + "  DEBUG START >>>>>>>>>>>>>>>");
    jrdn_DbgRecipe("| > Tool: " + tool.GetType());
    jrdn_DbgRecipe("| > Target: " + target.GetType());
    jrdn_DbgRecipe("| > Health: " + targetHealth + "/" + targetMaxHealth);
    jrdn_DbgRecipe("| > Wet: " + wetness);

    // Track what happened
    bool hadCut = false;
    string bleedLocation = "";
    bool hadResultDamage = false;
    
    // Check for cut
    ProcessCutRisk(player, tool, wetness, recipeName, hadCut, bleedLocation);
    
    // Apply penalties to results and check if they were damaged
    if (results && results.Count() > 0)
    {
        float beforeHealth = results[0].GetHealth("", "");
        ApplyCuttingResultPenalties(results, wetness, recipeName);
        float afterHealth = results[0].GetHealth("", "");
        
        if (afterHealth < beforeHealth)
        {
            hadResultDamage = true;
        }
    }

    // Send ONE notification at the end
    jrdn_notification_helper.NotifyCuttingRecipe(player, hadCut, bleedLocation, hadResultDamage, wetness);

    jrdn_DbgRecipe("<<<<<<<<<<<<<<< " + recipeName + "  DEBUG END >>>>>>>>>>>>>>>");
}

static void ProcessElectronicsRecipe(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, TStringArray possibleResults, string recipeName)
{
    if (!GetGame() || !GetGame().IsServer()) return;
    if (!player) return;
    if (!ingredients) return;
    
    ItemBase tool = ingredients[0];
    ItemBase target = ingredients[1];
    
    if (!tool || !target)
    {
        jrdn_DbgRecipe("| > Recipe aborted: missing tool or target");
        return;
    }
    
    float targetHealth = target.GetHealth("", "");
    float targetMaxHealth = target.GetMaxHealth("", "");
    array<ItemBase> wetCheck = new array<ItemBase>;
    wetCheck.Insert(target);
    float wetness = jrdn_helpers.GetHighestWetness(wetCheck);

    jrdn_DbgRecipe("<<<<<<<<<<<<<<< " + recipeName + "  DEBUG START >>>>>>>>>>>>>>>");
    jrdn_DbgRecipe("| > Tool: " + tool.GetType());
    jrdn_DbgRecipe("| > Target: " + target.GetType());
    jrdn_DbgRecipe("| > Health: " + targetHealth + "/" + targetMaxHealth);
    jrdn_DbgRecipe("| > Wet: " + wetness);
    jrdn_DbgPenalty(">>>>>>>>>>>>>>>>>>>>");
    
    string pickedClass = "";
    if (possibleResults && possibleResults.Count() > 0)
    {
        int idx = Math.RandomInt(0, possibleResults.Count());
        pickedClass = possibleResults.Get(idx);
        jrdn_DbgRecipe("| > Random result picked: " + pickedClass);
    }
    
    bool hadShock = false;
    int powerType = 0;
    bool hadResultDamage = false;
    
    ProcessShockRisk(player, tool, target, wetness, recipeName, hadShock, powerType);
    
    ItemBase spawnedResult = null;
    if (pickedClass != "")
    {
        spawnedResult = SpawnResultAtFeet(player, pickedClass, target, wetness);
        if (spawnedResult)
        {
            jrdn_DbgRecipe("| > Spawned result: " + pickedClass);
            
            float beforeHealth = spawnedResult.GetHealth("", "");
            
            array<ItemBase> resultArray = new array<ItemBase>;
            resultArray.Insert(spawnedResult);
            ApplyElectronicsResultPenalties(resultArray, wetness, target, recipeName);
            
            float afterHealth = spawnedResult.GetHealth("", "");
            if (afterHealth < beforeHealth || spawnedResult.IsRuined())
            {
                hadResultDamage = true;
            }
        }
    }
    
    if (results && results.Count() > 0)
    {
        ItemBase placeholder = results[0];
        if (placeholder) placeholder.Delete();
    }
    
    // Send ONE notification at the end
    jrdn_notification_helper.NotifyElectronicsRecipe(player, hadShock, powerType, hadResultDamage, wetness);
    
    jrdn_DbgRecipe("<<<<<<<<<<<<<<< " + recipeName + "  DEBUG END >>>>>>>>>>>>>>>");
}

static bool CanCombineWet(ItemBase ingredient0, ItemBase ingredient1)
{
    if (!ingredient0 || !ingredient1) return false;
    
    jrdn_gps_config cfg = GetJRDNConfig();
    float threshold = cfg.WetSettings.combineDryThreshold;
    
    array<ItemBase> items = new array<ItemBase>;
    items.Insert(ingredient0);
    items.Insert(ingredient1);
    
    float wetness = jrdn_helpers.GetHighestWetness(items);
    
    if (wetness > threshold)
    {
        return false;
    }
    
    return true;
}

static void ProcessCombineRecipe(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, string recipeName)
{
    if (!GetGame() || !GetGame().IsServer()) return;
    if (!ingredients) return;
    if (!results) return;
    
    jrdn_DbgRecipe("<<<<<<<<<<<<<<< " + recipeName + "  DEBUG START >>>>>>>>>>>>>>>");
    
    array<ItemBase> wetCheck = new array<ItemBase>;
    wetCheck.Insert(ingredients[0]);
    wetCheck.Insert(ingredients[1]);
    
    float wetness = jrdn_helpers.GetHighestWetness(wetCheck);
    jrdn_DbgWet("| > Transferring wetness: " + wetness);
    
    for (int i = 0; i < results.Count(); i++)
    {
        ItemBase result = results[i];
        if (result)
        {
            result.SetWet(wetness);
            jrdn_DbgRecipe("| > Applied wetness to result");
        }
    }
    
    jrdn_DbgRecipe("<<<<<<<<<<<<<<< " + recipeName + "  DEBUG END >>>>>>>>>>>>>>>");
}

// CHANGED: Now uses direct percentage damage based on wetness level
static void ApplyCuttingResultPenalties(array<ItemBase> results, float wetness, string recipeName)
{
    if (!results) return;
    
    jrdn_gps_config cfg = GetJRDNConfig();
    
    // Determine damage percentage based on wetness level
    float damagePercent = 0.0;
    string wetnessLevel = "dry";
    
    if (wetness >= GameConstants.STATE_DRENCHED)
    {
        damagePercent = cfg.ResultSettings.damageDrenched;
        wetnessLevel = "drenched";
    }
    else if (wetness >= GameConstants.STATE_SOAKING_WET)
    {
        damagePercent = cfg.ResultSettings.damageSoaking;
        wetnessLevel = "soaking";
    }
    else if (wetness >= GameConstants.STATE_WET)
    {
        damagePercent = cfg.ResultSettings.damageWet;
        wetnessLevel = "wet";
    }

    jrdn_DbgPenalty(">>>>>>>>>>>>>>>>>>>>");
    jrdn_DbgPenalty("| " + recipeName + " penalties:");
    jrdn_DbgPenalty("| > Wetness level: " + wetnessLevel + " (" + wetness + ")");
    jrdn_DbgPenalty("| > Damage percent: " + damagePercent + "%");
    
    if (damagePercent <= 0.0) return;
    
    for (int i = 0; i < results.Count(); i++)
    {
        ItemBase result = results[i];
        if (!result) continue;
        
        float beforeHealth = result.GetHealth("", "");
        float maxHealth = result.GetMaxHealth("", "");
        
        // Apply percentage damage
        float damageAmount = beforeHealth * (damagePercent / 100.0);
        float targetHealth = beforeHealth - damageAmount;
        if (targetHealth < 0.0) targetHealth = 0.0;
        
        result.SetHealth("", "", targetHealth);
        result.SetWet(wetness);
        float afterHealth = result.GetHealth("", "");
        
        float actualDamagePercent = 0.0;
        if (beforeHealth > 0.0)
        {
            actualDamagePercent = ((beforeHealth - afterHealth) / beforeHealth) * 100.0;
        }
        
        jrdn_DbgPenalty("| > Result " + i + " health: " + beforeHealth + " -> " + afterHealth + " (-" + actualDamagePercent + "%) wet: " + wetness);
    }
}

// CHANGED: Now uses direct percentage damage based on wetness level
static void ApplyElectronicsResultPenalties(array<ItemBase> results, float wetness, ItemBase target, string recipeName)
{
    if (!results) return;
    
    jrdn_gps_config cfg = GetJRDNConfig();
    
    int powerType = jrdn_helpers.DetectPowerSource(target);
    
    // Determine damage percentage based on wetness level
    float damagePercent = 0.0;
    string wetnessLevel = "dry";
    
    if (wetness >= GameConstants.STATE_DRENCHED)
    {
        damagePercent = cfg.ResultSettings.damageDrenched;
        wetnessLevel = "drenched";
    }
    else if (wetness >= GameConstants.STATE_SOAKING_WET)
    {
        damagePercent = cfg.ResultSettings.damageSoaking;
        wetnessLevel = "soaking";
    }
    else if (wetness >= GameConstants.STATE_WET)
    {
        damagePercent = cfg.ResultSettings.damageWet;
        wetnessLevel = "wet";
    }

    jrdn_DbgPenalty(">>>>>>>>>>>>>>>>>>>>");
    jrdn_DbgPenalty("| " + recipeName + " penalties:");
    jrdn_DbgPenalty("| > Wetness level: " + wetnessLevel + " (" + wetness + ")");
    jrdn_DbgPenalty("| > Damage percent: " + damagePercent + "%");
    jrdn_DbgPenalty("| > Power type: " + powerType);
    
    for (int i = 0; i < results.Count(); i++)
    {
        ItemBase result = results[i];
        if (!result) continue;
        
        float beforeHealth = result.GetHealth("", "");
        float maxHealth = result.GetMaxHealth("", "");
        float targetHealth = beforeHealth;
        
        // Check for instant ruin conditions
        if (powerType == 2 && cfg.ResultSettings.ruinOnCarBattery)
        {
            targetHealth = 0.0;
            jrdn_DbgPenalty("| > Result RUINED by car battery flag");
        }
        else if (powerType == 3 && cfg.ResultSettings.ruinOnTruckBattery)
        {
            targetHealth = 0.0;
            jrdn_DbgPenalty("| > Result RUINED by truck battery flag");
        }
        else if (damagePercent > 0.0)
        {
            // Apply percentage damage
            float damageAmount = beforeHealth * (damagePercent / 100.0);
            targetHealth = beforeHealth - damageAmount;
            if (targetHealth < 0.0) targetHealth = 0.0;
        }
        
        result.SetHealth("", "", targetHealth);
        float afterHealth = result.GetHealth("", "");
        
        float actualDamagePercent = 0.0;
        if (beforeHealth > 0.0)
        {
            actualDamagePercent = ((beforeHealth - afterHealth) / beforeHealth) * 100.0;
        }
        
        jrdn_DbgPenalty("| > Result " + i + " health: " + beforeHealth + " -> " + afterHealth + " (-" + actualDamagePercent + "%)");
    }
}

static ItemBase SpawnResultAtFeet(PlayerBase player, string className, ItemBase healthSource, float wetness)
{
    if (!player) return null;
    if (className == "") return null;
    
    vector pos = player.GetPosition();
    EntityAI created = EntityAI.Cast(GetGame().CreateObjectEx(className, pos, ECE_PLACE_ON_SURFACE));
    ItemBase spawned = ItemBase.Cast(created);
    
    if (!spawned)
    {
        if (created) created.Delete();
        return null;
    }
    
    if (healthSource)
    {
        float sourceHealth = healthSource.GetHealth("", "");
        float sourceMax = healthSource.GetMaxHealth("", "");
        if (sourceMax > 0.0)
        {
            float healthPct = sourceHealth / sourceMax;
            float spawnedMax = spawned.GetMaxHealth("", "");
            float newHealth = spawnedMax * healthPct;
            spawned.SetHealth("", "", newHealth);
            jrdn_DbgRecipe("| > Result inherited health: " + (healthPct * 100.0) + "%");
        }
    }
    
    spawned.SetWet(wetness);
    jrdn_DbgRecipe("| > Result wetness applied: " + wetness);
    
    return spawned;
}