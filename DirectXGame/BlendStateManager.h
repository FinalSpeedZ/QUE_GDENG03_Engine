#pragma once

#include <unordered_map>
#include <string>
#include "BlendState.h"

class BlendStateManager
{
public:
    BlendStateManager();
    ~BlendStateManager();

    bool createBlendState(const std::string& stateName, const D3D11_BLEND_DESC& blendDesc);
    void applyBlendState(const std::string& stateName, float blendFactor[4] = nullptr, UINT sampleMask = 0xFFFFFFFF);
    void releaseBlendState(const std::string& stateName);
    void releaseAll();

    void initBlendStates();

    BlendState* getBlendState(const std::string& stateName) const;

private:
    std::unordered_map<std::string, BlendState*> m_blendStates;
};

