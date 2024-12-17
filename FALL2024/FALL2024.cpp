#include <windows.h>

#include "Renderer.h"
#include "GameWindow.h"
#include "Input.h"
#include "SceneGraph.h"
#include "RenderableNode.h"
#include "TrianglePrimitive.h"
#include "RectanglePrimitive.h"
#include "FramerateController.h"
#include "EventManager.h"
#include "GameObject.h"
#include "PhysicsBody.h"
#include "AABB.h"
#include "OBB.h"
#include "Circle.h"
#include "PhysicsManager.h"
#include "Tests.h"
#include "Camera.h"
#include "Keys.h"
#include "Player.h"
#include "Catches.h"

// Well this is a very simple game like magic tiles, but there isn't any music in it so we use some functions to simulate the spawning of the tiles.

int main() {
        // Create window, renderer and input systems
        GameWindow window(800, 800, "2D Example");
        Renderer renderer(window);
        Input input(window);
        FramerateController* framerateController = FramerateController::GetInstance();

        // Create scene graph
        SceneGraph sceneGraph;

        // Set up camera (view and projection matrices)
        Camera camera;
        camera.setLocalPosition(Vector3(0.0f, 0.0f, 1.0f));
        camera.setTarget(Vector3(0.0f, 0.0f, 0.0f));
        float aspectRatio = static_cast<float>(window.getWidth()) / window.getHeight();
        float bottom = -window.getWidth() * 0.5f;
        float top = window.getHeight() * 0.5f;
        float left = -window.getWidth() * 0.5f;
        float right = window.getWidth() * 0.5f;
        camera.setProjectionMatrix(left, right, top, bottom, aspectRatio);

        Matrix4 projectionMatrix = camera.getProjectionMatrix();
        Matrix4 viewMatrix = camera.getViewMatrix();

        Vector3 keyScale = Vector3(60.0f, 60.0f, 1.0f);

        // Drawable objects
        auto boxQ = std::make_shared<Keys>("Icon1", &renderer, "Qtex.png");
        boxQ->setLocalPosition(Vector3(-5.0f, -6.0f, 0.0f));
        boxQ->setLocalScale(keyScale);

        auto boxW = std::make_shared<Keys>("Icon2", &renderer, "Wtex.png");
        boxW->setLocalPosition(Vector3(-4.0f, -6.0f, 0.0f));
        boxW->setLocalScale(keyScale);

        auto boxE = std::make_shared<Keys>("Icon3", &renderer, "Etex.png");
        boxE->setLocalPosition(Vector3(-3.0f, -6.0f, 0.0f));
        boxE->setLocalScale(keyScale);

        auto boxR = std::make_shared<Keys>("Icon4", &renderer, "Rtex.png");
        boxR->setLocalPosition(Vector3(-2.0f, -6.0f, 0.0f));
        boxR->setLocalScale(keyScale);

        auto boxT = std::make_shared<Keys>("Icon5", &renderer, "Ttex.png");
        boxT->setLocalPosition(Vector3(-1.0f, -6.0f, 0.0f));
        boxT->setLocalScale(keyScale);

        auto boxY = std::make_shared<Keys>("Icon6", &renderer, "Ytex.png");
        boxY->setLocalPosition(Vector3(1.0f, -6.0f, 0.0f));
        boxY->setLocalScale(keyScale);

        auto boxU = std::make_shared<Keys>("Icon7", &renderer, "Utex.png");
        boxU->setLocalPosition(Vector3(2.0f, -6.0f, 0.0f));
        boxU->setLocalScale(keyScale);

        auto boxI = std::make_shared<Keys>("Icon8", &renderer, "Itex.png");
        boxI->setLocalPosition(Vector3(3.0f, -6.0f, 0.0f));
        boxI->setLocalScale(keyScale);

        auto boxO = std::make_shared<Keys>("Icon9", &renderer, "Otex.png");
        boxO->setLocalPosition(Vector3(4.0f, -6.0f, 0.0f));
        boxO->setLocalScale(keyScale);

        auto boxP = std::make_shared<Keys>("IconX", &renderer, "Ptex.png");
        boxP->setLocalPosition(Vector3(5.0f, -6.0f, 0.0f));
        boxP->setLocalScale(keyScale);

        auto boxSP = std::make_shared<Keys>("Icon0", &renderer, "SPtex.png");
        boxSP->setLocalPosition(Vector3(0.0f, -6.0f, 0.0f));
        boxSP->setLocalScale(keyScale);

        sceneGraph.addNode(boxQ);
        sceneGraph.addNode(boxW);
        sceneGraph.addNode(boxE);
        sceneGraph.addNode(boxR);
        sceneGraph.addNode(boxT);
        sceneGraph.addNode(boxY);
        sceneGraph.addNode(boxU);
        sceneGraph.addNode(boxI);
        sceneGraph.addNode(boxO);
        sceneGraph.addNode(boxP);
        sceneGraph.addNode(boxSP);

        float angle = 0.0f;
        float speed = 5.0f;
        float deltaTime = 0.0f;
        int expectedFrameRate = 60; // 1000;
        framerateController->SetTargetFramerate(expectedFrameRate);

        //testRotationMatrices();
        //testMatrixMultiplication();
        //testVectorTransformation();
        //testTranslationMatrix();
        //testScaleMatrix();
        
        double score = 0;

        std::shared_ptr<Catches> bodies[10];
        Vector3 velocity = Vector3(0.0f, -4.0f, 0.0f);
        Vector3 posList[10];

        for (int i = 0; i < 10; i++) { // simulates music game track
            score += 10;
            int x = rand() % 10;
            int y = rand() % 25;
            bodies[i] = std::make_shared<Catches>("Catch", &renderer, "Greentex.png");
            posList[i] = Vector3(x - 5.0f, y + 7.0f, 0.0f);
            for (int j = 0; j < i; j++) {
                if (posList[i] == posList[j]) {
                    x = rand() % 10;
                    y = rand() % 25;
                    posList[i] = Vector3(x - 5.0f, y + 7.0f, 0.0f);
                    j = 0;
                }
            }
            bodies[i]->setLocalPosition(posList[i]);
            bodies[i]->setLocalScale(keyScale);
            sceneGraph.addNode(bodies[i]);
            bodies[i]->body->setVelocity(velocity);
        }

        while (!window.shouldClose()) {
            renderer.clear(0.0f, 0.0f, 0.0f, 1.0f);
            framerateController->FrameStart();              // record the time from frame start
            
            score += deltaTime*10;

            for (int i = 0; i < 10; i++) { // simulates music game track
                if (bodies[i]->getLocalPosition().y < -7.0f) {
                    int x = rand() % 10;
                    int y = rand() % 25;
                    posList[i] = Vector3(x - 5.0f, y + 7.0f, 0.0f);
                    for (int j = 0; j < i; j++) {
                        if (posList[i] == posList[j]) {
                            x = rand() % 10;
                            y = rand() % 25;
                            posList[i] = Vector3(x - 5.0f, y + 7.0f, 0.0f);
                            j = 0;
                        }
                    }
                    bodies[i]->setLocalPosition(posList[i]);
                }
            }

            // When you press the key...
            if (input.isKeyHeld(k_Q)) {
                boxQ->changeTex("QtexPressed.png");
                boxQ->isPressed(true);
            }
            else {
                boxQ->changeTex("Qtex.png");
                boxQ->isPressed(false);
            }
            if (input.isKeyHeld(k_W)) {
                boxW->changeTex("WtexPressed.png");
                boxW->isPressed(true);
            }
            else {
                boxW->changeTex("Wtex.png");
                boxW->isPressed(false);
            }
            if (input.isKeyHeld(k_E)) {
                boxE->changeTex("EtexPressed.png");
                boxE->isPressed(true);
            }
            else {
                boxE->changeTex("Etex.png");
                boxE->isPressed(false);
            }
            if (input.isKeyHeld(k_R)) {
                boxR->changeTex("RtexPressed.png");
                boxR->isPressed(true);
            }
            else {
                boxR->changeTex("Rtex.png");
                boxR->isPressed(false);
            }
            if (input.isKeyHeld(k_T)) {
                boxT->changeTex("TtexPressed.png");
                boxT->isPressed(true);
            }
            else {
                boxT->changeTex("Ttex.png");
                boxT->isPressed(false);
            }
            if (input.isKeyHeld(k_Y)) {
                boxY->changeTex("YtexPressed.png");
                boxY->isPressed(true);
            }
            else {
                boxY->changeTex("Ytex.png");
                boxY->isPressed(false);
            }
            if (input.isKeyHeld(k_U)) {
                boxU->changeTex("UtexPressed.png");
                boxU->isPressed(true);
            }
            else {
                boxU->changeTex("Utex.png");
                boxU->isPressed(false);
            }
            if (input.isKeyHeld(k_I)) {
                boxI->changeTex("ItexPressed.png");
                boxI->isPressed(true);
            }
            else {
                boxI->changeTex("Itex.png");
                boxI->isPressed(false);
            }
            if (input.isKeyHeld(k_O)) {
                boxO->changeTex("OtexPressed.png");
                boxO->isPressed(true);
            }
            else {
                boxO->changeTex("Otex.png");
                boxO->isPressed(false);
            }
            if (input.isKeyHeld(k_P)) {
                boxP->changeTex("PtexPressed.png");
                boxP->isPressed(true);
            }
            else {
                boxP->changeTex("Ptex.png");
                boxP->isPressed(false);
            }
            if (input.isKeyHeld(k_SPACE)) {
                boxSP->changeTex("SPtexPressed.png");
                boxSP->isPressed(true);
            }
            else {
                boxSP->changeTex("SPtex.png");
                boxSP->isPressed(false);
            }

            if (PhysicsManager::Instance().update(deltaTime)) {
                score -= 0.5;
            }
            
            input.update(); 
            if (input.isKeyHeld(K_ESCAPE)) { //press ESC to end the game and check the score
                std::cout << "Your final score is: " << score << endl;
                break;
            }

            sceneGraph.update(deltaTime);

            sceneGraph.draw(viewMatrix, projectionMatrix);

            //std::cout << "Angle for player: " << angle << std::endl;
            //std::cout << "========================" << std::endl;
            renderer.swapBuffers();
            window.pollEvents();

            framerateController->FrameEnd();
            deltaTime = framerateController->DeltaTime;

        }

        return 0;
}
