#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include "Renderer.h"
#include "GameWindow.h"
#include "SceneGraph.h"
#include "RenderableNode.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "TrianglePrimitive.h"
#include "Camera.h"
#include "Input.h"

int main() {
    try {
        // Create window and renderer
        GameWindow window(800, 600, "Triangle Rotation Test");
        Renderer renderer(window);
        Input input(window);

        // Create scene graph
        SceneGraph sceneGraph;

        // Create 3 triangles in different positions
        auto triangle1 = std::make_shared<TrianglePrimitive>("RedTriangle", &renderer);
        triangle1->setColor(Vector3(1.0f, 0.0f, 0.0f));
        triangle1->setLocalPosition(Vector3(-4.0f, 0.0f, 0.0f));
        triangle1->setLocalScale(Vector3(0.2f, 0.2f, 0.2f));
        sceneGraph.addNode(triangle1);

        auto triangle2 = std::make_shared<TrianglePrimitive>("GreenTriangle", &renderer);
        triangle2->setColor(Vector3(0.0f, 1.0f, 0.0f));
        triangle2->setLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
        triangle2->setLocalScale(Vector3(0.2f, 0.2f, 0.2f));
        sceneGraph.addNode(triangle2);

        auto triangle3 = std::make_shared<TrianglePrimitive>("BlueTriangle", &renderer);
        triangle3->setColor(Vector3(0.0f, 0.0f, 1.0f));
        triangle3->setLocalScale(Vector3(0.2f, 0.2f, 0.2f));
        triangle3->setLocalPosition(Vector3(2.0f, 0.0f, 0.0f));
        triangle3->setLocalRotation(Vector3(0.0f, 3.14159f/2.0f, 0.0f));
        sceneGraph.addNode(triangle3);

        // Set up camera (view and projection matrices)
        Vector3 cameraPos(0.0f, 0.0f, 2.0f);
        Vector3 cameraTarget = cameraPos + Vector3(0.0f, 0.0f, -1.0f);
        Camera c = Camera();
        c.setLocalPosition(cameraPos);
        c.setTarget(cameraTarget);
        float aspectRatio = static_cast<float>(window.getWidth()) / window.getHeight();
        c.setProjectionMatrix(aspectRatio);
        float deltaTime = 0.0f;
        float currentFrame = 0.0f;
        float lastFrame = 0.0f;
        float positionX = 0.0f;
        float positionY = 0.0f;
        // Main loop
        float rotationAngle = 0.0f;
        while (!window.shouldClose()) {
            input.update();

            currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);

            if (input.isKeyHeld(A_RIGHT))
                positionX += 2.0f * deltaTime;
            if (input.isKeyHeld(A_LEFT))
                positionX -= 2.0f * deltaTime;
            if (input.isKeyHeld(A_UP))
                positionY += 2.0f * deltaTime;
            if (input.isKeyHeld(A_DOWN))
                positionY -= 2.0f * deltaTime;

            // Update rotation for the triangle node
            rotationAngle += 1.0f * deltaTime;
            sceneGraph.setRootPosition(Vector3(positionX, positionY, 0.0f));
            sceneGraph.setRootRotation(Vector3(0.0f, rotationAngle, 0.0f));
            sceneGraph.update(deltaTime);

            // Draw scene
            triangle1->localToWorldSpace();
            triangle2->localToWorldSpace();
            triangle3->localToWorldSpace();
            sceneGraph.draw(c.getViewMatrix(), c.getProjectionMatrix());
            triangle1->worldToLocalSpace();
            triangle2->worldToLocalSpace();
            triangle3->worldToLocalSpace();

            renderer.swapBuffers();
            window.pollEvents();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}