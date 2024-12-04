using UnityEditor;
using UnityEngine;

[System.Serializable]
public class PhysicsComponent
{
    public string[] AngularConstraints = null;
    public float AngularDrag = 0f;
    public int BodyType = 0;
    public string Gravity = "No";
    public float LinearDrag = 0f;
    public float Mass = 0f;
    public string[] PositionConstraints = null;
    public string Physics = "No"; // Check if physics is enabled
}

[System.Serializable]
public class GameObjectData
{
    public string ObjectName;
    public string ObjectType;
    public PhysicsComponent PhysicsComponent;
    public float[] Position;
    public float[] Rotation;
    public float[] Scale;
}

[System.Serializable]
public class GameObjectDataArray
{
    public GameObjectData[] Objects;
}

public class LevelLoader : EditorWindow
{
    private TextAsset levelFile;  // File reference for level JSON

    [MenuItem("Tools/Level Loader")]
    public static void ShowWindow()
    {
        GetWindow<LevelLoader>("Level Loader");
    }

    private string filePath; // Store the selected file path

    private void OnGUI()
    {
        GUILayout.Label("Load Level File", EditorStyles.boldLabel);

        // Display the current file path
        EditorGUILayout.LabelField("Selected File:", filePath ?? "No file selected");

        // Button to open file browser
        if (GUILayout.Button("Browse File"))
        {
            filePath = EditorUtility.OpenFilePanel("Select Level File", "", "level");
        }

        // Load level if a valid file is selected
        if (!string.IsNullOrEmpty(filePath))
        {
            if (GUILayout.Button("Load Level"))
            {
                TextAsset levelFile = new TextAsset(System.IO.File.ReadAllText(filePath));
                LoadLevel(levelFile);
            }
        }
        else
        {
            EditorGUILayout.HelpBox("Please select a valid .level file to proceed.", MessageType.Info);
        }
    }


    private void LoadLevel(TextAsset file)
    {
        if (file == null)
        {
            Debug.LogError("No file selected!");
            return;
        }

        // Delete all existing GameObjects in the scene
        foreach (GameObject obj in Object.FindObjectsOfType<GameObject>())
        {
            DestroyImmediate(obj);
        }

        // Add a main camera
        GameObject camera = new GameObject("Main Camera");
        Camera camComponent = camera.AddComponent<Camera>();
        camera.tag = "MainCamera";
        camComponent.clearFlags = CameraClearFlags.Skybox;
        camera.transform.position = new Vector3(0, 5, -10);
        camera.transform.LookAt(Vector3.zero);

        // Add a directional light
        GameObject light = new GameObject("Directional Light");
        Light lightComponent = light.AddComponent<Light>();
        lightComponent.type = LightType.Directional;
        light.transform.rotation = Quaternion.Euler(50, -30, 0);

        // Deserialize the JSON directly into an array of GameObjectData objects
        GameObjectDataArray gameObjectDataArray = JsonUtility.FromJson<GameObjectDataArray>(file.text);

        if (gameObjectDataArray == null || gameObjectDataArray.Objects == null)
        {
            Debug.LogError("Failed to parse JSON data!");
            return;
        }

        // Create GameObjects from the deserialized data    
        foreach (var data in gameObjectDataArray.Objects)
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

        // Check if Physics is enabled and PhysicsComponent is provided
        if (data.PhysicsComponent != null && data.PhysicsComponent.Physics == "Yes")
        {
            // Debug log to verify that Physics is enabled
            Debug.Log($"Physics enabled for GameObject: {data.ObjectName}");

            // Add Rigidbody only if Physics is enabled
            Rigidbody rb = obj.AddComponent<Rigidbody>();
            rb.mass = data.PhysicsComponent.Mass;
            rb.drag = data.PhysicsComponent.LinearDrag;
            rb.angularDrag = data.PhysicsComponent.AngularDrag;
            rb.useGravity = data.PhysicsComponent.Gravity == "Yes";
            rb.isKinematic = data.PhysicsComponent.BodyType == 2;

            // Apply position constraints if any
            rb.constraints = RigidbodyConstraints.None;
            if (data.PhysicsComponent.PositionConstraints != null)
            {
                foreach (var axis in data.PhysicsComponent.PositionConstraints)
                {
                    switch (axis.ToLower())
                    {
                        case "x":
                            rb.constraints |= RigidbodyConstraints.FreezePositionX;
                            break;
                        case "y":
                            rb.constraints |= RigidbodyConstraints.FreezePositionY;
                            break;
                        case "z":
                            rb.constraints |= RigidbodyConstraints.FreezePositionZ;
                            break;
                    }
                }
            }

            // Apply angular constraints if any
            if (data.PhysicsComponent.AngularConstraints != null)
            {
                foreach (var axis in data.PhysicsComponent.AngularConstraints)
                {
                    switch (axis.ToLower())
                    {
                        case "x":
                            rb.constraints |= RigidbodyConstraints.FreezeRotationX;
                            break;
                        case "y":
                            rb.constraints |= RigidbodyConstraints.FreezeRotationY;
                            break;
                        case "z":
                            rb.constraints |= RigidbodyConstraints.FreezeRotationZ;
                            break;
                    }
                }
            }
        }
        else
        {
            // Log when physics is disabled
            Debug.Log($"Physics disabled for GameObject: {data.ObjectName}. Skipping Rigidbody.");
        }
    }
}
