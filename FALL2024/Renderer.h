#pragma once

#include <glew.h>
#include <glfw3.h>
#include "GameWindow.h"
#include "Vector3.h"
#include "Matrix4.h"

class Renderer {
public:
    Renderer(GameWindow& window);

    // Delete copy constructor and assignment operator
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void clear(float r, float g, float b, float a);
    void draw(unsigned int dataCount, GLenum drawingMode, bool indexed);
    void swapBuffers();

    GameWindow& getWindowPtr() { return pWindow; }

private:
    void initialize();
    void setupCallbacks();
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    GameWindow& pWindow;
};