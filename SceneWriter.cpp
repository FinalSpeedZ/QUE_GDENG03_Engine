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
            fileDirectory = m_directory; 
        }

        std::ofstream sceneFile(fileDirectory);
        if (!sceneFile.is_open())
        {
            Logger::log("Failed to open file for writing: " + fileDirectory);
            return;
        }

        Logger::log("Writing scene to file: " + fileDirectory);

        GameObjectManager::GameObjectList objectList = GameObjectManager::getInstance()->getAllObjects();

        for (AGameObject* gameObject : objectList)
        {
            sceneFile << "Object Name: " << gameObject->getName() << "\n";
            sceneFile << "Object Type: " << gameObject->getType() << "\n";

            // Position
            Vector3D position = gameObject->getLocalPosition();
            sceneFile << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";

            // Rotation
            Vector3D rotation = gameObject->getLocalRotation();
            sceneFile << "Rotation: (" << rotation.x << ", " << rotation.y << ", " << rotation.z << ")\n";

            // Scale
            Vector3D scale = gameObject->getLocalScale();
            sceneFile << "Scale: (" << scale.x << ", " << scale.y << ", " << scale.z << ")\n";

            // PhysicsComponent (if exists)
            AGameObject::ComponentList physicsList = gameObject->getComponentsOfType(AComponent::ComponentType::Physics);
            if (!physicsList.empty())
            {
                PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(physicsList[0]);
                if (physicsComponent)
                {
                    sceneFile << "Physics: Yes\n";
                    sceneFile << "Mass: " << physicsComponent->getMass() << "\n";
                    sceneFile << "Gravity: " << (physicsComponent->getUseGravity() ? "Yes" : "No") << "\n";
                    sceneFile << "BodyType: " << static_cast<int>(physicsComponent->getBodyType()) << "\n";
                    sceneFile << "LinearDrag: " << physicsComponent->getLinearDrag() << "\n";
                    sceneFile << "AngularDrag: " << physicsComponent->getAngularDrag() << "\n";

                    uint8_t constraints = physicsComponent->getConstraints();
                    sceneFile << "Position Constraints: ";
                    if (constraints & static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezePositionX)) sceneFile << "X ";
                    if (constraints & static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezePositionY)) sceneFile << "Y ";
                    if (constraints & static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezePositionZ)) sceneFile << "Z ";
                    sceneFile << "\n";

                    sceneFile << "Angular Constraints: ";
                    if (constraints & static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezeRotationX)) sceneFile << "X ";
                    if (constraints & static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezeRotationY)) sceneFile << "Y ";
                    if (constraints & static_cast<uint8_t>(PhysicsComponent::EConstraints::FreezeRotationZ)) sceneFile << "Z ";
                    sceneFile << "\n";
                }
            }
            else
            {
                sceneFile << "Physics: No\n";
            }

            sceneFile << "---\n"; // Separator for objects
        }

        sceneFile.close();
    }
}
