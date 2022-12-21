class FOX_StashModel
{
    int _id;
    bool state;
    bool allFromCategory;
    int numFromCategory = 3;
    bool allFromPresets;
    int numFromPresets = 3;
    int globalDelay;
    ref TStringArray categories;
    ref TStringArray presets;
    ref array<ref FOX_StashStatic> staticLoot;
    ref array<ref FOX_LootTrigger> triggers;
    vector positionlock;

    void FOX_StashModel(int id)
    {
        this._id = id;
        this.state = true;
        this.allFromCategory = false;
        this.numFromCategory = 1;
        this.allFromPresets = false;
        this.numFromPresets = 1;
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

    void SetNumFromCategory(int num)
    {
        this.numFromCategory = num;
    }

    void SetNumFromPresets(int num)
    {
        this.numFromPresets = num;
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
