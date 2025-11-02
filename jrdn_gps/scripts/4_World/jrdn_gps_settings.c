// ===================================================================================
// jrdn_gps_settings.c
// Read-only global tuning values for Jordan's Recipe Mods.
// ===================================================================================

// Define all settings classes FIRST (outside main class)
class PowerSettings
{
    float base9V    = 8.0;
    float baseCar   = 25.0;
    float baseTruck = 40.0;
    float baseDry = 50.0;
    float baseWet = 20.0;
    float baseMultiplyDry        = 1.0;
    float baseMultiplyDamp       = 1.25;
    float baseMultiplyWet        = 1.50;
    float baseMultiplySoaking    = 2.00;
    float baseMultiplyDrenched   = 2.50;
}

class CutSettings
{
    float baseChance       = 0.15;
    float wetnessScale     = 0.85;
    float healthPenaltyAbs = 5.0;
}

class ToolSettings
{
    float preferredMul          = 1.0;
    float notPreferredMul       = 1.35;
    float notPreferredFixed     = -10.0;
}

class WetSettings
{
    bool lockoutAtSoaking = true;
    float combineDryThreshold = 0.05;
}

class GearSettings
{
    float gloveMitigation = 0.5;
}

class ResultSettings
{
    float wetPenaltyScale     = 4.0;
    float wetPenaltyMax       = 10.0;
    float wrongToolPenaltyAbs = 10.0;
    float poweredPenaltyAbs   = 0.0;
    bool  ruinOnCarBattery    = true;
    bool  ruinOnTruckBattery  = false;
}

// Main settings class references them
class jrdn_settings
{
    static ref PowerSettings power = new PowerSettings;
    static ref CutSettings cut = new CutSettings;
    static ref ToolSettings tools = new ToolSettings;
    static ref WetSettings wet = new WetSettings;
    static ref GearSettings gear = new GearSettings;
    static ref ResultSettings result = new ResultSettings;
}