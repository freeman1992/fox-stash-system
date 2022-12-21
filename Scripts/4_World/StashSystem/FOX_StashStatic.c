class FOX_StashStatic
{
    bool state;
    ref TStringArray types;
    ref TStringArray presets;
    int delay;

    void FOX_StashStatic(bool state, ref TStringArray types, ref TStringArray presets, int delay)
    {
        this.state = state;
        this.types = types;
        this.presets = presets;
        this.delay = delay;
    }

    // Spawning implementation of the static stash
    static void Spawn(ref FOX_StashStatic staticStash, vector position)
    {
        for(int i = 0; i < staticStash.types.Count(); i++)
        {
            Print("[LootManager]: Spawning type: " + staticStash.types[i] + " from static stash on " + position);
            FOX_LootManager.SpawnLoot(FOX_ELootType.Default, staticStash.types[i], position);
        }
        
        ref FOX_LootPreset preset;
        for(int p = 0; p < staticStash.presets.Count(); p++)
        {
            Print("[LootManager]: Spawning preset: " + staticStash.presets[i] + " from static stash on " + position);
            if(!FOX_LootManager.GetInstance().TryGetLootPreset(staticStash.presets[i], preset))
            {
                continue;
            }

            FOX_LootPreset.Spawn(preset, position, true);
        }
    }

}
