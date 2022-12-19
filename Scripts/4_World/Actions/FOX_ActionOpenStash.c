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
        // here comes the condition logic
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
        FOX_LootManager.GetInstance().Loot(action_data.m_Target.GetObject());
    }
};