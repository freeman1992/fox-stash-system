modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);
        actions.Insert(FOX_ActionOpenStash);
        actions.Insert(FOX_ActionInspectStash);
    }
}