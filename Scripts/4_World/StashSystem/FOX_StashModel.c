class FOX_StashModel
{
    int _id;
    bool state;
    bool allFromCategory;
    bool allFromPresets;
    int globalDelay;
    ref TStringArray categories;
    ref TStringArray presets;
    ref array<ref FOX_StashStatic> staticLoot;
    ref array<ref FOX_LootTrigger> triggers;

    void FOX_StashModel(int id)
    {
        this._id = id;
        this.state = true;
        this.allFromCategory = false;
        this.allFromPresets = false;
        this.globalDelay = 0;
        this.staticLoot = new ref array<ref FOX_StashStatic>();
        this.categories = new ref TStringArray();
        this.presets = new ref TStringArray();
        this.triggers = new ref array<ref FOX_LootTrigger>();
    }

    void SetState(bool state)
    {
        this.state = state;
    }

    void SetDelay(int delay)
    {
        this.globalDelay = delay;
    }

    void AddStaticLoot(bool state, TStringArray types, TStringArray presets, int delay)
    {
        this.staticLoot.Insert(new FOX_StashStatic(state, types, presets, delay));
    }

    void AddCategory(string category)
    {
        this.categories.Insert(category);
    }

    void AddPreset(string preset)
    {
        this.presets.Insert(preset);
    }

};