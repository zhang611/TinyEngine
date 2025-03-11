#include "application.h"
#include <memory>
#include "component/game_object.h"
#include "renderer/camera.h"
#include "renderer/mesh_renderer.h"
#include "control/input.h"
#include "screen.h"

std::string Application::data_path_;
GLFWwindow *Application::glfw_window_;

static void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

// 键盘回调
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Input::RecordKey(key, action);
}

// 鼠标按键回调
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    Input::RecordKey(button, action);
//    std::cout<<"mouse_button_callback:"<<button<<","<<action<<std::endl;
}

// 鼠标移动回调
static void mouse_move_callback(GLFWwindow *window, double x, double y) {
    Input::set_mousePosition(x, y);
//    std::cout<<"mouse_move_callback:"<<x<<","<<y<<std::endl;
}

// 鼠标滚轮回调
static void mouse_scroll_callback(GLFWwindow *window, double x, double y) {
    Input::RecordScroll(y);
//    std::cout<<"mouse_scroll_callback:"<<x<<","<<y<<std::endl;
}

void Application::InitOpengl() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfw_window_ = glfwCreateWindow(960, 640, "Tiny Engine", NULL, NULL);
    if (!glfw_window_) {
        glfwTerminate();  // 释放资源，清理内存
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(glfw_window_);  // 这个窗口的 OpenGL 上下文成为当前线程的上下文
    gladLoadGL(glfwGetProcAddress);

    UpdateScreenSize();
    glfwSwapInterval(1);  // 开启垂直同步，防止撕裂

    glfwSetKeyCallback(glfw_window_, key_callback);
    glfwSetMouseButtonCallback(glfw_window_, mouse_button_callback);
    glfwSetScrollCallback(glfw_window_, mouse_scroll_callback);
    glfwSetCursorPosCallback(glfw_window_, mouse_move_callback);
}


void Application::Update() {
    UpdateScreenSize();

    // 遍历所有游戏对象的所有组件，更新
    GameObject::Foreach([](GameObject *game_object) {
        game_object->ForeachComponent([](Component *component) {
            component->Update();
        });
    });

    Input::Update();

//    std::cout<<"Application::Update"<<std::endl;
}


void Application::Render() {
    //遍历所有相机，每个相机的View Projection，都用来做一次渲染。
    Camera::Foreach([&]() {
        GameObject::Foreach([](GameObject *game_object) {
            auto component = game_object->GetComponent("MeshRenderer");
            if (!component) {
                return;
            }
            auto mesh_renderer = dynamic_cast<MeshRenderer *>(component);
            if (!mesh_renderer) {
                return;
            }
            mesh_renderer->Render();
        });
    });
}

void Application::Run() {
    while (!glfwWindowShouldClose(glfw_window_)) {
        Update();
        Render();

        glfwSwapBuffers(glfw_window_);

        glfwPollEvents();
    }

    glfwDestroyWindow(glfw_window_);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Application::UpdateScreenSize() {
    int width, height;
    glfwGetFramebufferSize(glfw_window_, &width, &height);
    glViewport(0, 0, width, height);
    Screen::set_width_height(width, height);
}
