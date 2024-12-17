#pragma once
#include "RenderableNode.h"

class RectanglePrimitive : public RenderableNode {
public:
    RectanglePrimitive(const std::string name,
        std::shared_ptr<GeometryBuffer>& geometryBuffer,
        Renderer* renderer, std::string tex = "ImgTexture120_100.bmp");
    RectanglePrimitive(const std::string name, Renderer* renderer, std::string tex = "ImgTexture120_100.bmp");
    ~RectanglePrimitive() = default;

    auto getGeometryBuffer() { return mesh ? mesh->getGeometryBuffer() : nullptr; }

protected:
    virtual void createMesh();
    virtual void createMaterial(std::string tex);
};