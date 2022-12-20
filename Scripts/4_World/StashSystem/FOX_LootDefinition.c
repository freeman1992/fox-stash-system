// Global configuration data class for the stash system
class FOX_LootDefinition
{
    string name;
    ref TStringArray types;
    ref FOX_StashModel model;

    void FOX_LootDefinition(int id)
    {
        this.name = "Some cool name of the definition (not being used in logic)";
        this.types = new ref TStringArray();
        this.model = new ref FOX_StashModel(id);
    }

    void AddType(string type)
    {
        this.types.Insert(type);
    }

    void ~FOX_LootDefinition()
    {
        delete this.types;
        delete this.model;
    }

};