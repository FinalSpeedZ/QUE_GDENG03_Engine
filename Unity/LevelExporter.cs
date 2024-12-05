using UnityEditor;
using UnityEngine;
using System.IO;

public class LevelExporter : EditorWindow
{
    private string filePath = "Assets/Scenes/LevelData.level";

    [MenuItem("Tools/Level Exporter")]
    public static void ShowWindow()
    {
        GetWindow<LevelExporter>("Level Exporter");
    }

    private void OnGUI()
    {
        GUILayout.Label("Export Level Data", EditorStyles.boldLabel);

        EditorGUILayout.LabelField("Current File Path:", filePath);

        if (GUILayout.Button("Select File Path"))
        {
            string selectedPath = EditorUtility.SaveFilePanel("Save Level Data", "Assets/Scenes", "LevelData", "level");
            if (!string.IsNullOrEmpty(selectedPath))
            {
                filePath = selectedPath;
            }
        }

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
        GameObject[] allObjects = GameObject.FindObjectsOfType<GameObject>();

        using (StreamWriter writer = new StreamWriter(path))
        {
            foreach (var obj in allObjects)
            {
                if (obj.CompareTag("MainCamera") || obj.GetComponent<Light>() != null)
                {
                    continue;
                }

                if (obj == null) continue;

                writer.WriteLine($"Object Name: {obj.name}");
                writer.WriteLine($"Object Type: {GetObjectType(obj)}");
                writer.WriteLine($"Position: ({obj.transform.position.x}, {obj.transform.position.y}, {obj.transform.position.z})");
                writer.WriteLine($"Rotation: ({NormalizeAngle(obj.transform.rotation.eulerAngles.x)}, " +
                                 $"{NormalizeAngle(obj.transform.rotation.eulerAngles.y)}, " +
                                 $"{NormalizeAngle(obj.transform.rotation.eulerAngles.z)})");
                writer.WriteLine($"Scale: ({obj.transform.localScale.x * 5}, {obj.transform.localScale.y * 5}, {obj.transform.localScale.z * 5})");

                Rigidbody rb = obj.GetComponent<Rigidbody>();
                if (rb != null)
                {
                    writer.WriteLine($"Physics: Yes");
                    writer.WriteLine($"Mass: {rb.mass}");
                    writer.WriteLine($"Gravity: {(rb.useGravity ? "Yes" : "No")}");
                    writer.WriteLine($"BodyType: {(rb.isKinematic ? 1 : 2)}"); // 0: Kinematic, 2: Dynamic
                    writer.WriteLine($"LinearDrag: {rb.drag}");
                    writer.WriteLine($"AngularDrag: {rb.angularDrag}");

                    var positionConstraints = new System.Collections.Generic.List<string>();
                    if (rb.constraints.HasFlag(RigidbodyConstraints.FreezePositionX)) positionConstraints.Add("X");
                    if (rb.constraints.HasFlag(RigidbodyConstraints.FreezePositionY)) positionConstraints.Add("Y");
                    if (rb.constraints.HasFlag(RigidbodyConstraints.FreezePositionZ)) positionConstraints.Add("Z");
                    writer.WriteLine($"Position Constraints: {string.Join(", ", positionConstraints)}");

                    var angularConstraints = new System.Collections.Generic.List<string>();
                    if (rb.constraints.HasFlag(RigidbodyConstraints.FreezeRotationX)) angularConstraints.Add("X");
                    if (rb.constraints.HasFlag(RigidbodyConstraints.FreezeRotationY)) angularConstraints.Add("Y");
                    if (rb.constraints.HasFlag(RigidbodyConstraints.FreezeRotationZ)) angularConstraints.Add("Z");
                    writer.WriteLine($"Angular Constraints: {string.Join(", ", angularConstraints)}");
                }
                else
                {
                    writer.WriteLine($"Physics: No");
                }

                writer.WriteLine("---");
            }
        }

        AssetDatabase.Refresh();

        Debug.Log($"Level data exported to: {path}");
    }

    private string GetObjectType(GameObject obj)
    {
        if (obj.GetComponent<MeshFilter>() != null)
        {
            string meshName = obj.GetComponent<MeshFilter>().sharedMesh.name;

            if (meshName.Contains("Cube")) return "Cube";
            else if (meshName.Contains("Plane")) return "Plane";
            else if (meshName.Contains("Sphere")) return "Sphere";
            else if (meshName.Contains("Capsule")) return "Capsule";
            else if (meshName.Contains("Cylinder")) return "Cylinder";
            else return "Unknown";
        }
        return "Unknown";
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