// ===================================================================================
// jrdn_gps_config.c
// Configuration for JRDN GPS Salvaging mod
// ===================================================================================

class jrdn_DebugSettings
{
    bool Enable = true;
    bool TraceWet = true;
    bool TraceTools = true;
    bool TracePower = true;
    bool TracePenalties = true;
    bool TraceRecipes = true;
}

class jrdn_PowerSettings
{
    float base9V = 8.0;
    float baseCar = 40.0;
    float baseTruck = 40.0;
    float baseDry = 50.0;
    float baseWet = 20.0;
    float multiplyDry = 1.0;
    float multiplyDamp = 1.3;
    float multiplyWet = 1.5;
    float multiplySoaking = 2.0;
    float multiplyDrenched = 2.5;
}

class jrdn_CutSettings
{
    float baseChance = 0.2;
    float wetnessScale = 0.9;
    float healthPenalty = 5.0;
}

class jrdn_ToolSettings
{
    float preferredMultiplier = 1.0;
    float notPreferredMultiplier = 1.4;
    float notPreferredFixed = -10.0;
}

class jrdn_WetSettings
{
    bool lockoutAtSoaking = true;
    float combineDryThreshold = 0.1;
}

class jrdn_GearSettings
{
    float gloveMitigation = 0.5;
}

class jrdn_ResultSettings
{
    float wetPenaltyScale = 4.0;
    float wetPenaltyMax = 10.0;
    float wrongToolPenalty = 10.0;
    float poweredPenalty = 0.0;
    bool ruinOnCarBattery = true;
    bool ruinOnTruckBattery = false;
}

class jrdn_NotificationSettings
{
    bool Enable = true;
    float DefaultDuration = 5.0;
    
    // Cutting recipe messages
    string CutTitle = "You Cut Yourself!";
    string CutDetailWet = "The {wetness} {target} slipped and your {tool} cut your {bodypart}!";
    string CutDetailDry = "Your {tool} slipped and cut your {bodypart}!";
    string CutDetailWrongTool = " Using the wrong tool made it worse.";
    string CutDetailResultDamage = " Your {result} took damage too.";
    
    // Electronics recipe messages
    string ShockTitle = "Electric Shock!";
    string ShockDetailLow = "You were shocked working on the {wetness} {target} with your {tool}!";
    string ShockDetailMedium = "You were badly shocked working on the {wetness} {target} with your {tool}!";
    string ShockDetailHigh = "You were severely shocked working on the {wetness} {target} with your {tool}!";
    string ShockDetailWrongTool = " Using the wrong tool made it worse.";
    string ShockDetailResultDestroyed = " The {result} was destroyed.";
    string ShockDetailResultDamaged = " The {result} was damaged.";
}

// Tool category assignments - admins can add modded tools here
class jrdn_ToolCategoryAssignments
{
    ref TStringArray SMALL_BLADE;
    ref TStringArray LARGE_BLADE;
    ref TStringArray AXE;
    ref TStringArray SAW;
    ref TStringArray HAMMER;
    ref TStringArray UTILITY_SCREW;
    ref TStringArray UTILITY_WRENCH;
    ref TStringArray BLUNT;
    ref TStringArray LONG;
    
    void jrdn_ToolCategoryAssignments()
    {
        SMALL_BLADE = new TStringArray;
        SMALL_BLADE.Insert("KitchenKnife");
        SMALL_BLADE.Insert("SteakKnife");
        SMALL_BLADE.Insert("CombatKnife");
        SMALL_BLADE.Insert("HuntingKnife");
        SMALL_BLADE.Insert("Cleaver");
        SMALL_BLADE.Insert("AK_Bayonet");
        SMALL_BLADE.Insert("M9A1_Bayonet");
        SMALL_BLADE.Insert("SNAFU_Kabar");
        
        LARGE_BLADE = new TStringArray;
        LARGE_BLADE.Insert("Msp_VorpalKnife");
        LARGE_BLADE.Insert("KukriKnife");
        LARGE_BLADE.Insert("FangeKnife");
        LARGE_BLADE.Insert("Mosin_Bayonet");
        LARGE_BLADE.Insert("SNAFU_SKS_Bayonet");
        LARGE_BLADE.Insert("Machete");
        LARGE_BLADE.Insert("CrudeMachete");
        LARGE_BLADE.Insert("OrientalMachete");
        
        AXE = new TStringArray;
        AXE.Insert("Hatchet");
        AXE.Insert("WoodAxe");
        AXE.Insert("FirefighterAxe");
        AXE.Insert("FirefighterAxe_Black");
        AXE.Insert("FirefighterAxe_Green");
        AXE.Insert("Pickaxe");
        AXE.Insert("Iceaxe");
        
        SAW = new TStringArray;
        SAW.Insert("HandSaw");
        SAW.Insert("Hacksaw");
        
        HAMMER = new TStringArray;
        HAMMER.Insert("Hammer");
        HAMMER.Insert("MeatTenderizer");
        HAMMER.Insert("SledgeHammer");
        
        UTILITY_SCREW = new TStringArray;
        UTILITY_SCREW.Insert("Screwdriver");
        UTILITY_SCREW.Insert("Pliers");
        UTILITY_SCREW.Insert("Crowbar");
        
        UTILITY_WRENCH = new TStringArray;
        UTILITY_WRENCH.Insert("LugWrench");
        UTILITY_WRENCH.Insert("Wrench");
        UTILITY_WRENCH.Insert("PipeWrench");
        
        BLUNT = new TStringArray;
        BLUNT.Insert("BaseballBat");
        BLUNT.Insert("BarbedBaseballBat");
        BLUNT.Insert("NailedBaseballBat");
        BLUNT.Insert("FryingPan");
        BLUNT.Insert("Mace");
        BLUNT.Insert("Pipe");
        
        LONG = new TStringArray;
        LONG.Insert("FarmingHoe");
        LONG.Insert("Shovel");
        LONG.Insert("FieldShovel");
        LONG.Insert("Pitchfork");
        LONG.Insert("Sword");
    }
}

// Friendly name mappings
class jrdn_FriendlyNames
{
    ref map<string, string> ItemNames;
    ref map<string, string> BodyPartNames;
    ref map<string, string> WetnessDescriptions;
    ref map<string, string> ToolCategoryNouns;
    ref map<string, string> PowerSourceNames;
    
    void jrdn_FriendlyNames()
    {
        ItemNames = new map<string, string>;
        // Add common items - admins can add more
        ItemNames.Insert("Battery9V", "9V battery");
        ItemNames.Insert("CarBattery", "car battery");
        ItemNames.Insert("TruckBattery", "truck battery");
        ItemNames.Insert("CircuitBoard", "circuit board");
        ItemNames.Insert("MetalWire", "metal wire");
        ItemNames.Insert("CopperWire", "copper wire");
        ItemNames.Insert("ElectronicRepairKit", "electronic repair kit");
        ItemNames.Insert("Rope", "rope");
        ItemNames.Insert("MetalPlate", "metal plate");
        
        BodyPartNames = new map<string, string>;
        BodyPartNames.Insert("LeftForeArmRoll", "left forearm");
        BodyPartNames.Insert("RightForeArmRoll", "right forearm");
        BodyPartNames.Insert("LeftArmRoll", "left arm");
        BodyPartNames.Insert("RightArmRoll", "right arm");
        BodyPartNames.Insert("LeftLeg", "left leg");
        BodyPartNames.Insert("RightLeg", "right leg");
        BodyPartNames.Insert("LeftLegRoll", "left leg");
        BodyPartNames.Insert("RightLegRoll", "right leg");
        BodyPartNames.Insert("LeftUpLeg", "left thigh");
        BodyPartNames.Insert("RightUpLeg", "right thigh");
        BodyPartNames.Insert("LeftFoot", "left foot");
        BodyPartNames.Insert("RightFoot", "right foot");
        BodyPartNames.Insert("LeftToeBase", "left toes");
        BodyPartNames.Insert("RightToeBase", "right toes");
        BodyPartNames.Insert("Head", "head");
        BodyPartNames.Insert("Neck", "neck");
        BodyPartNames.Insert("Pelvis", "hip");
        
        WetnessDescriptions = new map<string, string>;
        WetnessDescriptions.Insert("dry", "dry");
        WetnessDescriptions.Insert("damp", "damp");
        WetnessDescriptions.Insert("wet", "wet");
        WetnessDescriptions.Insert("soaking", "soaking wet");
        WetnessDescriptions.Insert("drenched", "drenched");
        
        ToolCategoryNouns = new map<string, string>;
        ToolCategoryNouns.Insert("SMALL_BLADE", "knife");
        ToolCategoryNouns.Insert("LARGE_BLADE", "blade");
        ToolCategoryNouns.Insert("AXE", "axe");
        ToolCategoryNouns.Insert("SAW", "saw");
        ToolCategoryNouns.Insert("HAMMER", "hammer");
        ToolCategoryNouns.Insert("UTILITY_SCREW", "tool");
        ToolCategoryNouns.Insert("UTILITY_WRENCH", "wrench");
        ToolCategoryNouns.Insert("BLUNT", "blunt tool");
        ToolCategoryNouns.Insert("LONG", "long tool");
        
        PowerSourceNames = new map<string, string>;
        PowerSourceNames.Insert("1", "9V battery");
        PowerSourceNames.Insert("2", "car battery");
        PowerSourceNames.Insert("3", "truck battery");
    }
}

// Notification message templates
class jrdn_NotificationMessages
{
    // Cutting recipe messages
    string Cut_WrongTool_Wet = "The {wetness} {ingredient} slipped and your {tool} cut your {bodypart}. Your {result} took damage from using the wrong tool.";
    string Cut_WrongTool_Dry = "Your {tool} slipped while working and cut your {bodypart}. Your {result} took damage from using the wrong tool.";
    string Cut_Wet = "The {wetness} {ingredient} slipped and your {tool} cut your {bodypart}. Your {result} took some damage too.";
    string Cut_Dry = "Your {tool} slipped while working and cut your {bodypart}. Your {result} took some damage too.";
    string Cut_NoResult_Wet = "The {wetness} {ingredient} slipped and your {tool} cut your {bodypart}.";
    string Cut_NoResult_Dry = "Your {tool} slipped while working and cut your {bodypart}.";
    
    string WrongTool_Only = "Using your {tool} damaged the {result}.";
    
    // Electronics recipe messages
    string Shock_Power_Wet_WrongTool = "Your {tool} touched a live wire from the {wetness} {power} and shocked you! The {result} was destroyed from being powered and using the wrong tool.";
    string Shock_Power_Wet = "Your {tool} touched a live wire from the {wetness} {power} and shocked you! The {result} was damaged.";
    string Shock_Power_Dry_WrongTool = "Your {tool} touched a live wire from the {power} and shocked you! The {result} was destroyed from being powered and using the wrong tool.";
    string Shock_Power_Dry = "Your {tool} touched a live wire from the {power} and shocked you! The {result} was damaged.";
    
    string Power_WrongTool = "Working on the powered {ingredient} with your {tool} destroyed the {result}.";
    string Power_Only = "Working on the powered {ingredient} damaged the {result}.";
    
    string Electronics_WrongTool_Only = "Using your {tool} damaged the {result}.";
    
    // Notification titles
    string Title_Cut = "You Cut Yourself!";
    string Title_Shock = "Electric Shock!";
    string Title_Damage = "Component Damaged!";
    string Title_WrongTool = "Wrong Tool!";
}

class jrdn_gps_config
{
    static const string MOD_AUTHOR = "JRDN_GPS";
    static const bool LOAD_ON_SERVER = true;
    static const bool LOAD_ON_CLIENT = false;
    static const bool CLIENT_SAVE_TO_SERVER_IP = false;
    static const bool SYNC_TO_CLIENTS = false;
    
    private const static string ModFolder = "$profile:\\" + MOD_AUTHOR + "\\";
    private const static string ConfigName = "JRDNSalvagingConfig.json";
    private const static string CURRENT_VERSION = "2";
    string ConfigVersion;
    
    ref jrdn_DebugSettings DebugSettings;
    ref jrdn_PowerSettings PowerSettings;
    ref jrdn_CutSettings CutSettings;
    ref jrdn_ToolSettings ToolSettings;
    ref jrdn_WetSettings WetSettings;
    ref jrdn_GearSettings GearSettings;
    ref jrdn_ResultSettings ResultSettings;
    ref jrdn_ToolCategoryAssignments ToolCategories;
    ref jrdn_FriendlyNames FriendlyNames;
    ref jrdn_NotificationMessages NotificationMessages;
    
    void jrdn_gps_config()
    {
        DebugSettings = new jrdn_DebugSettings;
        PowerSettings = new jrdn_PowerSettings;
        CutSettings = new jrdn_CutSettings;
        ToolSettings = new jrdn_ToolSettings;
        WetSettings = new jrdn_WetSettings;
        GearSettings = new jrdn_GearSettings;
        ResultSettings = new jrdn_ResultSettings;
        ToolCategories = new jrdn_ToolCategoryAssignments;
        FriendlyNames = new jrdn_FriendlyNames;
        NotificationMessages = new jrdn_NotificationMessages;
    }
    
    void Load()
    {
        if (GetGame().IsDedicatedServer())
        {
            if (!LOAD_ON_SERVER)
                return;
        }
        
        if (FileExist(ModFolder + ConfigName))
        {
            JsonFileLoader<jrdn_gps_config>.JsonLoadFile(ModFolder + ConfigName, this);
            
            if (ConfigVersion != CURRENT_VERSION)
            {
                JsonFileLoader<jrdn_gps_config>.JsonSaveFile(ModFolder + ConfigName + "_old", this);
                ConfigVersion = CURRENT_VERSION;
                Save();
            }
            else
            {
                Print("[JRDN_GPS] Config loaded successfully");
                return;
            }
        }
        
        ConfigVersion = CURRENT_VERSION;
        Save();
        Print("[JRDN_GPS] Config created with default values");
    }
    
    void Save()
    {
        if (GetGame().IsDedicatedServer())
        {
            if (!LOAD_ON_SERVER)
                return;
        }
        
        if (!FileExist(ModFolder))
        {
            MakeDirectory(ModFolder);
        }
        
        JsonFileLoader<jrdn_gps_config>.JsonSaveFile(ModFolder + ConfigName, this);
    }
}

static jrdn_gps_config GetJRDNConfig()
{
    if (!m_jrdn_gps_config)
    {
        Print("[JRDN_GPS] Initializing config...");
        m_jrdn_gps_config = new jrdn_gps_config();
        m_jrdn_gps_config.Load();
    }
    
    return m_jrdn_gps_config;
}

static ref jrdn_gps_config m_jrdn_gps_config;