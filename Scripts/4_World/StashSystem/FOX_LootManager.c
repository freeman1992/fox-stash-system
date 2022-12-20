class FOX_LootManager
{

    static const string PATH = "$profile:\\FoxApo";
    static const string FOLDER_NAME = "\\StashSystem";
    static const string FILE_NAME = "\\LootConfig.json";

    ref FOX_LootConfig _config;

    protected ref TStringSet _objects;

    protected ref map<string, ref FOX_LootPreset> _presets;
    protected ref map<string, ref FOX_LootCategory> _categories;
    protected ref map<string, ref FOX_StashModel> _lootDB;
    protected ref map<string, ref array<ref FOX_StashStatic>> _statics;

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
        return _objects;
    }

    void InitData()
    {
        // TODO: Load the data to the instance of LootManager and keep the tracking
        InitObjects(_config.objects);
        // TODO: Load the loot stashes into the loot manager as copy 
        InitLoot(_config.loot);
        // TODO: Load the presets (make copies from the config to LootManager)
        InitPresets(_config.presets);
        // TODO: Load the categories (make copies from the config to LootManager)
        InitCategories(_config.categories);
        // TODO: Load static definitions by stash id
        Print("[LootManager]: Initialized...");
        s_isLoaded = true;
    }

    void InitObjects(ref TStringArray objects)
    {
        Print("[LootManager]: Init objects");
        if(!_objects)
        {
            _objects = new TStringSet();
        }

        for(int i = 0; i < objects.Count(); i++)
        {
            _objects.Insert(objects[i]);
            Print("[LootManager]: Adding new object to loot manager - " + objects[i]);
        }
    }

    void InitLoot(ref array<ref FOX_LootDefinition> loot)
    {
        Print("[LootManager]: Init loot");
        if(!_lootDB)
        {
            _lootDB = new map<string, ref FOX_StashModel>();
        }

        Print("[LootManager]: Init loot for " + loot.Count() + " loot definitions");

        for(int i = 0; i < loot.Count(); i++)
        {
            for(int k = 0; k < loot[i].types.Count(); k++)
            {
                Print("[LootManager]: Loading loot stash with id " + loot[i].model._id + "  for " + loot[i].types[k]);
                _lootDB.Insert(loot[i].types[k], loot[i].model);
            }
        }
    }

    void InitCategories(ref array<ref FOX_LootCategory> categories)
    {
        Print("[LootManager]: Init categories");
        if(!_categories)
        {
            _categories = new map<string, ref FOX_LootCategory>();
        }

        for(int i = 0; i < categories.Count(); i++)
        {
            _categories.Insert(categories[i].id, categories[i]);
            Print("[LootManager]: Adding new category to loot manager - " + categories[i].id);
        }
    }

    void InitPresets(ref array<ref FOX_LootPreset> presets)
    {
        Print("[LootManager]: Init presets");
        if(!_presets)
        {
            _presets = new map<string, ref FOX_LootPreset>();
        }

        for(int i = 0; i < presets.Count(); i++)
        {
            _presets.Insert(presets[i].id, presets[i]);
            Print("[LootManager]: Adding new preset to loot manager - " + presets[i].id);
        }
    }



    // Looting mechanic
    void Loot(ref Object object)
    {
        Print("[LootManager]: Looting object." + object.GetType());

        if(!_lootDB)
        {
            Print("[LootManager]: No loot db initialized!");
            return;
        }

        FOX_StashModel stashModel = _lootDB.Get(object.GetType());
        if(!stashModel)
        {
            Print("[LootManager]: No loot stash for given type: " + object.GetType());
            return;
        }
       
        vector lootPosition = object.GetPosition();
        ValidateLoot(stashModel, lootPosition);
    }
    

    void ValidateLoot(ref FOX_StashModel model, vector position)
    {
        bool spawnPreset = model.presets && model.presets.Count() > 0;
        bool spawnCategory = model.categories && model.categories.Count() > 0;
        bool spawnStatic = model.staticLoot && model.staticLoot.Count() > 0;
        
        if(model.presets && model.presets.Count() > 0)
        {
            for(int i = 0; i < model.presets.Count(); i++)
            {
                ref FOX_LootPreset preset;
                if(!TryGetLootPreset(model.presets[i], preset))
                {
                    continue;
                }

                SpawnPreset(preset, position, model.allFromPresets);
            }
        }

        if(model.categories && model.categories.Count() > 0)
        {
            for(int c = 0; c < model.categories.Count(); c++)
            {
                ref FOX_LootCategory category;
                if(!TryGetCategory(model.categories[c], category))
                {
                    continue;
                }
                SpawnCategory(category, position, model.allFromCategory);
            }
        }

        if(model.staticLoot && model.staticLoot.Count() > 0)
        {
            for(int s = 0; s < model.staticLoot.Count(); s++)
            {
                SpawnStatic(model.staticLoot[s], position);
            }
        }
    }
    // Spawns the static loot everytime
    void SpawnStatic(ref FOX_StashStatic staticStash, vector position)
    {
        FOX_StashStatic.Spawn(staticStash, position);
    }

    // Spawns the item from the category or all, if the given parameter is true
    void SpawnCategory(ref FOX_LootCategory category, vector position, bool spawnAll = false)
    {
        FOX_LootCategory.Spawn(category, position, spawnAll);
    }

    void SpawnPreset(ref FOX_LootPreset preset, vector position, bool spawnAll = false)
    {
        FOX_LootPreset.Spawn(preset, position, spawnAll);
    }


    static void SpawnLoot(string className, vector position)
    {
        Print("[LootManager]: Spawning item " + className + " on position: " + position);
        ItemBase item = ItemBase.Cast(GetGame().CreateObjectEx(className, position, ECE_PLACE_ON_SURFACE ));
    }



    // Getters

    bool TryGetLootPreset(string id, out FOX_LootPreset preset)
    {
        preset = null;
        if(!_presets)
        {
            return false;
        }

        preset = _presets.Get(id);
        return true;
    }

    bool TryGetCategory(string id, out ref FOX_LootCategory category)
    {
        category = null;
        if(!_categories)
        {
            return false;
        }

        category = _categories.Get(id);
        return true;
    }

    

};
