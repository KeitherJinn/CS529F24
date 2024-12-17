#pragma once
#include "GameObject.h"
#include "PhysicsBody.h"
#include "PhysicsManager.h"
#include "AABB.h"
#include <iostream>
#include <memory>

// the keys you are going to press

class Keys : public GameObject
{
public:
	Keys(const std::string name, Renderer* renderer, std::string tex = "ImgTexture120_100.bmp") : GameObject(name, renderer, tex) {
        // Register GameObject in the list of collision listeners
        collisionListener = new CollisionListener(this);

        // set a collider
        body = std::make_unique<PhysicsBody>(this);
        auto shape = std::make_shared<AABB>(
            Vector3(-0.0f, -0.0f, 0.0f),  // SAME width/height of the box
            Vector3(1.0f, 1.0f, 0.0f));
        body->setShape(shape);
        PhysicsManager::Instance().addBody(body.get());

        // set a callback
        collisionListener->setCallback([this](RenderableNode* self, RenderableNode* other) {
            
            });
	}
    ~Keys() {
        
    }
    void changeTex(std::string tex = "megaman_24_24.bmp") {
        createMaterial(tex);
    }
    void isPressed(bool pressed) {
        if(pressed) PhysicsManager::Instance().removeBody(body.get());
        else PhysicsManager::Instance().addBody(body.get());
    }

    std::unique_ptr<PhysicsBody> body;
};