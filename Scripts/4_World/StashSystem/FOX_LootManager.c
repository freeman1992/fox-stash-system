class FOX_LootManager
{

    static const string PATH = "$profile:\\FoxApo";
    static const string FOLDER_NAME = "\\StashSystem";
    static const string FILE_NAME = "\\LootConfig.json";

    protected static ref FOX_LootManager s_instance;
    protected static ref FOX_LootConfig s_config;

    protected static TStringSet s_objects;
    protected static map<int, FOX_StashModel> s_stashes;
    protected static map<string, FOX_LootPreset> s_presets;
    protected static map<string, FOX_LootCategory> s_categories;

	protected static bool s_isLoaded = false;

    void LootManager()
    {
        Print("[LootManager]: Creating new instance");
    }

    static FOX_LootManager GetInstance()
    {
        if (s_instance == null)
        {
            s_instance = new LootManager();
        }
        return s_instance;
    }

    static void Init()
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
            CreateDefaultConfig();
        }

        FOX_LootConfig config;
        JsonFileLoader<FOX_LootConfig>.JsonLoadFile(PATH + FOLDER_NAME + FILE_NAME, config);

        if (!config)
        {
            Print("[LootManager]: LootConfig.json is null");
            return;
        }

        InitData(config);
    }

    static void CreateDefaultConfig()
    {
        Print("[LootManager]: Creating a default config file: " + PATH + FILE_NAME);

        FOX_LootDefinition lootDefinition = new FOX_LootDefinition();
        FOX_LootConfig config = new FOX_LootConfig();
        config.AddLoot(new FOX_LootDefinition(1).);
        config.AddLoot(new FOX_LootDefinition(33));
        config.AddCategory(new FOX_LootCategory("tools", {"Hammer", "Hacksaw"}, {"Headtorch"}));
        config.AddCategory(new FOX_LootCategory("weapons", {"AKM", "AK101", "AK74"}, {"FullAK", "FullM4"}));
        config.AddPreset(new FOX_LootPreset("Headtorch", new FOX_LootPresetModel("Headtorch_Black", {"Battery9V"})));
        config.AddPreset(new FOX_LootPreset("FullAK", new FOX_LootPresetModel("AK101", {"Mag_AK101_30Rnd", "PSO1Optic", "AK_Suppressor"})));
        config.AddPreset(new FOX_LootPreset("FullM4", new FOX_LootPresetModel("M4A1_Green", {"M4_OEBttstck", "Mag_CMAG_40Rnd", "M4_T3NRDSOptic", "M4_Suppressor"})));

        config.GetLootById(1).model.AddCategory("weapons");
        config.GetLootById(1).model.AddPreset("FullAK");
        config.GetLootById(1).model.AddPreset("FullM4");

        config.GetLootById(33).model.AddCategory("tools");
        config.GetLootById(33).model.AddCategory("Headtorch");
        
        config.AddObject("Land_Furniture_backpack");
        config.AddObject("Land_dead_spetsnaz_1");
        config.AddObject("Land_Furniture_box_metall_case");
        JsonFileLoader<FOX_LootConfig>.JsonSaveFile(PATH + FOLDER_NAME + FILE_NAME, config);
        Print("[LootManager]: Default config saved: " + PATH + FOLDER_NAME + FILE_NAME);
    }

    static void Loot(Object object)
    {
        Print("[LootManager]: Looting object." + object.GetType());
		GetLootForType(object.GetType());
    }

    static TStringArray GetValidObjects()
    {
        return s_config.objects;
    }

    static bool GetLootForType(string className, out TStringArray lootTypes)
    {
        TStringArray lootTypes = new TStringArray();
        Print("[LootManager]: Get loot for type - " + className);
        FOX_StashModel stashModel;
        for(int i = 0; i < s_config.loot.Count(); i++)
        {
            if(s_config.loot[i].types.Find(className) < 0)
            {
                continue;
            }
            Print("[LootManager]: Found stash ID:" + s_config.loot[i].model._id + " for " + className);
            stashModel = s_config.loot[i].model;
        }

        if(!stashModel)
        {
            Print("[LootManager]: Could not find a stash model for - " + className);
            return false;
        }

        ValidateLoot(stashModel, lootTypes);
        return true
    }

    static void ValidateLoot(FOX_StashModel model, out TStringArray lootTypes)
    {
        if(model.types && model.types.Count() > 0)
        {
            auto element = model.types.GetRandomELement();
            Print("[LootManager]: Getting random element from loot - " + element);
        }
    }

    static void InitData(FOX_LootConfig config)
    {
        InitObjects(config.objects);
        InitPresets(config.presets);
        InitCategories(config.categories);
        InitLoot(config.loot);
        Print("[LootManager]: Initialized...");
		s_isLoaded = true;
    }

    void InitObjects(TStringArray objects)
    {
        Print("[LootManager]: Init objects");
        if(!s_objects)
        {
            s_objects = new TStringSet();
        }

        for(int i = 0; i < objects.Count(); i++)
        {
            s_objects.Insert(objects[i]);
            Print("[LootManager]: Adding new object to loot manager - " + obj);
        }
    }

    void InitPresets(array<FOX_LootPreset> presets)
    {
        Print("[LootManager]: Init presets");
        return;
    }

    void InitCategories(array<FOX_LootCategory> categories)
    {
        Print("[LootManager]: Init categories");
        return;
    }

    void InitStashes(array<FOX_StashModel> stashes)
    {
        Print("[LootManager]: Init stashes");
        return;
    }

};
