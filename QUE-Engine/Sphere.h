#pragma once

#include "GameObject.h"

#include "Drawable.h"

class Sphere : public Drawable
{
public:
    Sphere(std::string name = "Sphere", float radius = 1.0f);
    ~Sphere() {}

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
    IndexBuffer* m_ib;
    std::vector<unsigned int> index_list;

    float radius;
    int numSegments = 60;
};
