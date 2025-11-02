modded class PluginRecipesManager
{
    override void RegisterRecipies()
    {
        super.RegisterRecipies();
        RegisterRecipe(new salvageWires);
        RegisterRecipe(new salvagePCBCasing);
        RegisterRecipe(new craftWiredPCB);
        RegisterRecipe(new craftGPS);
    }
}