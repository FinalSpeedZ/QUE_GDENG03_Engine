#include "UIScreen.h"

UIScreen::UIScreen(std::string name)
{
	this-> name = name;
	this->enabled = true;
}

UIScreen::~UIScreen()
{
}

std::string UIScreen::getName()
{
	return this->name;
}

void UIScreen::setEnabled(bool enabled)
{
	this->enabled = enabled;
}
