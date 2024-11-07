#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Vector3.h"
#include "Matrix4.h"
#include <glew.h>

using namespace std;

class Shader {
public:
    Shader(const string& shaderPaths);
    ~Shader();

    void use() const;
    void unuse() const;

    void setUInt(const string& name, unsigned int value) const;
    void setInt(const string& name, int value) const;
    void set2Int(const string& name, int v0, int v1) const;
    void setFloat(const string& name, float value) const;
    void setVec2(const string& name, float x, float y) const;
    void setVec3(const string& name, const Vector3& value) const;
    void setVec4(const string& name, float x, float y, float z, float w) const;
    void setMat4(const string& name, const Matrix4& value) const;

    unsigned int getID() const { return programID; }

private:
    unsigned int programID;
    mutable unordered_map<string, int> uniformLocationCache;
    unordered_map<GLenum, unsigned int> shaderIDs;

    unsigned int loadShader(const string& shaderCode, GLenum shaderType);
    void linkShaders();
    int getUniformLocation(const string& name) const;
    GLenum getShaderType(const string& filePath);
    string readShaderFile(const string& filePath);
    string toLowercase(const string& str);
};