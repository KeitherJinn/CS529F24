#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

Shader::Shader(const std::string& shaderPaths) {
    istringstream pathsStream(shaderPaths);
    string shaderPath;

    while (getline(pathsStream, shaderPath)) {
        string shaderCode = readShaderFile(shaderPath);
        GLenum shaderType = getShaderType(shaderPath);

        if (shaderType != GL_INVALID_ENUM) {
            unsigned int shaderID = loadShader(shaderCode, shaderType);
            shaderIDs[shaderType] = shaderID;
        }
        else {
            cerr << "Unrecognized shader type for file: " << shaderPath << std::endl;
        }
    }
    linkShaders();
}

Shader::~Shader() {
    glDeleteProgram(programID);
}

void Shader::use() const {
    glUseProgram(programID);
}

void Shader::unuse() const {
    glUseProgram(0);
}

void Shader::setUInt(const string& name, unsigned int value) const {
    glUniform1ui(getUniformLocation(name), value);
}

void Shader::setInt(const string& name, int value) const {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::set2Int(const string& name, int v0, int v1) const {
    glUniform2i(getUniformLocation(name), v0, v1);
}

void Shader::setFloat(const string& name, float value) const {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setVec2(const string& name, float x, float y) const {
    glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setVec3(const string& name, const Vector3& value) const {
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setVec4(const string& name, float x, float y, float z, float w) const {
    glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::setMat4(const string& name, const Matrix4& value) const {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value.getData());
}


unsigned int Shader::loadShader(const string& shaderCode, GLenum shaderType) {
    unsigned int shaderID = glCreateShader(shaderType);
    const char* code = shaderCode.c_str();
    glShaderSource(shaderID, 1, &code, nullptr);
    glCompileShader(shaderID);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cerr << "Shader compilation error: " << infoLog << std::endl;
    }

    return shaderID;
}

void Shader::linkShaders() {
    programID = glCreateProgram();

    for (const auto& [type, id] : shaderIDs) {
        glAttachShader(programID, id);
    }

    glLinkProgram(programID);

    int success;
    char infoLog[512];
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        cerr << "Shader program linking error: " << infoLog << endl;
    }

    for (const auto& [type, id] : shaderIDs) {
        glDeleteShader(id);
    }
}

int Shader::getUniformLocation(const string& name) const {
    auto it = uniformLocationCache.find(name);
    if (it != uniformLocationCache.end()) {
        return it->second;
    }

    int location = glGetUniformLocation(programID, name.c_str());
    uniformLocationCache[name] = location;

    if (location == -1) {
        cerr << "Warning: Uniform '" << name << "' doesn't exist!" << endl;
    }

    return location;
}

GLenum Shader::getShaderType(const string& filePath) {
    string lowercasePath = toLowercase(filePath);
    if (lowercasePath.find("vertex") != string::npos) return GL_VERTEX_SHADER;
    if (lowercasePath.find("fragment") != string::npos) return GL_FRAGMENT_SHADER;
    if (lowercasePath.find("geometry") != string::npos) return GL_GEOMETRY_SHADER;
    if (lowercasePath.find("compute") != string::npos) return GL_COMPUTE_SHADER;
    return GL_INVALID_ENUM;
}

string Shader::readShaderFile(const string& filePath) {
    ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        cerr << "Failed to open shader file: " << filePath << endl;
        return "";
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}

string Shader::toLowercase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return tolower(c); });
    return result;
}