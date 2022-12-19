class FOX_LootManager
{

    static const string PATH = "$profile:\\FoxApo";
    static const string FOLDER_NAME = "\\StashSystem";
    static const string FILE_NAME = "\\LootConfig.json";

    ref FOX_LootConfig _config;

    protected static ref TStringSet s_objects;
    protected ref map<int, ref FOX_StashModel> s_stashes;
    protected ref map<string, ref FOX_LootPreset> s_presets;
    protected ref map<string, ref FOX_LootCategory> s_categories;
	protected bool s_isLoaded = false;
    
    // Singleton
    protected static ref FOX_LootManager s_instance;

    void FOX_LootManager()
    {
        Print("[LootManager]: Creating new instance");
    }

    // Initializes a singleton if necessary
    static FOX_LootManager GetInstance()
    {
        if (s_instance == null)
        {
            s_instance = new FOX_LootManager();
        }
        return s_instance;
    }

    void Init()
    {
        if (!FileExist(PATH))
        {
            MakeDirectory(PATH);
        }

        if (!FileExist(PATH + FOLDER_NAME))
        {
            MakeDirectory(PATH + FOLDER_NAME);
        }

        if (!FileExist(PATH + FOLDER_NAME + FILE_NAME))
        {
            Print("[LootManager]: Creating a default config file: " + PATH + FILE_NAME);
            CreateDefaultConfig();
        }else
        {
            Print("[LootManager]: Loading a config file: " + PATH + FILE_NAME);
        }

        JsonFileLoader<FOX_LootConfig>.JsonLoadFile(PATH + FOLDER_NAME + FILE_NAME, _config);

        if (!_config)
        {
            Print("[LootManager]: LootConfig.json is null");
            return;
        }

        InitData();
    }

    void CreateDefaultConfig()
    {
        
        _config = new FOX_LootConfig();
        _config.AddLoot(new FOX_LootDefinition(1));
        _config.AddLoot(new FOX_LootDefinition(33));
        _config.AddCategory(new FOX_LootCategory("tools", {"Hammer", "Hacksaw"}, {"Headtorch"}));
        _config.AddCategory(new FOX_LootCategory("weapons", {"AKM", "AK101", "AK74"}, {"FullAK", "FullM4"}));
        _config.AddPreset(new FOX_LootPreset("Headtorch", new FOX_LootPresetModel("Headtorch_Black", {"Battery9V"})));
        _config.AddPreset(new FOX_LootPreset("FullAK", new FOX_LootPresetModel("AK101", {"Mag_AK101_30Rnd", "PSO1Optic", "AK_Suppressor"})));
        _config.AddPreset(new FOX_LootPreset("FullM4", new FOX_LootPresetModel("M4A1_Green", {"M4_OEBttstck", "Mag_CMAG_40Rnd", "M4_T3NRDSOptic", "M4_Suppressor"})));

        // TODO: Refactor here at the config level and loot definition
        // Adding methods on higher level so not need to direct access of model
        _config.GetLootById(1).model.AddCategory("weapons");
        _config.GetLootById(1).model.AddPreset("FullAK");
        _config.GetLootById(1).model.AddPreset("FullM4");

        _config.GetLootById(33).model.AddCategory("tools");
        _config.GetLootById(33).model.AddPreset("Headtorch");
        
        _config.AddType("Land_dead_spetsnaz_1", 1);
        _config.AddType("Land_Furniture_box_metall_case", 1);
        _config.AddType("Land_Furniture_backpack", 33);
        
        JsonFileLoader<FOX_LootConfig>.JsonSaveFile(PATH + FOLDER_NAME + FILE_NAME, _config);
        Print("[LootManager]: Default config saved: " + PATH + FOLDER_NAME + FILE_NAME);
    }
    
    ref TStringSet GetValidObjects()
    {
        return s_objects;
    }

    void InitData()
    {
        // TODO: Load the data to the instance of LootManager and keep the tracking
        InitObjects(_config.objects);
        // InitPresets(config.presets);
        // InitCategories(config.categories);
        // InitLoot(config.loot);
        Print("[LootManager]: Initialized...");
        s_isLoaded = true;
    }

    void InitObjects(ref TStringArray objects)
    {
        Print("[LootManager]: Init objects");
        if(!s_objects)
        {
            s_objects = new TStringSet();
        }

        for(int i = 0; i < objects.Count(); i++)
        {
            s_objects.Insert(objects[i]);
            Print("[LootManager]: Adding new object to loot manager - " + objects[i]);
        }
    }

    void InitPresets(ref array<ref FOX_LootPreset> presets)
    {
        Print("[LootManager]: Init presets");
        return;
    }

    void InitCategories(ref array<ref FOX_LootCategory> categories)
    {
        Print("[LootManager]: Init categories");
        return;
    }

    void InitStashes(ref array<ref FOX_StashModel> stashes)
    {
        Print("[LootManager]: Init stashes");
        return;
    }

    // LOOT MECHANICS

    void Loot(ref Object object)
    {
        Print("[LootManager]: Looting object." + object.GetType());

        TStringArray lootResult;
        GetLootForType(object.GetType(), lootResult);

        if(!lootResult)
        {
            Print("[LootManager]: No loot found for object: " + object.GetType());
            return;
        }

        if(lootResult.Count() == 0)
        {
            Print("[LootManager]: No loot found for object: " + object.GetType());
            return;
        }

        for(int i = 0; i < lootResult.Count(); i++)
        {
            Print("[LootManager]: Loot result: " + lootResult[i]);
        }
    }
    
    bool GetLootForType(string className, out TStringArray lootTypes)
    {
        Print("[LootManager]: Get loot for type - " + className);
        // TODO: FIX THIS NULL pointer for variable loot
        FOX_StashModel stashModel;
        for(int i = 0; i < _config.loot.Count(); i++)
        {
            if(_config.loot[i].types.Find(className) < 0)
            {
                continue;
            }
            Print("[LootManager]: Found stash ID:" + _config.loot[i].model._id + " for " + className);
            stashModel = _config.loot[i].model;
        }

        if(!stashModel)
        {
            Print("[LootManager]: Could not find a stash model for - " + className);
            return false;
        }

        ValidateLoot(stashModel, lootTypes);
        return true;
    }

    void ValidateLoot(FOX_StashModel model, out TStringArray lootTypes)
    {
        bool spawnPreset = model.presets && model.presets.Count() > 0;
        bool spawnCategory = model.categories && model.categories.Count() > 0;
        bool spawnStatic = model.staticLoot && model.staticLoot.Count() > 0;
        
        if(model.presets && model.presets.Count() > 0)
        {
            string randomPreset = model.presets.GetRandomElement();
            Print("[LootManager]: Getting random element from presets - " + randomPreset);
        }

        if(model.categories && model.categories.Count() > 0)
        {
            string randomCategory = model.categories.GetRandomElement();
            Print("[LootManager]: Getting random element from category - " + randomCategory);
        }
    }

    void SpawnLoot(string itemClassName, bool isPreset = false, int quantity = 1)
    {
        
    }

    

};
