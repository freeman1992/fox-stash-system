class CfgPatches
{
    class ObjectSearch
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {
            "DZ_Data",
            "DZ_Scripts"
        };
    };
};

class CfgMods
{
    class ObjectSearch
    {
        name = "ObjectSearch";
        credits = "";
        author = "foxFreeman";
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};
        dir = "ObjectSearch";

        class defs
        {
            class gameScriptModule
			{
				value="";
				files[]= { "ObjectSearch/scripts/3_Game" };
			};
            class worldScriptModule
            {
                value = "";
                files[] = { "ObjectSearch/scripts/4_World" };
            };
			class missionScriptModule
			{
				value="";
				files[]= { "ObjectSearch/scripts/5_Mission" };
			};
        };
    };
};