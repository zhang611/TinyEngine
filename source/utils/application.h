#ifndef UNTITLED_APPLICATION_H
#define UNTITLED_APPLICATION_H

#include <string>
#include "glad/gl.h"
#include "GLFW/glfw3.h"

class Application {
public:
    static const std::string &data_path() { return data_path_; }

    static void set_data_path(std::string data_path) { data_path_ = data_path; }

    static void InitOpengl();   // 初始化 OpenGL
    static void Run();

    static void UpdateScreenSize();

    static void Update();

    static void Render();

private:
    static std::string data_path_;      // data目录
    static GLFWwindow *glfw_window_;

};


#endif //UNTITLED_APPLICATION_H
