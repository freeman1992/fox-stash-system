class FOX_ActionOpenStashCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        m_ActionData.m_ActionComponent = new CAContinuousTime(8);
    }
};

class FOX_ActionOpenStash : ActionContinuousBase
{
    void FOX_ActionOpenStash()
    {
        m_CallbackClass = FOX_ActionOpenStashCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
        m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTObject(1.8);
    }

    override string GetText()
    {
        return "Search";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        // Here comes the condition logic
        House targetObject = House.Cast(target.GetObject());
        if (!targetObject)
        {
            return false;
        }
        if (!targetObject.IsSearchable)
        {
            return false;
        }
        return true;
    }

    // Succesful finish of the action
    override void OnFinishProgressServer(ActionData action_data)
    {
        Print("[LootSystem]: OnFinishProgressServer");
        House targetObject = House.Cast(action_data.m_Target.GetObject());
        if (!targetObject)
        {
            return;
        }
        
        if (!targetObject.IsSearchable)
        {
            return;
        }

        if(!targetObject.IsLootable)
        {
            // FOX_LootManager.SendPlayerMessage(action_data.m_Player, "Stash is already looted.");
            NotificationSystem.SimpleNoticiation("The stash has been already looted.");
            // NotificationSystem.SimpleNoticiation("The stash has been already looted.", "Notification/gui/data/notifications.edds", ARGB(240, 200, 20, 20), 10, PlayerIdentity);
            return;
        }
        NotificationSystem.SimpleNoticiation("Here comes the Santa Claus!");
        // NotificationSystem.SimpleNoticiation("The stash has been already looted.", "Notification/gui/data/notifications.edds", ARGB(164,255,164,1.000), 10, PlayerIdentity);
        FOX_LootManager.GetInstance().Loot(action_data.m_Player, action_data.m_Target.GetObject());
        // Sets the cooldown to be lootable again
        targetObject.SetAsNonLootable(FOX_LootManager.GetInstance().GlobalCooldown);
    }
};