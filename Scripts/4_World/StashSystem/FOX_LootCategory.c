class FOX_LootCategory
{
    string id;
    ref TStringArray types;   // types class names
    ref TStringArray presets; // ids

    void FOX_LootCategory(string id, TStringArray types, TStringArray presets)
    {
        this.id = id;
        this.types = types;
        this.presets = presets;
    }

    static void Spawn(ref FOX_LootCategory category, vector position, bool spawnAll, int numFromCategory = 1)
    {

        if(!category.types && !category.presets)
        {
            Print("[LootManager]: No types & presets in category: " + category.id);
            return;
        }

        ref FOX_LootPreset preset;
        for(int num = 0; num < numFromCategory; num++)
        {
            if(spawnAll)
            {
            
                for(int t = 0; t < category.types.Count(); t++)
                {
                    FOX_LootManager.SpawnLoot(FOX_ELootType.Default, category.types[t], position);
                }

                for(int p = 0; p < category.presets.Count(); p++)
                {
                
                    if(!FOX_LootManager.GetInstance().TryGetLootPreset(category.presets[p], preset))
                    {
                        continue;
                    }

                    FOX_LootPreset.Spawn(preset, position, true);
                }
            }
            else
            {
                FOX_LootManager.SpawnLoot(FOX_ELootType.Default, category.types.GetRandomElement(), position);
                string presetId = category.presets.GetRandomElement();
                if(!FOX_LootManager.GetInstance().TryGetLootPreset(presetId, preset))
                {
                    return;
                }
                FOX_LootPreset.Spawn(preset, position, false);
            }
        }
        
        
    }
    
}
