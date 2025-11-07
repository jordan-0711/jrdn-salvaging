class jrdn_notification_helper
{
    // Get tool category from item
    static int GetToolCategory(ItemBase tool)
    {
        if (!tool) return 0;
        
        string toolType = tool.GetType();
        toolType.ToLower();
        
        // Cutting tools
        if (toolType.Contains("knife") || toolType.Contains("machete") || toolType.Contains("axe") || 
            toolType.Contains("hatchet") || toolType.Contains("saw") || toolType.Contains("blade"))
        {
            return 1; // Cutting
        }
        
        // Impact tools
        if (toolType.Contains("hammer") || toolType.Contains("wrench") || toolType.Contains("pliers") ||
            toolType.Contains("screwdriver"))
        {
            return 2; // Impact
        }
        
        // Prying tools
        if (toolType.Contains("crowbar") || toolType.Contains("pry"))
        {
            return 3; // Prying
        }
        
        return 0; // Unknown
    }
    
    // Send shock notification to player
    static void NotifyShock(PlayerBase player, float wetness, ItemBase item, int powerType)
    {
        if (!player) return;
        
        string wetnessDesc = jrdn_FriendlyNames.GetWetnessDescription(wetness);
        string itemName = "";
        string powerDesc = "";
        
        if (item)
        {
            itemName = jrdn_FriendlyNames.GetItemFriendlyName(item.GetType());
        }
        
        if (powerType == 1)
        {
            powerDesc = "low-power";
        }
        else if (powerType == 2)
        {
            powerDesc = "medium-power";
        }
        else if (powerType == 3)
        {
            powerDesc = "high-power";
        }
        
        string title = "Electric Shock!";
        string detail = "";
        
        // Build message based on wetness and power
        if (itemName != "")
        {
            detail = "You were shocked working on the " + wetnessDesc + " " + powerDesc + " " + itemName + "!";
        }
        else
        {
            detail = "You were shocked by the " + wetnessDesc + " " + powerDesc + " components!";
        }
        
        if (powerType >= 2)
        {
            detail = detail + " The shock was severe.";
        }
        
        float duration = 5.0;
        if (powerType == 2 || powerType == 3) duration = 7.0;
        
        NotificationSystem.SendNotificationToPlayerExtended(player, duration, title, detail, "");
    }
    
    // Send wrong tool notification to player
    static void NotifyWrongTool(PlayerBase player, ItemBase tool, ItemBase target)
    {
        if (!player) return;
        
        string toolNoun = jrdn_FriendlyNames.GetToolNoun(GetToolCategory(tool));
        string targetName = "";
        
        if (target)
        {
            targetName = jrdn_FriendlyNames.GetItemFriendlyName(target.GetType());
        }
        
        string title = "Wrong Tool!";
        string detail = "";
        
        if (targetName != "")
        {
            detail = "Using your " + toolNoun + " damaged the " + targetName + ".";
        }
        else
        {
            detail = "Using your " + toolNoun + " damaged the components.";
            if (tool && tool.GetHealth() < tool.GetMaxHealth())
            {
                detail = detail + " Your tool was also damaged.";
            }
        }
        
        NotificationSystem.SendNotificationToPlayerExtended(player, 4.0, title, detail, "");
    }
    
    // Send power damage notification to player
    static void NotifyPowerDamage(PlayerBase player, ItemBase item, int powerType)
    {
        if (!player) return;
        
        string itemName = "";
        string powerDesc = "";
        
        if (item)
        {
            itemName = jrdn_FriendlyNames.GetItemFriendlyName(item.GetType());
        }
        
        if (powerType == 1)
        {
            powerDesc = "low-power";
        }
        else if (powerType == 2)
        {
            powerDesc = "medium-power";
        }
        else if (powerType == 3)
        {
            powerDesc = "high-power";
        }
        
        string title = "Component Damaged!";
        string detail = "";
        
        if (itemName != "")
        {
            detail = "Working on the " + powerDesc + " " + itemName + " while powered damaged it.";
            
            if (item.IsRuined())
            {
                detail = detail + " The " + itemName + " was destroyed.";
            }
        }
        else
        {
            detail = "Working on powered components damaged them.";
        }
        
        float duration = 5.0;
        if (powerType == 2 || powerType == 3) duration = 7.0;
        
        NotificationSystem.SendNotificationToPlayerExtended(player, duration, title, detail, "");
    }
    
    // Send cut notification to player
    static void NotifyCut(PlayerBase player, float wetness, ItemBase tool, ItemBase target, string bleedLocation, ItemBase result)
    {
        if (!player) return;
        
        string wetnessDesc = jrdn_FriendlyNames.GetWetnessDescription(wetness);
        string toolNoun = jrdn_FriendlyNames.GetToolNoun(GetToolCategory(tool));
        string targetName = "";
        string bodyPart = jrdn_FriendlyNames.GetBleedLocationFriendly(bleedLocation);
        string resultName = "";
        
        if (target)
        {
            targetName = jrdn_FriendlyNames.GetItemFriendlyName(target.GetType());
        }
        
        if (result)
        {
            resultName = jrdn_FriendlyNames.GetItemFriendlyName(result.GetType());
        }
        
        string title = "You Cut Yourself!";
        string detail = "";
        
        // Build message
        if (targetName != "")
        {
            detail = "The " + wetnessDesc + " " + targetName + " slipped and your " + toolNoun + " cut your " + bodyPart + "!";
        }
        else
        {
            detail = "Your " + toolNoun + " slipped on the " + wetnessDesc + " surface and cut your " + bodyPart + "!";
        }
        
        if (resultName != "")
        {
            detail = detail + " Your " + resultName + " took some damage too.";
        }
        
        NotificationSystem.SendNotificationToPlayerExtended(player, 6.0, title, detail, "");
    }
    
    // Send notification when items are too wet to combine
    static void NotifyTooWetToCombine(PlayerBase player, ItemBase item1, ItemBase item2)
    {
        if (!player) return;
        
        string item1Name = jrdn_FriendlyNames.GetItemFriendlyName(item1.GetType());
        string item2Name = jrdn_FriendlyNames.GetItemFriendlyName(item2.GetType());
        
        string title = "Items Too Wet";
        string detail = "The " + item1Name + " and " + item2Name + " are too wet to combine. Dry them first!";
        
        NotificationSystem.SendNotificationToPlayerExtended(player, 4.0, title, detail, "");
    }
}