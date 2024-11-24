#include "InspectorScreen.h"

#include "GameObjectManager.h"

#include "Libs/imgui/imgui_stdlib.h"

#include "UIManager.h"

InspectorScreen::InspectorScreen()
	: UIScreen("Inspector Screen")
{
}

void InspectorScreen::drawUI()
{
	ImGui::Begin("Inspector", &enabled);

	this->gameObject = GameObjectManager::getInstance()->getSelectedObject();

	if (this->gameObject)
	{
		std::string name = gameObject->getName();
		bool isActive = gameObject->isActive();

		if (ImGui::Checkbox("##Active", &isActive))
		{
			gameObject->setActive(isActive);
		}

		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);

		if (ImGui::InputText("##Name", &name))
		{
			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				gameObject->setName(name);
			}
		}

		this->drawTransform();

		if (ImGui::Button("Delete"))
		{
			GameObjectManager::getInstance()->setSelectedObject(nullptr);
			GameObjectManager::getInstance()->deleteGameObject(gameObject);
		}

	}

	ImGui::End();
}

void InspectorScreen::drawTransform()
{
	std::string labels[3] = { "Position", "Rotation", "Scale" };

	Vector3D transform[3];

	Vector3D pos = Vector3D(gameObject->getLocalMatrix().mat[3][0],
		gameObject->getLocalMatrix().mat[3][1],
		gameObject->getLocalMatrix().mat[3][2]);


	transform[0] = pos;
	transform[1] = gameObject->getLocalRotation();
	transform[2] = gameObject->getLocalScale();

	for (int i = 0; i < 3; ++i)
	{
		ImGui::Text(labels[i].c_str());
		ImGui::SameLine();

		float values[] = { transform[i].x, transform[i].y, transform[i].z };

		std::string label = "##" + labels[i];

		if (ImGui::DragFloat3(label.c_str(), values, 0.01f))  
		{
			switch (i)
			{
			case 0: // Position
				gameObject->setPosition(Vector3D(values[0], values[1], values[2]));
				break;
			case 1: // Rotation
				gameObject->setRotation(Vector3D(values[0], values[1], values[2]));
				break;
			case 2: // Scale
				gameObject->setScale(Vector3D(values[0], values[1], values[2]));
				break;
			}
		}
	}
}
