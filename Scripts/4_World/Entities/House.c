modded class House
{

    bool IsSearchable = true;

    protected FOX_LootManager _lootManager;
    protected static bool _closeAfter = false;
    
    void LoadPoints()
    {
        Print("[ObjectSearch]: LoadPoints");
        SearchedObjectLogger.Log("[" + this.GetType() + "][" + GetPosition() + "][" + GetOrientation() + "]");
    }

    override void DeferredInit()
    {
        super.DeferredInit();
        if (!GetGame().IsServer() || GetGame().IsClient())
        {
            return;
        }
        
        IsSearchable = GetDayZGame().IsValidSearchable(this.GetType());
        if(!IsSearchable)
        {
            return;
        }

        Print("[ObjectSearch]: " + this.GetType() + " IsSearchable - " + IsSearchable);
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.LoadPoints, 500, false);
    }

    override void SetActions()
    {
        super.SetActions();
        Print("[ObjectSearch]: SetActions - " + this.GetType() + " - " + IsSearchable);
        AddAction(FOX_ActionOpenStash);
    }

    // Investigate more this serialization function
    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(true);
    }

    // Investigate more this serialization function
    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        return true;
    }

};