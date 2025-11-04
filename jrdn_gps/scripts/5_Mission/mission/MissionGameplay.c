modded class MissionGameplay
{
    void MissionGameplay()
    {
        GetDayZGame().Event_OnRPC.Insert(OnRPC);
    }
    
    void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
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
                    // <-- this is the missing visibility
                    Print("[JGPS][SOUND] Could not play SoundSet '" + soundName + "' (name not found / not a SoundSet).");
                }
            }
        }
    }
}