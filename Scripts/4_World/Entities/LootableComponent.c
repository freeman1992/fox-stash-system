class LootableComponent : Container_Base
{

    string m_name = "";
    bool m_lootable = false;

    void SetAsLootable(string name)
    {
        m_name = name;
        m_lootable = true;
    }

    override void DeferredInit()
    {
        super.DeferredInit();
        Print("[LootableComponent]: " + m_name + " init");
        
    }

};