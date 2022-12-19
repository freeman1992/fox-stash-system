class FOX_StashStatic
{
    bool state;
    ref TStringArray types;
    ref TStringArray presets;
    int delay;

    void FOX_StashStatic(bool state, ref TStringArray types, ref TStringArray presets, int delay)
    {
        this.state = state;
        this.types = types;
        this.presets = presets;
        this.delay = delay;
    }

}
