#pragma once
#include <Windows.h>
#include <string>

#pragma comment (lib, "winmm.lib")
//included in windows.h

class SoundFunctions
{
public:
	static void LoadSound(std::string fileName);
	static void Play(std::string fileName);
	static void LoopSound(std::string fileName);
	static void PauseSound(std::string fileName);
	static void StopSound(std::string fileName);

};

