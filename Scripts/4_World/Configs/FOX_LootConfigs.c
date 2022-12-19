class FOX_LootConfig
{
    ref array<ref FOX_LootDefinition> loot;
    ref array<ref FOX_LootCategory> categories;
    ref array<ref FOX_LootPreset> presets;
    ref TStringArray objects;

    void FOX_LootConfig()
    {
        this.loot = new ref array<ref FOX_LootDefinition>();
        this.categories = new ref array<ref FOX_LootCategory>();
        this.presets = new ref array<ref FOX_LootPreset>();
        this.objects = new ref TStringArray();
    }

    void AddLoot(FOX_LootDefinition loot)
    {
        this.loot.Insert(loot);
    }

    void AddCategory(FOX_LootCategory category)
    {
        this.categories.Insert(category);
    }

    void AddPreset(FOX_LootPreset preset)
    {
        this.presets.Insert(preset);
    }

    void AddObject(string className)
    {
        this.objects.Insert(className);
    }

    FOX_LootDefinition GetLootById(int id)
    {
        for(int i = 0; i < loot.Count(); i++)
        {
            if(loot[i].model._id != id)
            {
                continue;
            }

            return loot[i];
        }

        return null;
    }

};