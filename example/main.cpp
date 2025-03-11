#define GLFW_INCLUDE_NONE

#include "component/game_object.h"
#include "utils/application.h"

int main(void) {
    Application::set_data_path("../data/");
    Application::InitOpengl();    // 初始化引擎

    GameObject *go = new GameObject("LoginSceneGox");
    go->AddComponent("Transform");
    go->AddComponent("LoginScene");

    Application::Run(); //开始引擎主循环
}