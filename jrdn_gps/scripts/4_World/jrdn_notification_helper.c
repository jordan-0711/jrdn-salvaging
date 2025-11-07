// ===================================================================================
// jrdn_notification_helper.c
// Notification system for JRDN GPS Salvaging mod
// ===================================================================================

class jrdn_notification_helper
{
    // Get friendly item name from config, fallback to class name
    static string GetItemFriendlyName(string className)
    {
        jrdn_gps_config cfg = GetJRDNConfig();
        
        if (cfg.FriendlyNames.ItemNames.Contains(className))
        {
            return cfg.FriendlyNames.ItemNames.Get(className);
        }
        
        // Fallback: make class name more readable
        string result = className;
        result.Replace("_", " ");
        return result;
    }
    
    // Get friendly body part name
    static string GetBodyPartFriendlyName(string selection)
    {
        if (selection == "") return "body";
        
        jrdn_gps_config cfg = GetJRDNConfig();
        
        if (cfg.FriendlyNames.BodyPartNames.Contains(selection))
        {
            return cfg.FriendlyNames.BodyPartNames.Get(selection);
        }
        
        return selection;
    }
    
    // Get wetness description from config
    static string GetWetnessDescription(float wetness)
    {
        jrdn_gps_config cfg = GetJRDNConfig();
        string key = "dry";
        
        if (wetness >= GameConstants.STATE_DRENCHED) key = "drenched";
        else if (wetness >= GameConstants.STATE_SOAKING_WET) key = "soaking";
        else if (wetness >= GameConstants.STATE_WET) key = "wet";
        else if (wetness >= GameConstants.STATE_DAMP) key = "damp";
        
        if (cfg.FriendlyNames.WetnessDescriptions.Contains(key))
        {
            return cfg.FriendlyNames.WetnessDescriptions.Get(key);
        }
        
        return key;
    }
    
    // Get tool category noun from config
    static string GetToolNoun(string categoryName)
    {
        jrdn_gps_config cfg = GetJRDNConfig();
        
        if (cfg.FriendlyNames.ToolCategoryNouns.Contains(categoryName))
        {
            return cfg.FriendlyNames.ToolCategoryNouns.Get(categoryName);
        }
        
        return "tool";
    }
    
    // Get power source friendly name
    static string GetPowerSourceName(int powerType)
    {
        jrdn_gps_config cfg = GetJRDNConfig();
        string key = powerType.ToString();
        
        if (cfg.FriendlyNames.PowerSourceNames.Contains(key))
        {
            return cfg.FriendlyNames.PowerSourceNames.Get(key);
        }
        
        return "power source";
    }
    
    // Replace placeholders in message template
    static string BuildMessage(string template, map<string, string> replacements)
    {
        string message = template;
        
        for (int i = 0; i < replacements.Count(); i++)
        {
            string key = replacements.GetKey(i);
            string value = replacements.GetElement(i);
            string placeholder = "{" + key + "}";
            message.Replace(placeholder, value);
        }
        
        return message;
    }
    
    // Send notification for cutting recipe
    static void NotifyCuttingRecipe(PlayerBase player, ItemBase tool, ItemBase ingredient, ItemBase result, bool hadCut, string bleedLocation, bool wrongTool, float wetness)
    {
        if (!player) return;
        
        jrdn_gps_config cfg = GetJRDNConfig();
        
        // If nothing happened, don't notify
        if (!hadCut && !wrongTool) return;
        
        string title = "";
        string message = "";
        float duration = 5.0;
        
        // Build replacement map
        ref map<string, string> replacements = new map<string, string>;
        
        if (tool)
        {
            toolCategory cat = GetToolCategory(tool);
            string catName = GetToolCategoryName(cat);
            replacements.Insert("tool", GetToolNoun(catName));
        }
        
        if (ingredient)
        {
            replacements.Insert("ingredient", GetItemFriendlyName(ingredient.GetType()));
        }
        
        if (result)
        {
            replacements.Insert("result", GetItemFriendlyName(result.GetType()));
        }
        
        if (bleedLocation != "")
        {
            replacements.Insert("bodypart", GetBodyPartFriendlyName(bleedLocation));
        }
        
        replacements.Insert("wetness", GetWetnessDescription(wetness));
        
        bool isWet = (wetness >= GameConstants.STATE_DAMP);
        
        // Select message template based on conditions
        if (hadCut && wrongTool && result)
        {
            title = cfg.NotificationMessages.Title_Cut;
            if (isWet)
                message = BuildMessage(cfg.NotificationMessages.Cut_WrongTool_Wet, replacements);
            else
                message = BuildMessage(cfg.NotificationMessages.Cut_WrongTool_Dry, replacements);
            duration = 6.0;
        }
        else if (hadCut && result)
        {
            title = cfg.NotificationMessages.Title_Cut;
            if (isWet)
                message = BuildMessage(cfg.NotificationMessages.Cut_Wet, replacements);
            else
                message = BuildMessage(cfg.NotificationMessages.Cut_Dry, replacements);
            duration = 6.0;
        }
        else if (hadCut)
        {
            title = cfg.NotificationMessages.Title_Cut;
            if (isWet)
                message = BuildMessage(cfg.NotificationMessages.Cut_NoResult_Wet, replacements);
            else
                message = BuildMessage(cfg.NotificationMessages.Cut_NoResult_Dry, replacements);
            duration = 5.0;
        }
        else if (wrongTool && result)
        {
            title = cfg.NotificationMessages.Title_WrongTool;
            message = BuildMessage(cfg.NotificationMessages.WrongTool_Only, replacements);
            duration = 4.0;
        }
        
        if (message != "")
        {
            NotificationSystem.SendNotificationToPlayerExtended(player, duration, title, message, "");
        }
    }
    
    // Send notification for electronics recipe
    static void NotifyElectronicsRecipe(PlayerBase player, ItemBase tool, ItemBase ingredient, ItemBase result, bool hadShock, int powerType, bool wrongTool, float wetness)
    {
        if (!player) return;
        
        jrdn_gps_config cfg = GetJRDNConfig();
        
        // If nothing happened, don't notify
        if (!hadShock && !wrongTool && powerType == 0) return;
        
        string title = "";
        string message = "";
        float duration = 5.0;
        
        // Build replacement map
        ref map<string, string> replacements = new map<string, string>;
        
        if (tool)
        {
            toolCategory cat = GetToolCategory(tool);
            string catName = GetToolCategoryName(cat);
            replacements.Insert("tool", GetToolNoun(catName));
        }
        
        if (ingredient)
        {
            replacements.Insert("ingredient", GetItemFriendlyName(ingredient.GetType()));
        }
        
        if (result)
        {
            replacements.Insert("result", GetItemFriendlyName(result.GetType()));
        }
        
        if (powerType > 0)
        {
            replacements.Insert("power", GetPowerSourceName(powerType));
        }
        
        replacements.Insert("wetness", GetWetnessDescription(wetness));
        
        bool isWet = (wetness >= GameConstants.STATE_DAMP);
        bool isHighPower = (powerType >= 2);
        
        // Select message template based on conditions
        if (hadShock && powerType > 0 && wrongTool && result)
        {
            title = cfg.NotificationMessages.Title_Shock;
            if (isWet)
                message = BuildMessage(cfg.NotificationMessages.Shock_Power_Wet_WrongTool, replacements);
            else
                message = BuildMessage(cfg.NotificationMessages.Shock_Power_Dry_WrongTool, replacements);
            duration = 7.0;
        }
        else if (hadShock && powerType > 0 && result)
        {
            title = cfg.NotificationMessages.Title_Shock;
            if (isWet)
                message = BuildMessage(cfg.NotificationMessages.Shock_Power_Wet, replacements);
            else
                message = BuildMessage(cfg.NotificationMessages.Shock_Power_Dry, replacements);
            duration = 7.0;
        }
        else if (powerType > 0 && wrongTool && result)
        {
            title = cfg.NotificationMessages.Title_Damage;
            message = BuildMessage(cfg.NotificationMessages.Power_WrongTool, replacements);
            duration = 5.0;
        }
        else if (powerType > 0 && result)
        {
            title = cfg.NotificationMessages.Title_Damage;
            message = BuildMessage(cfg.NotificationMessages.Power_Only, replacements);
            duration = 5.0;
        }
        else if (wrongTool && result)
        {
            title = cfg.NotificationMessages.Title_WrongTool;
            message = BuildMessage(cfg.NotificationMessages.Electronics_WrongTool_Only, replacements);
            duration = 4.0;
        }
        
        if (message != "")
        {
            NotificationSystem.SendNotificationToPlayerExtended(player, duration, title, message, "");
        }
    }
}