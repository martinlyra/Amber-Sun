//
// Created by Martin Lyrå on 2017-12-25.
//

#include "ShaderProgram.h"

#include "glad.h"

#include <string>
#include <cstdio>
#include <fstream>

// TODO: Make this macro a constexpr function
#define FILENAME_POSIX(x) (strrchr(x, '/') ? strrchr(x, '/') + 1 : x)

void check_opengl_errors(const char* msg)
{
    int e = glGetError();
    if (e)
        std::printf("GLError: %s; %#X", msg, e);
}

/*
ShaderProgram::ShaderProgram(const char *vertexShaderFile, const char *fragmentShaderFile)
: vertexShaderFile(vertexShaderFile), fragmentShaderFile(fragmentShaderFile)
{
    programId = 0;
    vertexId = glCreateShader(GL_VERTEX_SHADER);
    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

bool CompileShader()
{

    return false;
}

bool ShaderProgram::Compile()
{
    std::string vertexCode = LoadContents(vertexShaderFile);
    std::string fragmentCode = LoadContents(fragmentShaderFile);

    return false;
}
*/

void get_opengl_shader_info_log(GLuint shader)
{
    GLint log_length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 0)
    {
        char* info_string_buffer = (char*)malloc(sizeof(char) * log_length);
        glGetShaderInfoLog(shader, log_length, nullptr, info_string_buffer);
        fprintf(stderr, "%s\n", info_string_buffer);
        free(info_string_buffer);
    }
}

void GetOpenGLProgramInfoLog(GLuint program)
{
    GLint log_length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 0)
    {
        char* info_string_buffer = (char*)malloc(sizeof(char) * log_length);
        glGetProgramInfoLog(program, log_length, nullptr, info_string_buffer);
        fprintf(stderr, "%s\n", info_string_buffer);
        free(info_string_buffer);
    }
}

std::string LoadContents(const char* file)
{
    std::string s;
    std::ifstream stream(file, std::ios::in);
    if (stream.is_open()){
        std::string l;
        while(getline(stream, l))
            s += "\n" + l;
        stream.close();
    }
    else std::printf("Unable to open %s", file);
    return s;
}

ShaderProgram::ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile)
{
    Shader vertex_shader = 0;
    Shader fragment_shader = 0;
    programId = glCreateProgram();

    std::printf("Loading vertex shader\n");
    if (vertexShaderFile)
    {
        vertex_shader = CreateShader(vertexShaderFile, GL_VERTEX_SHADER);
        if (!vertex_shader)
        {
            std::printf("Could not open %s\n", vertexShaderFile);
            glDeleteShader(vertex_shader);
        }
        else
        {
            glAttachShader(programId, vertex_shader);
            std::printf("[SHADERPROGRAM %p] vertex shader %s loaded\n", this, FILENAME_POSIX( vertexShaderFile ) );
        }
    }
    std::printf("Loading fragment shader\n");
    if (fragmentShaderFile)
    {
        fragment_shader = CreateShader(fragmentShaderFile, GL_FRAGMENT_SHADER);
        if (!fragment_shader)
        {
            std::printf("Could not open %s\n", fragmentShaderFile);
            glDeleteShader(fragment_shader);
        }
        else
        {
            glAttachShader(programId, fragment_shader);
            std::printf("[SHADERPROGRAM %p] fragment shader %s loaded\n", this, FILENAME_POSIX( fragmentShaderFile ) );
        }
    }

    glLinkProgram(programId);
    glDeleteShader( fragment_shader );
    glDeleteShader( vertex_shader );
    GLint link_ok = GL_FALSE;
    glGetProgramiv(programId, GL_LINK_STATUS, &link_ok);
    if (!link_ok)
    {
        std::printf("glLinkProgram error!\n");
        GetOpenGLProgramInfoLog(programId);
        glDeleteProgram(programId);
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(programId);
}

GLint ShaderProgram::GetAttribute(const char* attributeName)
{
    GLint attribute = glGetAttribLocation(programId, attributeName);
    //if (attribute == -1)
    //fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return attribute;
}

GLint ShaderProgram::GetUniform(const char* uniformName)
{
    GLint uniform = glGetUniformLocation(programId, uniformName);
    //if (uniform == -1)
    //fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    return uniform;
}

void ShaderProgram::Bind()
{
    glUseProgram(programId);
}

void ShaderProgram::Unbind()
{
    glUseProgram(0);
}


ShaderProgram::Shader ShaderProgram::CreateShader(const char* shader_filename, GLenum type)
{
    check_opengl_errors("Error intercepted before create_shader()");
    std::printf("Loading file %s\n", shader_filename);
    const GLchar* source = LoadContents(shader_filename).c_str();
    if (source == nullptr)
    {
        printf("Error creating shader file: %s\n perror() ->", shader_filename);
        perror("");
        return 0;
    }
    //fprintf(stdout,"%s\n", source);
    GLuint resource = glCreateShader(type);
    check_opengl_errors("create_shader(), glCreateShader()");

    /*const GLchar* sources[] = {
        "#version 120				\n", // 1st
        (type == GL_FRAGMENT_SHADER) ?
        "#define highp				\n"
        : "							\n", // 2nd
        source
    }; // ^ 3rd*/

    glShaderSource(resource, 1, &source, 0);
    //free((void*)source); // we don't need the source anymore

    check_opengl_errors("create_shader(), glShaderSource()");

    glCompileShader(resource);

    check_opengl_errors("create_shader(), glCompileShader()");

    GLint compile_status = GL_FALSE;
    glGetShaderiv(resource, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        std::printf("Shader compilation failed!\n");
        check_opengl_errors("create_shader(), Compile failed");
        get_opengl_shader_info_log(resource);
        glDeleteShader(resource);
        return 0;
    }
    return resource;
}

