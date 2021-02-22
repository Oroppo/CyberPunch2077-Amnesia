#include "UI.h"
#include "Window.h"


bool UI::m_isInit = false;
SDL_Window* UI::m_window = nullptr;

void UI::InitImGUI(SDL_Window* window, void* context, const char* glslVer)
{
	ImGui::CreateContext();

	m_window = window;

	//Set up input output configs
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	//DARK MODE POG
	ImGui::StyleColorsDark();

	//Setup styles
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		style.FrameBorderSize = 0.f;
		style.FramePadding = ImVec2(0.f, 0.f);
	}

	//Init imgui for OpenGL3 and SDL
	ImGui_ImplSDL2_InitForOpenGL(m_window, context);
	ImGui_ImplOpenGL3_Init(glslVer);

	m_isInit = true;
}

void UI::ShutDownImGui()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void UI::Start(int windowWidth, int windowHeight)
{
	if (m_isInit)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize.x = static_cast<float>(windowWidth);
		io.DisplaySize.y = static_cast<float>(windowHeight);
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(m_window);
		ImGui::NewFrame();
	}
	else
	{
		printf("Imgui is not currently initialized");
	}
}

void UI::End()
{
	if (m_isInit)
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
			SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
		}

	}
	else
	{
		printf("Imgui is not currently intialized");
	}
}
