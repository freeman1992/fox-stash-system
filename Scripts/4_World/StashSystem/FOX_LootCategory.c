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
}