// Preset can be also known as Loadout - pre-defined collection of items related to the one item type
// Attachments and stuff like that can be included
class FOX_LootPreset
{
    string id;
    ref FOX_LootPresetModel model;

    void FOX_LootPreset(string id, FOX_LootPresetModel model)
    {
        this.id = id;
        this.model = model;
    }

    static void Spawn(ref FOX_LootPreset preset, vector position, bool spawnAll)
    {
        FOX_LootManager.SpawnLoot(preset.model.lootType, preset.model.className, position, preset.model);
    }
};

class FOX_LootPresetModel
{

    FOX_ELootType lootType;
    string className;
    ref TStringArray attachments;
    string magazine = "";
    bool spawnAll = true;

    void FOX_LootPresetModel(string className, TStringArray attachments, string magazine = "", FOX_ELootType lootType = FOX_ELootType.Default)
    {
        this.className = className;
        this.attachments = attachments;
        this.magazine = magazine;
        this.lootType = lootType;
    }
};
