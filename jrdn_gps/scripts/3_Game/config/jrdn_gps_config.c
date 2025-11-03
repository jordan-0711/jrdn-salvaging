class jrdn_gps_config
{
    static const string MOD_AUTHOR = "JRDN_GPS";
    static const bool LOAD_ON_SERVER = true;
    static const bool LOAD_ON_CLIENT = false;
    static const bool CLIENT_SAVE_TO_SERVER_IP = false;
    static const bool SYNC_TO_CLIENTS = false;
    
    private const static string ModFolder = "$profile:\\" + MOD_AUTHOR + "\\";
    private const static string ConfigName = "JRDNSalvagingConfig.json";
    private const static string CURRENT_VERSION = "1";
    string CONFIG_VERSION;
    
    bool debug_Enable = true;
    bool debug_TraceWet = true;
    bool debug_TraceTools = true;
    bool debug_TracePower = true;
    bool debug_TracePenalties = true;
    bool debug_TraceRecipes = true;
    
    float power_base9V = 8.0;
    float power_baseCar = 25.0;
    float power_baseTruck = 40.0;
    float power_baseDry = 50.0;
    float power_baseWet = 20.0;
    float power_baseMultiplyDry = 1.0;
    float power_baseMultiplyDamp = 1.25;
    float power_baseMultiplyWet = 1.50;
    float power_baseMultiplySoaking = 2.00;
    float power_baseMultiplyDrenched = 2.50;
    
    float cut_baseChance = 0.15;
    float cut_wetnessScale = 0.85;
    float cut_healthPenaltyAbs = 5.0;
    
    float tools_preferredMul = 1.0;
    float tools_notPreferredMul = 1.35;
    float tools_notPreferredFixed = -10.0;
    
    bool wet_lockoutAtSoaking = true;
    float wet_combineDryThreshold = 0.05;
    
    float gear_gloveMitigation = 0.5;
    
    float result_wetPenaltyScale = 4.0;
    float result_wetPenaltyMax = 10.0;
    float result_wrongToolPenaltyAbs = 10.0;
    float result_poweredPenaltyAbs = 0.0;
    bool result_ruinOnCarBattery = true;
    bool result_ruinOnTruckBattery = false;
    
    void Load()
    {
        SetDefaultValues();
        
        if (GetGame().IsDedicatedServer())
        {
            if (!LOAD_ON_SERVER)
                return;
        }
        
        if (FileExist(ModFolder + ConfigName))
        {
            JsonFileLoader<jrdn_gps_config>.JsonLoadFile(ModFolder + ConfigName, this);
            
            if (CONFIG_VERSION != CURRENT_VERSION)
            {
                JsonFileLoader<jrdn_gps_config>.JsonSaveFile(ModFolder + ConfigName + "_old", this);
            }
            else
            {
                Print("[JRDN_GPS] Config loaded successfully");
                return;
            }
        }
        
        CONFIG_VERSION = CURRENT_VERSION;
        Save();
        Print("[JRDN_GPS] Config created with default values");
    }
    
    void SetDefaultValues()
    {
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