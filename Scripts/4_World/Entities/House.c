modded class House
{

    bool IsSearchable = true;
    bool IsLootable = false;

    protected static bool _closeAfter = false;
    

    override void DeferredInit()
    {
        super.DeferredInit();

        RegisterNetSyncVariableBool("IsSearchable");
        RegisterNetSyncVariableBool("IsLootable");

        if (!GetGame().IsServer() || GetGame().IsClient())
        {
            return;
        }
        
        IsSearchable = GetDayZGame().IsValidSearchable(this.GetType());
        IsLootable = false;
        SetSynchDirty();
        if(!IsSearchable)
        {
            // If the object is not set in the config, it won't have the action to search
            return;
        }

        SearchedObjectLogger.Log("[" + this.GetType() + "][" + GetPosition() + "][" + GetOrientation() + "]");
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SetAsLootable, 500, false);
    }

    override void SetActions()
    {
        super.SetActions();
        if(IsSearchable){
            AddAction(FOX_ActionOpenStash);
        }
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

    // CUSTOM METHODS
    void SetAsLootable()
    {
        this.IsLootable = true;
        SetSynchDirty();
    }

    void SetAsNonLootable(int milisecondsDelay)
    {
        this.IsLootable = false;
        SetSynchDirty();
        if(milisecondsDelay == -1)
        {
            return;
        }

        if(milisecondsDelay < 0)
        {
            milisecondsDelay *= -1;
        }

        // Sets the delay until the stash is lootable again
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SetAsLootable, milisecondsDelay, false);
    }

};