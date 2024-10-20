#include "Sphere.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <corecrt_math_defines.h>

Sphere::Sphere(std::string name, float radius)
    : Drawable(name), radius(radius)
{
}

void Sphere::onCreate()
{
    calculateVertices();

    m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
    UINT size_list = vertices.size();

    m_ib = GraphicsEngine::getInstance()->createIndexBuffer();
    UINT size_index_list = index_list.size();

    m_ib->load(index_list, size_index_list);

    void* shader_byte_code = nullptr;
    size_t size_shader = 0;
    GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

    m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
    m_vb->load(vertices, sizeof(vertex), size_list, shader_byte_code, size_shader);

    GraphicsEngine::getInstance()->releaseCompiledShader();

    GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
    m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
    GraphicsEngine::getInstance()->releaseCompiledShader();

    constant cc;
    cc.m_time = 0;

    m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
    m_cb->load(&cc, sizeof(constant));
}

void Sphere::onUpdate(float deltaTime)
{
    Drawable::onUpdate(deltaTime);
}

void Sphere::onDestroy()
{
    Drawable::onDestroy();
}

void Sphere::draw()
{
    Drawable::draw();

    GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

    GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Sphere::setRadius(float radius)
{
    this->radius = radius;
    calculateVertices(); 
    onCreate();
}

void Sphere::calculateVertices()
{
    vertices.clear();
    index_list.clear(); 

    float phiIncrement = M_PI / numSegments;
    float thetaIncrement = 2.0f * M_PI / numSegments;

    for (int i = 0; i <= numSegments; ++i) {
        float phi = i * phiIncrement;

        for (int j = 0; j <= numSegments; ++j) {
            float theta = j * thetaIncrement;

            float x = radius * sin(phi) * cos(theta);
            float y = radius * cos(phi);
            float z = radius * sin(phi) * sin(theta);

            vertices.push_back({ Vector3D(x, y, z), Colors::WHITE, Colors::RED });
        }
    }

    // Generate indices for a triangle list
    for (int i = 0; i < numSegments; ++i) {
        for (int j = 0; j < numSegments; ++j) {
            int first = i * (numSegments + 1) + j;
            int second = first + numSegments + 1;

            // First triangle of the quad
            index_list.push_back(first);
            index_list.push_back(second);
            index_list.push_back(first + 1);

            // Second triangle of the quad
            index_list.push_back(second);
            index_list.push_back(second + 1);
            index_list.push_back(first + 1);
        }
    }

}

void Sphere::updateConstantBuffer(float deltaTime)
{
    Drawable::updateConstantBuffer(deltaTime);
}

void Sphere::projectionMat()
{
    Drawable::projectionMat();
}
