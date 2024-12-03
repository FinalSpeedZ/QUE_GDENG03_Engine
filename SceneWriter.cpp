#include "SceneWriter.h"
#include <json/json.h>
#include <fstream>

#include "BaseComponentSystem.h"
#include "GameObjectManager.h"
#include "MeshRenderer.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "TextureComponent.h"
#include "Mesh.h"

namespace GDEngine
{
    SceneWriter::SceneWriter(std::string directory)
    {
        m_directory = directory;
    }

    SceneWriter::~SceneWriter()
    {
    }

    void SceneWriter::writeToFile()
    {
        std::string fileDirectory = m_directory + ".level";
        if (m_directory.find(".level") != std::string::npos)
        {
            fileDirectory = m_directory; // Use directory as file name if it contains .level
        }

        std::ofstream sceneFile(fileDirectory);
        if (!sceneFile.is_open())
        {
            Logger::log("Failed to open file for writing: " + fileDirectory);
            return;
        }

        Logger::log("Writing scene to file: " + fileDirectory);

        GameObjectManager::GameObjectList objectList = GameObjectManager::getInstance()->getAllObjects();

        Json::Value root;  // Root JSON object for the wrapper

        // Create an array to hold all objects
        Json::Value objectsJson(Json::arrayValue);

        for (AGameObject* gameObject : objectList)
        {
            Json::Value objectJson;

            // ObjectType and ObjectName
            objectJson["ObjectType"] = gameObject->getType();
            objectJson["ObjectName"] = gameObject->getName();

            // Position, rotation, and scale
            Vector3D position = gameObject->getLocalPosition();
            Vector3D rotation = gameObject->getLocalRotation();
            Vector3D scale = gameObject->getLocalScale();

            objectJson["Position"] = Json::Value(Json::arrayValue);
            objectJson["Position"].append(position.x);
            objectJson["Position"].append(position.y);
            objectJson["Position"].append(position.z);

            objectJson["Rotation"] = Json::Value(Json::arrayValue);
            objectJson["Rotation"].append(rotation.x);
            objectJson["Rotation"].append(rotation.y);
            objectJson["Rotation"].append(rotation.z);

            objectJson["Scale"] = Json::Value(Json::arrayValue);
            objectJson["Scale"].append(scale.x);
            objectJson["Scale"].append(scale.y);
            objectJson["Scale"].append(scale.z);

            // PhysicsComponent (if exists)
            Json::Value physicsJson;
            AGameObject::ComponentList physicsList = gameObject->getComponentsOfType(AComponent::ComponentType::Physics);

            // If a physics component exists, set it to "Yes", otherwise "No"
            if (!physicsList.empty())
            {
                PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(physicsList[0]);

                if (physicsComponent)
                {
                    physicsJson["Physics"] = "Yes";  // Indicate that this object has a physics component

                    physicsJson["Mass"] = physicsComponent->getMass();
                    physicsJson["Gravity"] = (physicsComponent->getUseGravity() ? "Yes" : "No");
                    physicsJson["BodyType"] = static_cast<int>(physicsComponent->getBodyType());
                    physicsJson["LinearDrag"] = physicsComponent->getLinearDrag();
                    physicsJson["AngularDrag"] = physicsComponent->getAngularDrag();

                    uint8_t constraints = physicsComponent->getConstraints();
                    Json::Value positionConstraints = Json::arrayValue;
                    if (constraints & static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezePositionX)) positionConstraints.append("X");
                    if (constraints & static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezePositionY)) positionConstraints.append("Y");
                    if (constraints & static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezePositionZ)) positionConstraints.append("Z");
                    physicsJson["PositionConstraints"] = positionConstraints;

                    Json::Value angularConstraints = Json::arrayValue;
                    if (constraints & static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezeRotationX)) angularConstraints.append("X");
                    if (constraints & static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezeRotationY)) angularConstraints.append("Y");
                    if (constraints & static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezeRotationZ)) angularConstraints.append("Z");
                    physicsJson["AngularConstraints"] = angularConstraints;
                }
            }
            else
            {
                physicsJson["Physics"] = "No";  // Indicate that this object does not have a physics component
            }

            objectJson["PhysicsComponent"] = physicsJson; // Add physics data (either Yes or No)

            // Add this object to the "Objects" array
            objectsJson.append(objectJson);
        }

        // Wrap the objects in a root object under the "Objects" key
        root["Objects"] = objectsJson;

        // Writing the JSON object to file
        sceneFile << root.toStyledString();

        sceneFile.close();
    }
}
