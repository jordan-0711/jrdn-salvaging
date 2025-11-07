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

class jrdn_gps_config
{
    static const string MOD_AUTHOR = "Jordan";
    static const bool LOAD_ON_SERVER = true;
    static const bool LOAD_ON_CLIENT = false;
    static const bool CLIENT_SAVE_TO_SERVER_IP = false;
    static const bool SYNC_TO_CLIENTS = false;
    
    private const static string ModFolder = "$profile:\\" + "JRDN_Salvaging" + "\\";
    private const static string ConfigName = "JRDN_Salvaging_Config.json";
    private const static string CURRENT_VERSION = "1";
    string ConfigVersion;
    
    ref jrdn_DebugSettings DebugSettings;
    ref jrdn_PowerSettings PowerSettings;
    ref jrdn_CutSettings CutSettings;
    ref jrdn_ToolSettings ToolSettings;
    ref jrdn_WetSettings WetSettings;
    ref jrdn_GearSettings GearSettings;
    ref jrdn_ResultSettings ResultSettings;
    
    void jrdn_gps_config()
    {
        DebugSettings = new jrdn_DebugSettings;
        PowerSettings = new jrdn_PowerSettings;
        CutSettings = new jrdn_CutSettings;
        ToolSettings = new jrdn_ToolSettings;
        WetSettings = new jrdn_WetSettings;
        GearSettings = new jrdn_GearSettings;
        ResultSettings = new jrdn_ResultSettings;
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
                Print("[JRDN_Salvaging] Config loaded successfully");
                return;
            }
        }
        
        ConfigVersion = CURRENT_VERSION;
        Save();
        Print("[JRDN_Salvaging] Config created with default values");
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
        Print("[JRDN_Salvaging] Initializing config...");
        m_jrdn_gps_config = new jrdn_gps_config();
        m_jrdn_gps_config.Load();
    }
    
    return m_jrdn_gps_config;
}

static ref jrdn_gps_config m_jrdn_gps_config;