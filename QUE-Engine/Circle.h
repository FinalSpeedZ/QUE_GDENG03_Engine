#pragma once

#include "GameObject.h"

#include "Drawable.h"

class Circle : public Drawable
{
public:
    Circle(std::string name, float radius = 0.25f);
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

private:
    std::vector<vec4> colors; 

    float radius;
    int numSegments = 360; 
};
