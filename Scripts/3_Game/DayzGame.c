modded class DayZGame
{
    ref protected TStringSet ValidObjects;

    // Sets the collection of all the class names of given objects for object search & loot system
    void SetObjectSearchObjects(ref TStringSet objects)
    {

        Print("[ObjectSearch]: Game setting up the objects.");

        if(!ValidObjects)
        {
            this.ValidObjects = objects;
        }

        for(int i = 0; i < this.ValidObjects.Count(); i++)
        {
            Print("[ObjectSearch]: Valid object: " + this.ValidObjects[i]);
        }
    }

    // Checks the availability for the object search by given class name of type
    bool IsValidSearchable(string objectClassName)
    {
        int index = this.ValidObjects.Find(objectClassName);
        if(index < 0)
        {
            return false;
        }

        Print("[ObjectSearch]: IsValidSearchable(" + objectClassName + ") = true")
        return true;
    }

};