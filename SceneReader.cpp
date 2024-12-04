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
            fileDirectory = m_directory; 
        }

        std::ifstream sceneFile(fileDirectory);
        if (!sceneFile.is_open())
        {
            Logger::log("Failed to open file for reading: " + fileDirectory);
            return;
        }

        Logger::log("Reading scene from file: " + fileDirectory);

        GameObjectManager::getInstance()->deleteAllObjects();

        std::string line;
        std::string objectName, objectType;
        Vector3D position, rotation, scale;
        bool hasPhysics = false;
        float mass = 0.0f, linearDrag = 0.0f, angularDrag = 0.0f;
        bool gravity = false;
        int bodyType = 0;
        uint8_t constraints = 0;
        std::vector<std::string> positionConstraints, angularConstraints;

        while (std::getline(sceneFile, line))
        {
            if (line.empty()) continue;

            // Parse each line
            if (line.find("Object Name:") != std::string::npos)
            {
                objectName = line.substr(line.find(":") + 2);
            }
            else if (line.find("Object Type:") != std::string::npos)
            {
                objectType = line.substr(line.find(":") + 2);
            }
            else if (line.find("Position:") != std::string::npos)
            {
                sscanf(line.c_str(), "Position: (%f, %f, %f)", &position.x, &position.y, &position.z);
            }
            else if (line.find("Rotation:") != std::string::npos)
            {
                sscanf(line.c_str(), "Rotation: (%f, %f, %f)", &rotation.x, &rotation.y, &rotation.z);
            }
            else if (line.find("Scale:") != std::string::npos)
            {
                sscanf(line.c_str(), "Scale: (%f, %f, %f)", &scale.x, &scale.y, &scale.z);
            }
            else if (line.find("Physics:") != std::string::npos)
            {
                hasPhysics = (line.substr(line.find(":") + 2) == "Yes");
            }
            else if (line.find("Mass:") != std::string::npos)
            {
                mass = std::stof(line.substr(line.find(":") + 2));
            }
            else if (line.find("Gravity:") != std::string::npos)
            {
                gravity = (line.substr(line.find(":") + 2) == "Yes");
            }
            else if (line.find("BodyType:") != std::string::npos)
            {
                bodyType = std::stoi(line.substr(line.find(":") + 2));
            }
            else if (line.find("LinearDrag:") != std::string::npos)
            {
                linearDrag = std::stof(line.substr(line.find(":") + 2));
            }
            else if (line.find("AngularDrag:") != std::string::npos)
            {
                angularDrag = std::stof(line.substr(line.find(":") + 2));
            }
            else if (line.find("Position Constraints:") != std::string::npos)
            {
                positionConstraints.clear();
                std::istringstream stream(line.substr(line.find(":") + 2));
                std::string constraint;
                while (stream >> constraint)
                {
                    if (constraint == "X")
                        constraints |= static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezePositionX);
                    else if (constraint == "Y")
                        constraints |= static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezePositionY);
                    else if (constraint == "Z")
                        constraints |= static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezePositionZ);
                }
            }
            else if (line.find("Angular Constraints:") != std::string::npos)
            {
                angularConstraints.clear();
                std::istringstream stream(line.substr(line.find(":") + 2));
                std::string constraint;
                while (stream >> constraint)
                {
                    if (constraint == "X")
                        constraints |= static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezeRotationX);
                    else if (constraint == "Y")
                        constraints |= static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezeRotationY);
                    else if (constraint == "Z")
                        constraints |= static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezeRotationZ);
                }
            }
            else if (line == "---")
            {
                // Create the object and assign components
                AGameObject* currentObject = GameObjectManager::getInstance()->createObjectFromFile(
                    objectName, objectType, position, rotation, scale);

                if (hasPhysics)
                {
                    BaseComponentSystem::getInstance()->getPhysicsSystem()->createComponentFromFile(
                        "PhysicsComponent", currentObject, AComponent::ComponentType::Physics,
                        mass, gravity, static_cast<BodyType>(bodyType), linearDrag, angularDrag, constraints);
                }

                // Reset variables for the next object
                objectName = objectType = "";
                position = rotation = scale = Vector3D();
                hasPhysics = false;
                mass = linearDrag = angularDrag = 0.0f;
                gravity = false;
                bodyType = 0;
                constraints = 0;
            }
        }

        sceneFile.close();
    }

}
