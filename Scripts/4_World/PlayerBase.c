modded class PlayerBase
{
    override void SetActions()
    {
        super.SetActions();
        AddAction(FOX_ActionOpenStash);
        AddAction(FOX_ActionInspectStash);
    }
}