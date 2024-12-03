#include "SceneReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <json/json.h> // Add this for JSON parsing
#include "BaseComponentSystem.h"
#include "GameObjectManager.h"
#include "PhysicsComponent.h"
#include "TextureComponent.h"
#include "MeshRenderer.h"
#include "PhysicsSystem.h"  // Include this for using PhysicsSystem

namespace GDEngine
{
    SceneReader::SceneReader(std::string directory)
    {
        m_directory = directory;
    }

    SceneReader::~SceneReader()
    {
    }

    void SceneReader::readFromFile()
    {
        std::string fileDirectory = m_directory + ".level";
        if (m_directory.find(".level") != std::string::npos)
        {
            fileDirectory = m_directory; // Use directory as file name if it contains .level
        }

        std::ifstream sceneFile(fileDirectory);
        if (!sceneFile.is_open())
        {
            Logger::log("Failed to open file for reading: " + fileDirectory);
            return;
        }

        Logger::log("Reading scene from file: " + fileDirectory);

        GameObjectManager::getInstance()->deleteAllObjects();

        Json::Value root;
        sceneFile >> root; // Parse the whole file into the root Json object

        // Ensure that we are accessing the "Objects" array (from the previous exporter)
        const Json::Value& objectsJson = root["Objects"];
        
        if (objectsJson.isArray())
        {
            // Iterate through each object in the "Objects" array
            for (const auto& objectJson : objectsJson)
            {
                std::string classType = objectJson["ObjectType"].asString();
                std::string name = objectJson["ObjectName"].asString();

                // Read Position, Rotation, Scale as arrays
                const Json::Value& positionJson = objectJson["Position"];
                Vector3D position(positionJson[0].asFloat(), positionJson[1].asFloat(), positionJson[2].asFloat());

                const Json::Value& rotationJson = objectJson["Rotation"];
                Vector3D rotation(rotationJson[0].asFloat(), rotationJson[1].asFloat(), rotationJson[2].asFloat());

                const Json::Value& scaleJson = objectJson["Scale"];
                Vector3D scale(scaleJson[0].asFloat(), scaleJson[1].asFloat(), scaleJson[2].asFloat());

                // Create the game object using the extracted data
                AGameObject* currentObject = GameObjectManager::getInstance()->createObjectFromFile(name, classType, position, rotation, scale);

                // Read PhysicsComponent if it exists
                const Json::Value& physicsJson = objectJson["PhysicsComponent"];
                if (!physicsJson.isNull() && physicsJson["Physics"].asString() == "Yes")
                {
                    // Extract physics properties from JSON
                    float mass = physicsJson["Mass"].asFloat();
                    bool gravity = (physicsJson["Gravity"].asString() == "Yes");
                    BodyType bodyType = static_cast<BodyType>(physicsJson["BodyType"].asInt());
                    float linearDrag = physicsJson["LinearDrag"].asFloat();
                    float angularDrag = physicsJson["AngularDrag"].asFloat();
                    uint8_t constraints = 0;

                    const Json::Value& positionConstraintsJson = physicsJson["PositionConstraints"];
                    if (!positionConstraintsJson.isNull())
                    {
                        for (const auto& constraint : positionConstraintsJson)
                        {
                            std::string constraintStr = constraint.asString();
                            if (constraintStr == "X")
                            {
                                constraints |= static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezePositionX);
                            }
                            else if (constraintStr == "Y")
                            {
                                constraints |= static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezePositionY);
                            }
                            else if (constraintStr == "Z")
                            {
                                constraints |= static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezePositionZ);
                            }
                        }
                    }

                    const Json::Value& angularConstraintsJson = physicsJson["AngularConstraints"];
                    if (!angularConstraintsJson.isNull())
                    {
                        for (const auto& constraint : angularConstraintsJson)
                        {
                            std::string constraintStr = constraint.asString();
                            if (constraintStr == "X")
                            {
                                constraints |= static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezeRotationX);
                            }
                            else if (constraintStr == "Y")
                            {
                                constraints |= static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezeRotationY);
                            }
                            else if (constraintStr == "Z")
                            {
                                constraints |= static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezeRotationZ);
                            }
                        }
                    }

                    // Use PhysicsSystem to create and attach the PhysicsComponent
                    BaseComponentSystem::getInstance()->getPhysicsSystem()->createComponentFromFile(
                        "PhysicsComponent",
                        currentObject,
                        AComponent::ComponentType::Physics,
                        mass,
                        gravity,
                        bodyType,
                        linearDrag,
                        angularDrag,
                        constraints
                    );
                }
            }
        }

        sceneFile.close();
    }
}
