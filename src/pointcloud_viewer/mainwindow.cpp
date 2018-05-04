#include <pointcloud_viewer/mainwindow.hpp>
#include <core_library/exception.hpp>

#include <GLFW/glfw3.h>

namespace pointcloud_viewer {
namespace mainwindow {

extern GLFWwindow* glfw_window;

void throw_glfw_error(int error, const char* description);

// Constructor initializes glfw and an opengl 4.5 window
Instance::Instance()
{
  // Initialize glfw
  if(glfwInit() != GLFW_TRUE)
    throw exception_t{"Couldn't initialize glfw"};
  glfwSetErrorCallback(throw_glfw_error);

  // create a window with an opengl 4.5 context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfw_window = glfwCreateWindow(640, 480, "Pointcloud Viewer", nullptr, nullptr);
  if(!glfw_window)
    throw exception_t{"Couldn't create glfw window"};

  glfwMakeContextCurrent(glfw_window);
}

// Constructor deinitializes glfw and destroays all windows
Instance::~Instance()
{
  glfwDestroyWindow(glfw_window);
  glfw_window = nullptr;

  glfwTerminate();
}

GLFWwindow* glfw_window = nullptr;

void throw_glfw_error(int error, const char* description)
{
  print_error("glfw error(", error, "): ", description);
}

} // namespace mainwindow
} // namespace pointcloud_viewer
