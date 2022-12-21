class FOX_LootConfig
{
    // Debug and settings
    bool DebugSearch = true;
    bool DebugPlayers = true;
    bool DebugManager = true;
    //
    // GlobalCooldown (can be set to -1, so the stash is not respawned at all until the next restart)
    //  (miliseconds)
    int GlobalCooldown = 10000;



    // Collections
    ref array<ref FOX_LootDefinition> loot;
    ref array<ref FOX_LootCategory> categories;
    ref array<ref FOX_LootPreset> presets;
    ref TStringArray objects;

    ref SearchDefinition Search;

    void FOX_LootConfig()
    {
        this.DebugSearch = true;
        this.DebugPlayers = true;
        this.DebugManager = true;
        this.GlobalCooldown = 10000;
        this.loot = new ref array<ref FOX_LootDefinition>();
        this.categories = new ref array<ref FOX_LootCategory>();
        this.presets = new ref array<ref FOX_LootPreset>();
        this.objects = new ref TStringArray();
        this.Search = new ref SearchDefinition();
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

    void AddType(string className, int lootId)
    {
        this.objects.Insert(className);
        GetLootById(lootId).AddType(className);
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

class SearchDefinition
{
    string Position;
    int Radius;

    void SearchDefinition()
    {
        this.Position = "0 0 0";
        this.Radius = 0;
    }
}