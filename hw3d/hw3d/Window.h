#pragma once
#include "WinSetup.h"
#include "LewisException.h"
#include "Graphics.h"
#include <optional>
#include <memory>


class Window
{
public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetWindowTitle(const std::string& title);
	//static std::optional<int> ProcessMessages();
	static void ProcessMessages();
	Graphics* GetGraphics();
private:
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "Lewis Direct3D Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};

	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	int width;
	int height;
	HWND hWindow;
	std::unique_ptr<Graphics> pGraphics;
};
