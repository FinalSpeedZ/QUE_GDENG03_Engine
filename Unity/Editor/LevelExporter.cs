using UnityEditor;
using UnityEngine;
using System.IO;

public class LevelExporter : EditorWindow
{
    private string filePath = "Assets/Scenes/LevelData.level"; // Default export path

    [MenuItem("Tools/Level Exporter")]
    public static void ShowWindow()
    {
        GetWindow<LevelExporter>("Level Exporter");
    }

    private void OnGUI()
    {
        GUILayout.Label("Export Level Data", EditorStyles.boldLabel);

        // Display current file path
        EditorGUILayout.LabelField("Current File Path:", filePath);

        // Button to open a save file panel
        if (GUILayout.Button("Select File Path"))
        {
            string selectedPath = EditorUtility.SaveFilePanel("Save Level Data", "Assets/Scenes", "LevelData", "level");
            if (!string.IsNullOrEmpty(selectedPath))
            {
                filePath = selectedPath;
            }
        }

        // Export level data
        if (GUILayout.Button("Export Level"))
        {
            if (string.IsNullOrEmpty(filePath))
            {
                Debug.LogError("Please select a valid file path to export the level data.");
            }
            else
            {
                ExportLevel(filePath);
            }
        }
    }

    private void ExportLevel(string path)
    {
        // Gather all the objects in the scene
        GameObject[] allObjects = GameObject.FindObjectsOfType<GameObject>();
        var gameObjectDataList = new System.Collections.Generic.List<GameObjectData>();

        foreach (var obj in allObjects)
        {
            if (obj.CompareTag("MainCamera") || obj.GetComponent<Light>() != null)
            {
                continue;
            }

            if (obj == null) continue;

            GameObjectData data = new GameObjectData
            {
                ObjectName = obj.name,
                Position = new float[] { obj.transform.position.x, obj.transform.position.y, obj.transform.position.z },
                Rotation = new float[] { NormalizeAngle(obj.transform.rotation.eulerAngles.x),
                                     NormalizeAngle(obj.transform.rotation.eulerAngles.y),
                                     NormalizeAngle(obj.transform.rotation.eulerAngles.z) },
                Scale = new float[] { obj.transform.localScale.x, obj.transform.localScale.y, obj.transform.localScale.z }
            };

            // Determine ObjectType based on the type of the object
            if (obj.GetComponent<MeshFilter>() != null)
            {
                string meshName = obj.GetComponent<MeshFilter>().sharedMesh.name;

                if (meshName.Contains("Cube"))
                    data.ObjectType = "Cube";
                else if (meshName.Contains("Plane"))
                    data.ObjectType = "Plane";
                else if (meshName.Contains("Sphere"))
                    data.ObjectType = "Sphere";
                else if (meshName.Contains("Capsule"))
                    data.ObjectType = "Capsule";
                else if (meshName.Contains("Cylinder"))
                    data.ObjectType = "Cylinder";
                else
                    data.ObjectType = "Unknown";
            }
            else
            {
                data.ObjectType = "Unknown";
            }

            // Add physics component data if the object has a Rigidbody
            Rigidbody rb = obj.GetComponent<Rigidbody>();
            if (rb != null)
            {
                data.PhysicsComponent = new PhysicsComponent
                {
                    AngularDrag = rb.angularDrag,
                    BodyType = rb.isKinematic ? 1 : 2,
                    Gravity = rb.useGravity ? "Yes" : "No",
                    LinearDrag = rb.drag,
                    Mass = rb.mass,
                    Physics = "Yes",
                    PositionConstraints = new string[] { },
                    AngularConstraints = new string[] { }
                };

                var positionConstraints = new System.Collections.Generic.List<string>();
                if (rb.constraints.HasFlag(RigidbodyConstraints.FreezePositionX)) positionConstraints.Add("X");
                if (rb.constraints.HasFlag(RigidbodyConstraints.FreezePositionY)) positionConstraints.Add("Y");
                if (rb.constraints.HasFlag(RigidbodyConstraints.FreezePositionZ)) positionConstraints.Add("Z");
                data.PhysicsComponent.PositionConstraints = positionConstraints.ToArray();

                // Collect angular constraints
                var angularConstraints = new System.Collections.Generic.List<string>();
                if (rb.constraints.HasFlag(RigidbodyConstraints.FreezeRotationX)) angularConstraints.Add("X");
                if (rb.constraints.HasFlag(RigidbodyConstraints.FreezeRotationY)) angularConstraints.Add("Y");
                if (rb.constraints.HasFlag(RigidbodyConstraints.FreezeRotationZ)) angularConstraints.Add("Z");
                data.PhysicsComponent.AngularConstraints = angularConstraints.ToArray();
            }

            gameObjectDataList.Add(data);
        }

        // Convert the list to an array
        GameObjectDataArray gameObjectDataArray = new GameObjectDataArray
        {
            Objects = gameObjectDataList.ToArray()
        };

        // Serialize to JSON and write to file
        string json = JsonUtility.ToJson(gameObjectDataArray, true);

        // Write JSON data to the specified file path
        File.WriteAllText(path, json);
        AssetDatabase.Refresh();

        Debug.Log($"Level data exported to: {path}");
    }
    private float NormalizeAngle(float angle)
    {
        if (angle > 180)
        {
            return angle - 360;
        }
        return angle;
    }
}