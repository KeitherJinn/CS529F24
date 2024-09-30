#include "Renderer.h"
#include "GameWindow.h"
#include <iostream>


int main() {
    try {
        GameWindow window(800, 600, "Window");
        Renderer renderer(window);
        unsigned int shaderProgram = renderer.drawTriangle(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.5f, 0.0f));

        while (!window.shouldClose()) {
            window.pollEvents();

            renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);

            // Render your 3D scene here
			glUseProgram(shaderProgram);
			glDrawArrays(GL_TRIANGLES, 0, 3);

            renderer.swapBuffers();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}