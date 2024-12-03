using UnityEditor;
using UnityEngine;

[System.Serializable]
public class GameObjectData
{
    public string ObjectName;  
    public string ObjectType;  
    public object PhysicsComponent;  
    public float[] Position;  
    public float[] Rotation;  
    public float[] Scale;    
}

// Wrapper class to help deserialize arrays
[System.Serializable]
public class Wrapper
{
    public GameObjectData[] Items;  // Array of GameObjectData items
}

public class LevelLoader : EditorWindow
{
    private TextAsset levelFile;  // File reference for level JSON

    [MenuItem("Tools/Level Loader")]
    public static void ShowWindow()
    {
        GetWindow<LevelLoader>("Level Loader");
    }

    private void OnGUI()
    {
        GUILayout.Label("Load Level File", EditorStyles.boldLabel);
        levelFile = (TextAsset)EditorGUILayout.ObjectField("Level File", levelFile, typeof(TextAsset), false);

        if (levelFile != null)
        {
            if (GUILayout.Button("Load Level"))
            {
                LoadLevel(levelFile);
            }
        }
        else
        {
            EditorGUILayout.HelpBox("Drag and drop a .level file here", MessageType.Info);
        }
    }

    private void LoadLevel(TextAsset file)
    {
        if (file == null)
        {
            Debug.LogError("No file selected!");
            return;
        }

        foreach (GameObject obj in Object.FindObjectsOfType<GameObject>())
        {
            DestroyImmediate(obj);
        }

        GameObject camera = new GameObject("Main Camera");
        Camera camComponent = camera.AddComponent<Camera>();
        camera.tag = "MainCamera";
        camComponent.clearFlags = CameraClearFlags.Skybox;
        camera.transform.position = new Vector3(0, 5, -10);
        camera.transform.LookAt(Vector3.zero);

        GameObject light = new GameObject("Directional Light");
        Light lightComponent = light.AddComponent<Light>();
        lightComponent.type = LightType.Directional;
        light.transform.rotation = Quaternion.Euler(50, -30, 0);

        // Wrap the JSON content and deserialize it into a Wrapper object
        Wrapper wrappedData = JsonUtility.FromJson<Wrapper>("{\"Items\":" + file.text + "}");

        if (wrappedData == null || wrappedData.Items == null)
        {
            Debug.LogError("Failed to parse JSON data!");
            return;
        }

        // Create GameObjects from the deserialized data
        foreach (var data in wrappedData.Items)
        {
            CreateGameObject(data);
        }
    }


    private void CreateGameObject(GameObjectData data)
    {
        if (data == null)
        {
            Debug.LogError("GameObjectData is null!");
            return;
        }

        if (string.IsNullOrEmpty(data.ObjectName))
        {
            Debug.LogError("GameObject name is missing!");
            return;
        }

        if (string.IsNullOrEmpty(data.ObjectType))
        {
            Debug.LogError("GameObject type is missing!");
            return;
        }

        if (data.Position == null || data.Rotation == null || data.Scale == null)
        {
            Debug.LogError($"Position, Rotation, or Scale data is missing for GameObject: {data.ObjectName}");
            return;
        }

        GameObject obj;

        // Map the "ObjectType" to a Unity primitive
        switch (data.ObjectType.ToLower())
        {
            case "cube":
                obj = GameObject.CreatePrimitive(PrimitiveType.Cube);
                break;
            case "sphere":
                obj = GameObject.CreatePrimitive(PrimitiveType.Sphere);
                break;
            case "capsule":
                obj = GameObject.CreatePrimitive(PrimitiveType.Capsule);
                break;
            case "cylinder":
                obj = GameObject.CreatePrimitive(PrimitiveType.Cylinder);
                break;
            case "plane":
                obj = GameObject.CreatePrimitive(PrimitiveType.Plane);
                break;
            default:
                Debug.LogWarning($"Unknown ObjectType: {data.ObjectType}");
                return;
        }

        // Set object properties (position, rotation, scale)
        obj.name = data.ObjectName;
        obj.transform.position = new Vector3(data.Position[0], data.Position[1], data.Position[2]);
        obj.transform.eulerAngles = new Vector3(data.Rotation[0], data.Rotation[1], data.Rotation[2]);
        obj.transform.localScale = new Vector3(data.Scale[0], data.Scale[1], data.Scale[2]);
    }
}
