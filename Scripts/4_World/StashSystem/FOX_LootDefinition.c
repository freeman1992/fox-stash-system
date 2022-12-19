// Global configuration data class for the stash system
class FOX_LootDefinition
{
    ref TStringArray types;
    ref FOX_StashModel model;

    void FOX_LootDefinition(int id)
    {
        this.types = new ref TStringArray();
        this.model = new ref FOX_StashModel(id);
    }

};