using UnityEditor;
using UnityEditor.AssetImporters;
using UnityEngine;
using System.IO;

[ScriptedImporter(1, "level")]
public class LevelImporter : ScriptedImporter
{
    public override void OnImportAsset(AssetImportContext imported)
    {
        if (!imported.assetPath.EndsWith(".level"))
        {
            return;
        }

        TextAsset subAsset = new TextAsset(File.ReadAllText(imported.assetPath));

        imported.AddObjectToAsset("text", subAsset);
        imported.SetMainObject(subAsset);
    }
}
