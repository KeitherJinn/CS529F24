#include "Renderer.h"
#include "GameWindow.h"
#include <iostream>

int main() {
    try {
        GameWindow window(800, 600, "Window");
        Renderer renderer(window);
        Vector3 v1 = Vector3(-0.5f, -0.5f, 0.0f);
        Vector3 v2 = Vector3(0.5f, -0.5f, 0.0f);
        Vector3 v3 = Vector3(0.0f, 0.5f, 0.0f);
        Matrix4 model = Matrix4();
        Vector3 v4 = model * v1;
        renderer.drawTriangle(v1, v2, v3, model);
        while (!window.shouldClose()) {
            window.pollEvents();
            renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);
            // Render your 3D scene here
            renderer.UpdateTriangle(model.rotationY(5 * glfwGetTime()));

            renderer.swapBuffers();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}