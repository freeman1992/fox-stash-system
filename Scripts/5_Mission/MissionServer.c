modded class MissionServer
{
    override void OnInit()
    {
        if (!GetGame().IsServer())
        {
            return;
        }
        super.OnInit();
        SearchedObjectLogger.Init();
        FOX_LootManager.GetInstance().Init();
        
        GetDayZGame().SetObjectSearchObjects(FOX_LootManager.GetInstance().GetValidObjects());
        
        
    }
};
