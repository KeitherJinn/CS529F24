#pragma once


#include "EventListener.h"
#include "RectanglePrimitive.h"
#include "CollisionEvent.h"
#include "CollisionListener.h"

class GameObject : public RectanglePrimitive
{
public:
	GameObject(const std::string name, Renderer* renderer, std::string tex = "ImgTexture120_100.bmp")
		: RectanglePrimitive(name, renderer, tex) {

        // Register GameObject in the list of collision listeners
        collisionListener = new CollisionListener(this);

        // set a callback
        collisionListener->setCallback([this](RenderableNode* self, RenderableNode* other) {
            std::cout << "Collision beteween " << self->getName() << " and " << other->getName() << std::endl;
            });
	}

    ~GameObject() {
        delete collisionListener;
    }

    virtual void update(float deltaTime) override {
        //std::cout << "Position of " << this->getName() << " is: " << this->getLocalPosition() << std::endl;
        RenderableNode::update(deltaTime);
    }

	CollisionListener* collisionListener;
};