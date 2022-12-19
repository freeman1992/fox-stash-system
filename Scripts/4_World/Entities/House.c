modded class House
{

    bool IsSearchable = true;

    protected FOX_LootManager _lootManager;
    protected static bool _closeAfter = false;
    
    void LoadPoints()
    {
        SearchedObjectLogger.Log("[" + this.GetType() + "][" + GetPosition() + "][" + GetOrientation() + "]");
        IsSearchable = true;
    }

    override void DeferredInit()
    {
        super.DeferredInit();
        if (!GetGame().IsServer() || GetGame().IsClient())
        {
            return;
        }

        if(!GetDayZGame().IsValid(this.GetType()))
        {
            return;
        }

        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.LoadPoints, 500, false);
    }

    override void SetActions()
    {
        super.SetActions();
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