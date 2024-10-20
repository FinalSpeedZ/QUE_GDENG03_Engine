#pragma once

#include "Vector2D.h"

class InputListener
{
public:
	InputListener() {};
	~InputListener() {};

	//KEYBOARD pure virtual callback functions 
	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;

	//MOUSE pure virtual callback fucntions
	virtual void onMouseMove(const Vector2D& deltaMousePos) = 0;

	virtual void onLeftMouseDown(const Vector2D& mousePos) = 0;
	virtual void onLeftMouseUp(const Vector2D& mousePos) = 0;

	virtual void onRightMouseDown(const Vector2D& mousePos) = 0;
	virtual void onRightMouseUp(const Vector2D& mousePos) = 0;
};