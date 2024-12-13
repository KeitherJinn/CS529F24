#include "CollisionGenerator.h"
#include "AABB.h"
#include "OBB.h"
#include "Circle.h"

CollisionGenerator::CollisionGenerator() {
    initializeCollisionMatrix();
}

bool CollisionGenerator::generateContact(PhysicsBody* body1, PhysicsBody* body2, Contact& contact) {
    Shape* shape1 = body1->getShape();
    Shape* shape2 = body2->getShape();

    if (!shape1 || !shape2) return false;

    int type1 = static_cast<int>(shape1->getType());
    int type2 = static_cast<int>(shape2->getType());

    CollisionTest test = collisionTests[type1][type2];
    if (test) {
        if (test(shape1, shape2, contact)) {
            contact.bodies[0] = body1;
            contact.bodies[1] = body2;
            return true;
        }
    }
    return false;
}

bool CollisionGenerator::AABBvsAABB(const Shape* a, const Shape* b, Contact& contact) {
    const AABB* aabb1 = static_cast<const AABB*>(a);
    const AABB* aabb2 = static_cast<const AABB*>(b);

    Vector3 min1 = aabb1->getMin();
    Vector3 max1 = aabb1->getMax();
    Vector3 min2 = aabb2->getMin();
    Vector3 max2 = aabb2->getMax();

    if (max1.x < min2.x || min1.x > max2.y) return false;
    if (max1.y < min2.y || min1.y > max2.y) return false;

    contact.point = (aabb1->getCenter() + aabb2->getCenter()) * 0.5f;
    return true;
}

bool CollisionGenerator::OBBvsOBB(const Shape* a, const Shape* b, Contact& contact) {
    const OBB* obb1 = static_cast<const OBB*>(a);
    const OBB* obb2 = static_cast<const OBB*>(b);

    Vector3 centerDiff = obb2->getCenter() - obb1->getCenter();

    float scale = obb1->getHalfExtents().x * 2;

    Vector3 axes[4] = {
        obb1->getRight().normalized(),
        obb1->getUp().normalized(),
        obb2->getRight().normalized(),
        obb2->getUp().normalized(),
    };

    for (int i = 0; i < 4; i++) {
        float min1 = 0.0f, min2 = 0.0f, max1 = 0.0f, max2 = 0.0f;

        obb1->project(axes[i], min1, max1);
        obb2->project(axes[i], min2, max2);

        float extent1 = (max1 - min1) * 0.5f;
        float extent2 = (max2 - min2) * 0.5f;

        float rawDist = std::abs(centerDiff.dot(axes[i]));
        float scaledDist = rawDist * scale;

        if (scaledDist > extent1 + extent2) return false;
    }

    contact.point = (obb1->getCenter() + obb2->getCenter()) * 0.5f;
    return true;
}

bool CollisionGenerator::AABBvsOBB(const Shape* a, const Shape* b, Contact& contact) {
    const AABB* aabb = static_cast<const AABB*>(a);
    OBB tempObb(aabb->getCenter(), aabb->getHalfExtents());
    return OBBvsOBB(&tempObb, b, contact);
}

bool CollisionGenerator::OBBvsAABB(const Shape* a, const Shape* b, Contact& contact) {
    return AABBvsOBB(b, a, contact);
}

void CollisionGenerator::initializeCollisionMatrix() {
    // Initialize all to nullptr
    for (auto& row : collisionTests)
        for (auto& test : row)
            test = nullptr;

    // Set up existing collision tests
    collisionTests[static_cast<int>(Shape::Type::AABB)][static_cast<int>(Shape::Type::AABB)] = &AABBvsAABB;
    collisionTests[static_cast<int>(Shape::Type::OBB)][static_cast<int>(Shape::Type::AABB)] = &OBBvsOBB;
    collisionTests[static_cast<int>(Shape::Type::AABB)][static_cast<int>(Shape::Type::OBB)] = &AABBvsOBB;
    collisionTests[static_cast<int>(Shape::Type::OBB)][static_cast<int>(Shape::Type::AABB)] = &OBBvsAABB;
    // TODO: register all the collision functions in the test table

}

bool CollisionGenerator::CirclevsCircle(const Shape* a, const Shape* b, Contact& contact) {
    const Circle* circle1 = static_cast<const Circle*>(a);
    const Circle* circle2 = static_cast<const Circle*>(b);

    Vector3 diff = circle2->getCenter() - circle1->getCenter();
    float distSquared = diff.magnitudSquared();
    float radiusSum = circle1->getRadius() + circle2->getRadius();

    if (distSquared <= radiusSum * radiusSum) {
        contact.point = circle1->getCenter() + diff * 0.5f;
        return true;
    }
    return false;
}

bool CollisionGenerator::CirclevsAABB(const Shape* a, const Shape* b, Contact& contact) {
    const Circle* circle = static_cast<const Circle*>(a);
    const AABB* aabb = static_cast<const AABB*>(b);

    // Find closest point on AABB to circle center
    Vector3 closestPoint;
    Vector3 circleCenter = circle->getCenter();

    // For each axis, clamp circle center to AABB bounds
    closestPoint.x = std::max(aabb->getMin().x, std::min(circleCenter.x, aabb->getMax().x));
    closestPoint.y = std::max(aabb->getMin().y, std::min(circleCenter.y, aabb->getMax().y));

    // Check if closest point is within circle's radius
    Vector3 diff = circleCenter - closestPoint;
    float distSquared = diff.magnitudSquared();

    if (distSquared <= circle->getRadius() * circle->getRadius()) {
        contact.point = closestPoint;
        return true;
    }
    return false;
}

bool CollisionGenerator::AABBvsCircle(const Shape* a, const Shape* b, Contact& contact) {
    return CirclevsAABB(b, a, contact);
}

bool CollisionGenerator::CirclevsOBB(const Shape* a, const Shape* b, Contact& contact) {
    const Circle* circle = static_cast<const Circle*>(a);
    const OBB* obb = static_cast<const OBB*>(b);

    // Convert circle center to OBB's local space
    Vector3 circleCenter = circle->getCenter() - obb->getCenter();

    // Get local space position using OBB's axes
    Vector3 localCenter(
        circleCenter.dot(obb->getRight()),
        circleCenter.dot(obb->getUp()),
        0.0f
    );

    // Find closest point in local space (clamp to OBB bounds)
    Vector3 closestPoint;
    closestPoint.x = std::max(-obb->getHalfExtents().x,
        std::min(localCenter.x, obb->getHalfExtents().x));
    closestPoint.y = std::max(-obb->getHalfExtents().y,
        std::min(localCenter.y, obb->getHalfExtents().y));

    // Convert back to world space
    Vector3 worldClosest = obb->getCenter() +
        obb->getRight() * closestPoint.x +
        obb->getUp() * closestPoint.y;

    // Check if closest point is within circle's radius
    Vector3 diff = circle->getCenter() - worldClosest;
    float distSquared = diff.magnitudSquared();

    if (distSquared <= circle->getRadius() * circle->getRadius()) {
        contact.point = worldClosest;
        return true;
    }
    return false;
}

bool CollisionGenerator::OBBvsCircle(const Shape* a, const Shape* b, Contact& contact) {
    return CirclevsOBB(b, a, contact);
}