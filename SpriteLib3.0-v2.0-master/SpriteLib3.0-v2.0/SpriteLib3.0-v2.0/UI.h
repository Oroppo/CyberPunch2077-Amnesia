#ifndef __UI_H__
#define __UI_H__

#include <string>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>

class UI
{
public:
	static void InitImGUI(SDL_Window* window, void* context, const char* glslVer="#version 330 core");
	static void ShutDownImGui();
	static void Start(int windowWidth, int windowHeight);
	static void End();
	static bool m_isInit;
	static SDL_Window* m_window;
};

#endif // !__UI_H__
