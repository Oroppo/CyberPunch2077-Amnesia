#include "Scene.h"
#include "String"

class VictoryScreen : public Scene
{
public:

    VictoryScreen(std::string name);

    void InitScene(float windowWidth, float windowHeight) override;

    void Update() override;

    int GetSceneChange() override;

    void SetSceneChange(int) override;

    void CreateCameraEntity(bool mainCamera, float windowWidth, float windowHeight, float left, float right, float bottom, float top,
        float zNear, float zFar, float aspectRatio, bool vertScroll = false, bool horizScroll = false);

private:
    bool m_firstWindow = false;
    bool m_secondWindow = false;
    bool m_SceneChange = false;


    std::string m_fileInput;
};