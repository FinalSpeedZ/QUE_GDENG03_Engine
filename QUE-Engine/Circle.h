#pragma once

#include "GameObject.h"

#include "Drawable.h"

class Circle : public Drawable
{
public:
    Circle(std::string name, float radius = 0.1f);
    ~Circle() {}

public:
    void onCreate() override;
    void onUpdate(float deltaTime) override;
    void onDestroy() override;

protected:
    void draw() override;

public:
    void setRadius(float radius);

private:
    void calculateVertices() override;
    void updateConstantBuffer(float deltaTime) override;
    void projectionMat() override;

    float getRandomFloat(float min, float max);
    void randomColor();

private:
    vec4 color; 

    float radius;
    int numSegments = 100;

    float velocityX;
    float velocityY;

};
