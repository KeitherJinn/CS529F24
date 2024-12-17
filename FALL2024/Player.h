#pragma once
#include "GameObject.h"
#include "PhysicsBody.h"
#include "PhysicsManager.h"
#include "AABB.h"
#include <iostream>
#include <memory>

// useless

class Player : public GameObject
{
public:
    Player(const std::string name, Renderer* renderer, std::string tex = "megaman_24_24.bmp") : GameObject(name, renderer, tex) {
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
            std::cout << "Collision beteween " << self->getName() << " and " << other->getName() << std::endl;
            });
    }
    ~Player() {
        
    }

    std::unique_ptr<PhysicsBody> body;
};