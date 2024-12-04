using UnityEditor;
using UnityEngine;
using System.IO;
using System.Collections.Generic;

public class LevelLoader : EditorWindow
{
    private string filePath;

    [MenuItem("Tools/Level Loader")]
    public static void ShowWindow()
    {
        GetWindow<LevelLoader>("Level Loader");
    }

    private void OnGUI()
    {
        GUILayout.Label("Load Level File", EditorStyles.boldLabel);

        EditorGUILayout.LabelField("Selected File:", filePath ?? "No file selected");

        if (GUILayout.Button("Browse File"))
        {
            filePath = EditorUtility.OpenFilePanel("Select Level File", "", "level");
        }

        if (!string.IsNullOrEmpty(filePath))
        {
            if (GUILayout.Button("Load Level"))
            {
                LoadLevel(filePath);
            }
        }
        else
        {
            EditorGUILayout.HelpBox("Please select a valid .level file to proceed.", MessageType.Info);
        }
    }

    private void LoadLevel(string path)
    {
        if (string.IsNullOrEmpty(path) || !File.Exists(path))
        {
            Debug.LogError("Invalid file path!");
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

        string[] lines = File.ReadAllLines(path);
        ParseLevelData(lines);
    }

    private void ParseLevelData(string[] lines)
    {
        string objectName = "", objectType = "";
        Vector3 position = Vector3.zero, rotation = Vector3.zero, scale = Vector3.one;
        bool hasPhysics = false;
        float mass = 0f, linearDrag = 0f, angularDrag = 0f;
        bool useGravity = false;
        int bodyType = 0;
        List<string> positionConstraints = new List<string>();
        List<string> angularConstraints = new List<string>();

        foreach (string line in lines)
        {
            if (string.IsNullOrWhiteSpace(line)) continue;

            // Parse each line
            if (line.StartsWith("Object Name:"))
            {
                objectName = line.Substring(line.IndexOf(":") + 2);
            }
            else if (line.StartsWith("Object Type:"))
            {
                objectType = line.Substring(line.IndexOf(":") + 2);
            }
            else if (line.StartsWith("Position:"))
            {
                position = ParseVector3(line);
            }
            else if (line.StartsWith("Rotation:"))
            {
                rotation = ParseVector3(line);
            }
            else if (line.StartsWith("Scale:"))
            {
                scale = ParseVector3(line);
            }
            else if (line.StartsWith("Physics:"))
            {
                hasPhysics = line.Substring(line.IndexOf(":") + 2).Trim() == "Yes";
            }
            else if (line.StartsWith("Mass:"))
            {
                mass = float.Parse(line.Substring(line.IndexOf(":") + 2));
            }
            else if (line.StartsWith("Gravity:"))
            {
                useGravity = line.Substring(line.IndexOf(":") + 2).Trim() == "Yes";
            }
            else if (line.StartsWith("BodyType:"))
            {
                bodyType = int.Parse(line.Substring(line.IndexOf(":") + 2));
            }
            else if (line.StartsWith("LinearDrag:"))
            {
                linearDrag = float.Parse(line.Substring(line.IndexOf(":") + 2));
            }
            else if (line.StartsWith("AngularDrag:"))
            {
                angularDrag = float.Parse(line.Substring(line.IndexOf(":") + 2));
            }
            else if (line.StartsWith("Position Constraints:"))
            {
                positionConstraints = ParseConstraints(line);
            }
            else if (line.StartsWith("Angular Constraints:"))
            {
                angularConstraints = ParseConstraints(line);
            }
            else if (line.Trim() == "---")
            {
                // Create the GameObject
                CreateGameObject(objectName, objectType, position, rotation, scale, hasPhysics, mass, linearDrag, angularDrag, useGravity, bodyType, positionConstraints, angularConstraints);

                // Reset values for the next object
                objectName = objectType = "";
                position = rotation = Vector3.zero;
                scale = Vector3.one;
                hasPhysics = false;
                mass = linearDrag = angularDrag = 0f;
                useGravity = false;
                bodyType = 0;
                positionConstraints.Clear();
                angularConstraints.Clear();
            }
        }
    }

    private Vector3 ParseVector3(string line)
    {
        float x, y, z;
        string vectorString = line.Substring(line.IndexOf("(") + 1).Trim(')');
        string[] values = vectorString.Split(',');
        x = float.Parse(values[0]);
        y = float.Parse(values[1]);
        z = float.Parse(values[2]);
        return new Vector3(x, y, z);
    }

    private List<string> ParseConstraints(string line)
    {
        List<string> constraints = new List<string>();
        string constraintsString = line.Substring(line.IndexOf(":") + 2).Trim();
        if (!string.IsNullOrEmpty(constraintsString))
        {
            constraints.AddRange(constraintsString.Split(new[] { ' ', ',' }, System.StringSplitOptions.RemoveEmptyEntries));
        }
        return constraints;
    }

    private void CreateGameObject(string name, string type, Vector3 position, Vector3 rotation, Vector3 scale, bool hasPhysics, float mass, float linearDrag, float angularDrag, bool useGravity, int bodyType, List<string> positionConstraints, List<string> angularConstraints)
    {
        GameObject obj;

        switch (type.ToLower())
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
                Debug.LogWarning($"Unknown ObjectType: {type}");
                return;
        }

        obj.name = name;
        obj.transform.position = position;
        obj.transform.eulerAngles = rotation;
        obj.transform.localScale = scale;

        if (hasPhysics)
        {
            Rigidbody rb = obj.AddComponent<Rigidbody>();
            rb.mass = mass;
            rb.drag = linearDrag;
            rb.angularDrag = angularDrag;
            rb.useGravity = useGravity;
            rb.isKinematic = bodyType == 2;

            rb.constraints = RigidbodyConstraints.None;

            foreach (string constraint in positionConstraints)
            {
                switch (constraint.ToLower())
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

            foreach (string constraint in angularConstraints)
            {
                switch (constraint.ToLower())
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
}
