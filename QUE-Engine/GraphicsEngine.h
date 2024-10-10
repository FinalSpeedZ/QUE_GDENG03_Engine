#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>

#include "SwapChain.h"
#include "DeviceContext.h"

class SwapChain;
class DeviceContext;

class GraphicsEngine
{

private:
	GraphicsEngine() {};
	~GraphicsEngine() {};
	GraphicsEngine(GraphicsEngine const&) {};
	GraphicsEngine& operator = (GraphicsEngine const&) {};

	static GraphicsEngine* sharedInstance;

public:
	static GraphicsEngine* getInstance();

public:
	static void initialize();
	static void destroy();

	bool init();
	bool release();

public:
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();

private:
	DeviceContext* m_imm_device_context;

	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D11DeviceContext* m_imm_context;

private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

private:
	friend class SwapChain;
};

