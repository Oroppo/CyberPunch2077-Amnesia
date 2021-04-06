#pragma once

#include "Scene.h"
#include <string>

class StartMenu : public Scene
{
public:

	StartMenu(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	void MenuUpdate();

	int GetSceneChange() override;

	void SetSceneChange(int) override;

	void CreateCameraEntity(bool mainCamera, float windowWidth, float windowHeight, float left, float right, float bottom, float top,
		float zNear, float zFar, float aspectRatio, bool vertScroll = false, bool horizScroll = false);

private:
	bool m_firstWindow = false;
	bool m_secondWindow = false;
	bool m_SceneChange = false;

	int m_arrow;
	int m_selection = 0;
	int m_infographic;
	int m_enterID;
	bool m_locked=false;

	std::string m_fileInput;
};

