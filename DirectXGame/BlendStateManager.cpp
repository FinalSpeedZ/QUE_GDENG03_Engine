#include "BlendStateManager.h"

BlendStateManager::BlendStateManager() {}

BlendStateManager::~BlendStateManager()
{
    releaseAll();
}

bool BlendStateManager::createBlendState(const std::string& stateName, const D3D11_BLEND_DESC& blendDesc)
{
    if (m_blendStates.find(stateName) != m_blendStates.end())
        return false;

    BlendState* blendState = new BlendState();
    if (!blendState->init(blendDesc))
    {
        delete blendState;
        return false;
    }


    m_blendStates[stateName] = blendState;
    return true;
}

void BlendStateManager::applyBlendState(const std::string& stateName, float blendFactor[4], UINT sampleMask)
{
    auto it = m_blendStates.find(stateName);
    if (it != m_blendStates.end())
    {
        it->second->apply(blendFactor, sampleMask);
    }
}

void BlendStateManager::releaseBlendState(const std::string& stateName)
{
    auto it = m_blendStates.find(stateName);
    if (it != m_blendStates.end())
    {
        it->second->release();
        m_blendStates.erase(it);
    }
}

void BlendStateManager::releaseAll()
{
    for (auto& pair : m_blendStates)
    {
        pair.second->release();
    }
    m_blendStates.clear();
}

void BlendStateManager::initBlendStates()
{
    D3D11_BLEND_DESC blendDesc = {};

    // Alpha Blend State
    blendDesc = {};
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.IndependentBlendEnable = true; 
    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    createBlendState("AlphaBlend", blendDesc);

    // Custom Blend State 1
    blendDesc = {};
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.IndependentBlendEnable = true; 
    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; 
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_COLOR; 
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD; 
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD; 
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    createBlendState("CustomBlend1", blendDesc);

    // Custom Blend State 2
    blendDesc = {};
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.IndependentBlendEnable = true;
    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    createBlendState("CustomBlend2", blendDesc);

    // Custom Blend State 3
    blendDesc = {};
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.IndependentBlendEnable = true;
    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_COLOR;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    createBlendState("CustomBlend3", blendDesc);

    // Custom Blend 4
    blendDesc = {};
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.IndependentBlendEnable = true;
    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    createBlendState("CustomBlend4", blendDesc);
}

BlendState* BlendStateManager::getBlendState(const std::string& stateName) const {

	auto bs = m_blendStates.find(stateName);

    if (bs != m_blendStates.end()) {
        return bs->second;
    }
    return nullptr; 
}
