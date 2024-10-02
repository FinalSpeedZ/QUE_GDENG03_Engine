#pragma once

#include "GraphicsEngine.h"

#include "DeviceContext.h"

#include "VertexBuffer.h"

#include "Vertex.h"

class Drawable
{
protected:
    VertexBuffer* m_vb;

    vec3 m_position;   
    vec3 m_scale;      
    vec3 m_origin;

    vec4 m_rgba;

    std::vector<vertex> m_vertices;

    BlendState* m_blendState;

public:
    Drawable();
    virtual ~Drawable();

    void setPosition(const vec3& position);
    void setScale(const vec3& scale);
    void setOrigin(const vec3& origin);

    void setBlendState(BlendState* blendState);
    BlendState* getBlendState();

    virtual void load(void* shader_byte_code, UINT size_byte_shader);

    virtual void draw();
};