#include "Renderer.h"
#include <stdexcept>

void APIENTRY openglCallbackFunction(
    GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* userParam)
{
    std::string sourceStr;
    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             sourceStr = "API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceStr = "Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceStr = "Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     sourceStr = "Application"; break;
    case GL_DEBUG_SOURCE_OTHER:           sourceStr = "Other"; break;
    }

    std::string typeStr;
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               typeStr = "Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "Deprecated Behavior"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeStr = "Undefined Behavior"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         typeStr = "Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         typeStr = "Performance"; break;
    case GL_DEBUG_TYPE_MARKER:              typeStr = "Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          typeStr = "Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           typeStr = "Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER:               typeStr = "Other"; break;
    }

    std::string severityStr;
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         severityStr = "High"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       severityStr = "Medium"; break;
    case GL_DEBUG_SEVERITY_LOW:          severityStr = "Low"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "Notification"; break;
    }

    std::cerr << "OpenGL Debug Message\n"
        << "Source: " << sourceStr << "\n"
        << "Type: " << typeStr << "\n"
        << "ID: " << id << "\n"
        << "Severity: " << severityStr << "\n"
        << "Message: " << message << std::endl;
}

Renderer::Renderer(GameWindow& window) : pWindow(window) {
    initialize();
    setupCallbacks();
}

void Renderer::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::swapBuffers() {
    glfwSwapBuffers(pWindow.getNativeWindow());
}

void Renderer::initialize() {
    pWindow.setWindowHints([]() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        });

    glfwMakeContextCurrent(pWindow.getNativeWindow());

    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    // Enable debug
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Makes sure errors are reported immediately
    glDebugMessageCallback(openglCallbackFunction, nullptr);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, pWindow.getWidth(), pWindow.getHeight());
}

void Renderer::draw(unsigned int dataCount, GLenum drawingMode, bool indexed) {
    if (indexed) {
        glDrawElements(drawingMode, dataCount, GL_UNSIGNED_INT, 0);
    }
    else {
        glDrawArrays(drawingMode, 0, dataCount);
    }

}

void Renderer::setupCallbacks() {
    pWindow.setResizeCallback([this](GLFWwindow* window, int width, int height) {
        this->framebufferSizeCallback(window, width, height);
        });
}

void Renderer::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    // Additional rendering adjustments can be made here
}