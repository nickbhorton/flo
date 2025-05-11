#include <array>
#include <iostream>
#include <stdexcept>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

// globals
int window_width = 640;
int window_height = 480;

void background_color_tool(std::array<float, 3>& bg_color)
{
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;

    if (!ImGui::Begin("Window", nullptr, window_flags)) {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }
    static bool init = false;
    if (!init) {
        ImGui::SetWindowPos(ImVec2(0, 0));
        ImGui::SetWindowSize(ImVec2(200, 1080));
        init = true;
    }
    ImGui::Text("background color");
    ImGui::ColorEdit3("", (float*)&bg_color); // Edit 3 floats representing a color
    ImGui::End();
}

void glfw_error_callback(int error, const char* desc)
{
    std::cerr << "glfw_error_callback " << error << " " << desc << std::endl;
}

void glfw_window_resize_callback([[maybe_unused]] GLFWwindow* window, int new_width, int new_height)
{
    std::cout << "window resized: " << new_width << " " << new_height << "\n";
    window_width = new_width;
    window_height = new_height;
    glViewport(0, 0, new_width, new_height);
}

class Glfw
{
public:
    Glfw()
    {
        if (!glfwInit()) {
            throw std::runtime_error("failed to initialize glfw");
        }
        glfwSetErrorCallback(glfw_error_callback);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(window_width, window_height, "flo", NULL, NULL);
        if (!window) {
            throw std::runtime_error("failed to initialize glfw window");
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, glfw_window_resize_callback);

        // turn on vsync
        glfwSwapInterval(1);
    }
    ~Glfw() { glfwTerminate(); };

public:
    GLFWwindow* window;
    const char* glsl_version = "#version 150";
};

class ImguiContext
{
public:
    ImguiContext(Glfw& glfw)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = NULL;

        ImGui_ImplGlfw_InitForOpenGL(glfw.window, true);
        ImGui_ImplOpenGL3_Init(glfw.glsl_version);
    }
    ~ImguiContext()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    void new_frame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
    void render()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
};

int main(void)
{
    // background color
    std::array<float, 3> bg_color{0.4f, 0.3f, 0.4f};

    Glfw glfw{};
    ImguiContext gui_context{glfw};

    while (!glfwWindowShouldClose(glfw.window)) {
        glfwPollEvents();
        glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        gui_context.new_frame();
        background_color_tool(bg_color);
        gui_context.render();

        glfwSwapBuffers(glfw.window);
    }
    return 0;
}
