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

class jrdn_WetSettings
{
    bool lockoutAtSoaking = true;
    float combineDryThreshold = 0.1;
}

class jrdn_GearSettings
{
    float gloveMitigation = 0.5;
}

// CHANGED: Now uses percentage damage per wetness level
class jrdn_ResultSettings
{
    float damageWet = 10.0;           // 10% damage when wet (0.5-0.74)
    float damageSoaking = 15.0;       // 15% damage when soaking (0.75-0.89)
    float damageDrenched = 25.0;      // 25% damage when drenched (0.9+)
    float poweredPenalty = 0.0;
    bool ruinOnCarBattery = true;
    bool ruinOnTruckBattery = false;
}

// NEW: Configurable notification messages
class jrdn_NotificationMessages
{
    // Cutting recipe messages
    string cutTitle = "You Cut Yourself!";
    string cutSimple = "Your tool slipped!";
    string cutWithDamage = "Tool slipped and damaged the result";
    
    // Electronics recipe messages
    string shockTitle = "Electric Shock!";
    string shockSimple = "Shocked by power source!";
    string shockWithDamage = "Shocked and result damaged";
    
    // Damage-only messages
    string damageTitle = "Item Damaged";
    string damageWet = "Wet conditions damaged result";
    string damagePowered = "Power source damaged result";
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

class jrdn_gps_config
{
    static const string MOD_AUTHOR = "JRDN_GPS";
    static const bool LOAD_ON_SERVER = true;
    static const bool LOAD_ON_CLIENT = false;
    static const bool CLIENT_SAVE_TO_SERVER_IP = false;
    static const bool SYNC_TO_CLIENTS = false;
    
    private const static string ModFolder = "$profile:\\" + MOD_AUTHOR + "\\";
    private const static string ConfigName = "JRDNSalvagingConfig.json";
    private const static string CURRENT_VERSION = "4";
    string ConfigVersion;
    
    ref jrdn_DebugSettings DebugSettings;
    ref jrdn_PowerSettings PowerSettings;
    ref jrdn_CutSettings CutSettings;
    ref jrdn_WetSettings WetSettings;
    ref jrdn_GearSettings GearSettings;
    ref jrdn_ResultSettings ResultSettings;
    ref jrdn_NotificationMessages NotificationMessages;  // NEW
    ref jrdn_ToolCategoryAssignments ToolCategories;
    
    void jrdn_gps_config()
    {
        DebugSettings = new jrdn_DebugSettings;
        PowerSettings = new jrdn_PowerSettings;
        CutSettings = new jrdn_CutSettings;
        WetSettings = new jrdn_WetSettings;
        GearSettings = new jrdn_GearSettings;
        ResultSettings = new jrdn_ResultSettings;
        NotificationMessages = new jrdn_NotificationMessages;  // NEW
        ToolCategories = new jrdn_ToolCategoryAssignments;
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