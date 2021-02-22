#pragma once

#include "Scene.h"

class FirstCreation : public Scene
{
public:
	FirstCreation(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	void AdjustScrollOffset();

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

protected:
	
};
