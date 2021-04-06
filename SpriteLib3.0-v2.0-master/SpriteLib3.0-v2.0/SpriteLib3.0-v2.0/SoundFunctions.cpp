#include "SoundFunctions.h"

void SoundFunctions::LoadSound(std::string fileName) {

	std::string SoundString = "open assets/Sounds/" + fileName + " type mpegvideo alias " + fileName;
	mciSendString(SoundString.c_str(), NULL, 0, NULL);

}

void SoundFunctions::Play(std::string fileName) {

	std::string SoundString = "play " + fileName ;
	mciSendString(SoundString.c_str(), NULL, 0, NULL);

}

void SoundFunctions::LoopSound(std::string fileName) {

	std::string SoundString = "play " + fileName + " repeat";
	mciSendString(SoundString.c_str(), NULL, 0, NULL);

}

void SoundFunctions::PauseSound(std::string fileName) {

	std::string SoundString = "pause " + fileName;
	mciSendString(SoundString.c_str(), NULL, 0, NULL);

}

void SoundFunctions::StopSound(std::string fileName) {

	std::string SoundString = "close " + fileName;
	mciSendString(SoundString.c_str(), NULL, 0, NULL);

}
