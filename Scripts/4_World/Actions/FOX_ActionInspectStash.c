class FOX_ActionInspectStash : ActionInteractBase
{
	void FOX_ActionInspectStash()
	{
        m_FullBody = true;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
        m_Text = "Search";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
        if(!target)
        {
            return false;
        }
        
		return true;
	}
	
    override void OnExecuteServer( ActionData action_data )
	{

        int component_id = action_data.m_Target.GetComponentIndex();
        Object targetObject = action_data.m_Target.GetObject();
        float util = action_data.m_Target.GetUtility();

        string selection = targetObject.GetActionComponentName(component_id);
        Print("[LootSystem]: Component name: " + selection);
        Print("[" + targetObject.GetDisplayName() + "][" + targetObject.GetType() + "] :: " + targetObject + " | util: " + util + " | compIdx: " + component_id + " | compName: " +selection + "| wPos: " + targetObject.GetWorldPosition() );

        


        // int windowPosX = 0;
		// int windowPosY = 50;
        // DbgUI.BeginCleanupScope();
		// DbgUI.Begin("Action Targets", windowPosX, windowPosY);

        // float util = action_data.m_Target.GetUtility();
        // string compName = targetObject.GetActionComponentName(component_id);
        // array<string> compNames = new array<string>;
        // targetObject.GetActionComponentNameList(component_id, compNames);
        // if( compNames.Count() > 0 )
        // {
        //     for ( int c = 0; c < compNames.Count(); c++ )
        //     {
                
        //         DbgUI.Text("[" + targetObject.GetDisplayName() + "][" + targetObject.GetType() + "] :: " + targetObject + " | util: " + util + " | compIdx: " + component_id + " | compName: " + compNames[c] + "| wPos: " + targetObject.GetWorldPosition() );
        //     }
        // }
        // else
        // {
        //     Print("[" + targetObject.GetDisplayName() + "][" + targetObject.GetType() + "] :: " + targetObject + " | util: " + util + " | compIdx: " + component_id + " | compName: " + compName + "| wPos: " + targetObject.GetWorldPosition() );
        //     DbgUI.Text("[" + targetObject.GetDisplayName() + "][" + targetObject.GetType() + "] :: " + targetObject + " | util: " + util + " | compIdx: " + component_id + " | compName: " + compName + "| wPos: " + targetObject.GetWorldPosition() );					
        // }

        // DbgUI.End();
		// DbgUI.EndCleanupScope();

	}
};