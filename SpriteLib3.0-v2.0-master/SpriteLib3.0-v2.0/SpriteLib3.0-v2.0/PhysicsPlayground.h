#pragma once

#include "Scene.h"
#include "PhysicsPlaygroundListener.h"
#include <string>

class PhysicsPlayground : public Scene
{
public:
	PhysicsPlayground(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	void GUI() override;

	void GUIWindowUI();
	void GUIWindowOne();
	void GUIWindowTwo();


	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;
	void MouseClick(SDL_MouseButtonEvent evnt) override;
protected:
	bool m_firstWindow = false;
	bool m_secondWindow = false;

	std::string m_fileInput;

	PhysicsPlaygroundListener listener;
	// Part of enemy code
	unsigned enemyEntity;
	std::vector <unsigned int> EnemyEnts = {};

	int enemy;
	int puzzleWall1;
	int puzzleWall2;
};