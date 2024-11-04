#include <iostream>
#include <memory>
#include <vector>
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

int main() {
    try {
        // Create window and renderer
        GameWindow window(800, 600, "Triangle Rotation Test");
        Renderer renderer(window);

        // Create scene graph
        SceneGraph sceneGraph;

        // Create 3 triangles in different positions
        auto triangle1 = std::make_shared<TrianglePrimitive>("RedTriangle", &renderer);
        triangle1->setColor(Vector3(1.0f, 0.0f, 0.0f));
        triangle1->setLocalPosition(Vector3(-1.0f, 0.0f, 0.0f));
        triangle1->setLocalScale(Vector3(0.5f, 0.5f, 0.5f));
        sceneGraph.addNode(triangle1);

        auto triangle2 = std::make_shared<TrianglePrimitive>("GreenTriangle", &renderer);
        triangle2->setColor(Vector3(0.0f, 1.0f, 0.0f));
        triangle2->setLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
        triangle2->setLocalScale(Vector3(0.5f, 0.5f, 0.5f));
        sceneGraph.addNode(triangle2);

        auto triangle3 = std::make_shared<TrianglePrimitive>("BlueTriangle", &renderer);
        triangle3->setColor(Vector3(0.0f, 0.0f, 1.0f));
        triangle3->setLocalScale(Vector3(0.5f, 0.5f, 0.5f));
        triangle3->setLocalPosition(Vector3(0.5f, 0.0f, 0.0f));
        sceneGraph.addNode(triangle3);

        // Set up camera (view and projection matrices)
        Vector3 cameraPos(0.0f, 0.0f, 2.0);
        Vector3 cameraTarget = cameraPos + Vector3(0.0f, 0.0f, -1.0f);
        Vector3 upVector(0.0f, 1.0f, 0.0f);
        Matrix4 viewMatrix = Matrix4::lookAt(cameraPos, cameraTarget, upVector);
        float aspectRatio = static_cast<float>(window.getWidth()) / window.getHeight();
        Matrix4 projectionMatrix = Matrix4::perspective(45.0f * 3.14159f / 180.0f, aspectRatio, 0.1f, 100.0f);

        // Main loop
        float rotationAngle = 0.0f;
        float deltaTime = 1.0f / 60.0f; // Assume 60 FPS
        while (!window.shouldClose()) {
            renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);

            // Update rotation for the triangle node
            rotationAngle += 1.0f * deltaTime * 0.05;
            sceneGraph.setRootRotation(Vector3(0.0f, rotationAngle, 0.0f));
            sceneGraph.update(deltaTime);

            // Draw scene
            triangle1->localToWorldSpace();
            triangle2->localToWorldSpace();
            triangle3->localToWorldSpace();
            sceneGraph.draw(viewMatrix, projectionMatrix);
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