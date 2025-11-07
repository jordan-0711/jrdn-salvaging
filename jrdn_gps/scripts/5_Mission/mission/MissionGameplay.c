modded class MissionGameplay
{
    protected ref NotificationUI m_jrdnNOTIFY;
    protected float m__notifyTimer = 0.0;
    protected bool  m__notifyShown = false;

    void MissionGameplay()
    {
        GetDayZGame().Event_OnRPC.Insert(jrdnRPC);
    }
    
    void jrdnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        if (rpc_type == ERPCsCustom.RPC_JRDN_PLAY_SOUND)
        {
            string soundName;
            if (ctx.Read(soundName))
            {
                EffectSound sound = SEffectManager.PlaySound(soundName, GetGame().GetPlayer().GetPosition());
                if (sound)
                {
                    sound.SetSoundAutodestroy(true);
                }
                else
                {
                    Print("[JGPS][SOUND] Could not play SoundSet '" + soundName + "' (name not found / not a SoundSet).");
                }
            }
        }
    }

    override void OnInit()
    {
        super.OnInit();
        NotificationSystem.InitInstance();
        m_jrdnNOTIFY = null;
        Print("[JGPS][NOTIFY] NotificationSystem initialized.");
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        NotificationSystem.Update(timeslice);

        // Create NotificationUI after HUD is ready
        if (!m_jrdnNOTIFY)
        {
            PlayerBase p = PlayerBase.Cast(GetGame().GetPlayer());
            if (p && GetGame().GetMission() && GetGame().GetMission().GetHud())
            {
                m_jrdnNOTIFY = new NotificationUI();
                Print("[JGPS][NOTIFY] NotificationUI created.");
            }
        }

        if (m_jrdnNOTIFY)
        {
            m_jrdnNOTIFY.Update(timeslice);
        }

        // Test notification after delay
        if (!m__notifyShown && m_jrdnNOTIFY)
        {
            m__notifyTimer += timeslice;
            if (m__notifyTimer >= 4.0)
            {
                m__notifyShown = true;
                NotificationSystem ntfSys = NotificationSystem.GetInstance();
                if (ntfSys)
                {
                    NotificationSystem.AddNotificationExtended(5.0, "JRDN GPS", "Notification system active!", "");
                    Print("[JGPS][NOTIFY] Test notification sent.");
                }
                else
                {
                    Print("[JGPS][NOTIFY] ERROR: NotificationSystem instance is null!");
                }
            }
        }
    }

    void ~MissionGameplay()
    {
        if (GetDayZGame())
        {
            GetDayZGame().Event_OnRPC.Remove(jrdnRPC);
        }

        delete m_jrdnNOTIFY;
        NotificationSystem.CleanupInstance();
        Print("[JGPS][NOTIFY] Cleaned up.");
    }
}