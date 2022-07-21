#pragma once
#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <memory>
#include <tuple>
#include <vector>

#include "IRenderable.hpp"

class ImGuiWrapper
{
public:
	
	static void StartImGui();
	static void AddWindow(std::unique_ptr<IRenderable> window);
	
private:
	static std::tuple<WNDCLASSEX, HWND> ImGuiStartup();
	static void ImGuiShutdown(WNDCLASSEX wc, HWND hwnd);
	static bool CreateDeviceD3D(HWND hWnd);
	static void CleanupDeviceD3D();
	static void CreateRenderTarget();
	static void CleanupRenderTarget();

	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static ID3D11Device* s_pd3dDevice;
	static ID3D11DeviceContext* s_pd3dDeviceContext;
	static IDXGISwapChain* s_pSwapChain;
	static ID3D11RenderTargetView* s_mainRenderTargetView;

	static std::vector<std::unique_ptr<IRenderable>> s_Windows;
};

