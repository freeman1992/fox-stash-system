class FOX_LootTrigger
{
    string id;
    bool state;
    int delay;

    void FOX_LootTrigger()
    {
        this.id = "trigger_default";
        this.state = false;
        this.delay = 0;
    }
}