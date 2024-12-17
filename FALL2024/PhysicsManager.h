#pragma once

#include "CollisionGenerator.h"
#include "EventManager.h"
#include "CollisionEvent.h"
#include <vector>

class PhysicsManager {
public:
    static PhysicsManager& Instance();

    void removeBody(PhysicsBody* body);
    bool update(float deltatime);
    void addBody(PhysicsBody* body);

    const std::vector<PhysicsBody*>& getBodies() const { return bodies; }

private:
    PhysicsManager() = default;
    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;

    bool checkCollisions();

    std::vector<PhysicsBody*> bodies;
    CollisionGenerator collisionGenerator;
};