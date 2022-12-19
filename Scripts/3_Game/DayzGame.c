modded class DayZGame
{
    protected static ref TStringSet ValidObjects;

    // Sets the collection of all the class names of given objects for object search & loot system
    static void SetObjectSearchObjects(TStringArray objects)
    {

        Print("[ObjectSearch]: Game setting up the objects.");

        if(!ValidObjects)
        {
            ValidObjects = new TStringSet();
        }

        for(int i = 0; i < objects.Count(); i++)
        {
            ValidObjects.Insert(objects[i]);
            Print("[ObjectSearch]: Setting for " + objects[i]);
        }
    }

    // Checks the availability for the object search by given class name of type
    static bool IsValid(string objectClassName)
    {
        int index = ValidObjects.Find(objectClassName);
        if(index < 0)
        {
            return false;
        }

        return true;
    }

};