modded class MissionServer
{
    override void OnInit()
    {
        if (!GetGame().IsServer())
        {
            return;
        }
        super.OnInit();
        FOX_LootManager.GetInstance().Init();
        SearchedObjectLogger.Init();
        
        GetDayZGame().SetObjectSearchObjects(FOX_LootManager.GetInstance().GetValidObjects());
        
        
    }
};
