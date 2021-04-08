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


	int GetSceneChange() override;
	void SetSceneChange(int) override;


	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;
	void MouseClick(SDL_MouseButtonEvent evnt) override;

	static float Bsheild;
	static float laserPointerG;
	static float laserBeamG;
	static float laserPointerT;
	static float laserBeamT;
	
protected:
	bool m_firstWindow = false;
	bool m_secondWindow = false;

	std::string m_fileInput;

	PhysicsPlaygroundListener listener;
	// Part of enemy code
	unsigned enemyEntity;
	std::vector <unsigned int> EnemyEnts = {};
	void SpawnBasicRobot(float32, float32, float);
	void SpawnVent(float, float , float);
	void EXPUROSION();
	unsigned BossEntity;
	std::vector <unsigned int> BossEnts = {};

	int enemy;
	int enemy2;
	int puzzleWall1;
	int puzzleWall2;
	int MainPlayer;
	
	int hud5;
	int hud4;
	int hud3;
	int hud2;
	int hud1;
	int hud0;
};
