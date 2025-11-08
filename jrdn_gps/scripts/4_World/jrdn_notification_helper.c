// ===================================================================================
// jrdn_notification_helper.c
// REPLACE your existing file
// Location: YourModName/Scripts/4_World/jrdn_notification_helper.c
//
// CHANGED: Now reads all messages from config
// ===================================================================================

class jrdn_notification_helper
{
    // Send notification for cutting recipe
    static void NotifyCuttingRecipe(PlayerBase player, bool hadCut, string bleedLocation, bool hadResultDamage, float wetness)
    {
        if (!player) return;
        
        // If nothing happened, don't notify
        if (!hadCut && !hadResultDamage) return;
        
        jrdn_gps_config cfg = GetJRDNConfig();
        jrdn_NotificationMessages msgs = cfg.NotificationMessages;
        
        string title = "";
        string message = "";
        float duration = 5.0;
        
        // Build the message based on what happened
        if (hadCut && hadResultDamage)
        {
            title = msgs.cutTitle;
            message = msgs.cutWithDamage;
            duration = 6.0;
        }
        else if (hadCut)
        {
            title = msgs.cutTitle;
            message = msgs.cutSimple;
            duration = 5.0;
        }
        else if (hadResultDamage)
        {
            title = msgs.damageTitle;
            message = msgs.damageWet;
            duration = 4.0;
        }
        
        if (message != "")
        {
            NotificationSystem.SendNotificationToPlayerExtended(player, duration, title, message, "");
        }
    }
    
    // Send notification for electronics recipe
    static void NotifyElectronicsRecipe(PlayerBase player, bool hadShock, int powerType, bool hadResultDamage, float wetness)
    {
        if (!player) return;
        
        // If nothing happened, don't notify
        if (!hadShock && !hadResultDamage && powerType == 0) return;
        
        jrdn_gps_config cfg = GetJRDNConfig();
        jrdn_NotificationMessages msgs = cfg.NotificationMessages;
        
        string title = "";
        string message = "";
        float duration = 3.0;
        
        // Build the message based on what happened
        if (hadShock && hadResultDamage)
        {
            title = msgs.shockTitle;
            message = msgs.shockWithDamage;
            duration = 7.0;
        }
        else if (hadShock)
        {
            title = msgs.shockTitle;
            message = msgs.shockSimple;
            duration = 6.0;
        }
        else if (hadResultDamage && powerType > 0)
        {
            title = msgs.damageTitle;
            message = msgs.damagePowered;
            duration = 5.0;
        }
        else if (hadResultDamage)
        {
            title = msgs.damageTitle;
            message = msgs.damageWet;
            duration = 4.0;
        }
        
        if (message != "")
        {
            NotificationSystem.SendNotificationToPlayerExtended(player, duration, title, message, "");
        }
    }
}