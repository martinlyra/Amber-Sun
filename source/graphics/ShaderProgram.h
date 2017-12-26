//
// Created by Martin Lyrå on 2017-12-25.
//

#ifndef AMBER_SUN_SHADERPROGRAM_H
#define AMBER_SUN_SHADERPROGRAM_H

#include "maths/Matrix4.h"

class ShaderProgram {
public:
    ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile);
    ~ShaderProgram();

    //bool Compile();

    void Bind();
    void Unbind();

    int GetAttribute(const char *attributeName);
    int GetUniform(const char *uniformName);

private:
    typedef unsigned int Shader;

    unsigned int programId;

    Shader CreateShader(const char *shader_filename, unsigned int type);
};


#endif //AMBER_SUN_SHADERPROGRAM_H
