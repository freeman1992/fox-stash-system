class SearchedObjectLogger
{
    static const string PATH = "$profile:\\FoxApo\\StashSystem\\";
    static const string FILE_NAME = "SearchedObjects.log";
    
    protected static FileHandle handle;

    static void Init()
    {
        if (!FileExist(PATH))
        {
            MakeDirectory(PATH);
        }

        handle = OpenFile(PATH + FILE_NAME, FileMode.APPEND);
    }

    static void CloseAfter()
    {
        if (handle != 0) {
            CloseFile(handle);
        }
    }

    static void Log(string message)
    {
        FPrintln(handle, "[ObjectSearch] " + message);
    }

}