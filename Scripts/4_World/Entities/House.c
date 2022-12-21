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

        // TODO Change this after testing 
        if(this.GetType() == "Land_ds_kpp_building")
        {
            Print("Land_ds_kpp_building extra condition");
            SetLootableComponent(33);
            return;
        }
        else
        {
            IsSearchable = GetDayZGame().IsValidSearchable(this.GetType());
        }

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
        AddAction(FOX_ActionInspectStash);
        // TODO: Remove later 
        if(IsSearchable){
            AddAction(FOX_ActionOpenStash);
        }else
        {
            RemoveAction(FOX_ActionOpenStash);
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

    void SetLootableComponent(int index)
    {
        EntityAI entity = EntityAI.Cast(this);
        Component targetComponent = entity.GetComponent(index, "Lootable component");
        if(targetComponent)
        {
            Print("[LootSystem]: Setting " + targetComponent + " as lootable.");
        }
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