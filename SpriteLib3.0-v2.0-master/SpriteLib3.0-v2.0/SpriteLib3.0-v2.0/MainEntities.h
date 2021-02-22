#ifndef __MAINENTITIES_H__
#define __MAINENTITIES_H__

class MainEntities
{
public:
	//Getters
	static int MainCamera();
	static int MainPlayer();

	//Setters
	static void MainCamera(int main);
	static void MainPlayer(int main);

private:
	static int m_mainCamera;
	static int m_mainPlayer;
};

#endif // !__MAINENTITIES_H__
