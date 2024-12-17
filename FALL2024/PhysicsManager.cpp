#include "PhysicsManager.h"
#include <algorithm>

PhysicsManager& PhysicsManager::Instance() {
    static PhysicsManager instance;
    return instance;
}


void PhysicsManager::removeBody(PhysicsBody* body) {
    bodies.erase(
        std::remove(bodies.begin(), bodies.end(), body),
        bodies.end()
    );
}

void PhysicsManager::addBody(PhysicsBody* body) {
    if (std::find(bodies.begin(), bodies.end(), body) == bodies.end()) {
        bodies.push_back(body);
    }
}

bool PhysicsManager::update(float deltatime) {
    for (auto body : bodies) {
        body->integrate(deltatime);
    }
    bool res = checkCollisions();
    return res;
}

bool PhysicsManager::checkCollisions() {
    Contact contact;
    bool sign = false;
    for (size_t i = 0; i < bodies.size(); i++) {
        for (size_t j = i + 1; j < bodies.size(); j++) {
            if (collisionGenerator.generateContact(bodies[i], bodies[j], contact)) {
                // Collision detected, broadcast event
                CollisionEvent event(
                    contact.bodies[0]->getOwner(),
                    contact.bodies[1]->getOwner()
                    );
                EventManager::Instance().BroadcastEvent(event);
                sign = true;
            }
        }
    }
    return sign;
}