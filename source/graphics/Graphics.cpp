//
// Created by Martin Lyrå on 2017-12-18.
//

#include "Graphics.h"

#include "glad.h"
#include "ShaderProgram.h"

#include "maths/Matrix4.h"
#include "maths/Vector4.h"

#include "utils/Timer.h"

#include "Input.h"

#include <cstdio>
#include <GLFW/glfw3.h>

GLFWwindow* mainWindow;

GLuint vertexArrayObjectId;
GLuint vertexBufferObjectId;

int window_width, window_height;

typedef double MatType;

Matrix4<MatType> modelMatrix;
Matrix4<MatType> viewMatrix;
Matrix4<MatType> perspectiveMatrix;

Matrix4<MatType> transformMatrix;

ShaderProgram* shaderProgram;

void UpdateTransformMatrix()
{
    double ratio = double(window_width)/double(window_height);
    perspectiveMatrix = Matrix4<MatType>::Perspective(60.0f, ratio, 0.1f, 100.0f);
    viewMatrix = Matrix4<MatType>::LookAt(
            Vector4<MatType>(8,3,6,1),  // camera/eye
            Vector4<MatType>(0,0,0,1),  // target
            Vector4<MatType>(0,1,0,0)); // up
    //viewMatrix = viewMatrix.Inversed();
    modelMatrix = Matrix4<MatType>(1.0f);
    //modelMatrix.SetAsIdentity();

    /*
    std::printf("Perspective\n");
    perspectiveMatrix.PrintContents();
    std::printf("View\n");
    viewMatrix.PrintContents();
    std::printf("Model\n");
    modelMatrix.PrintContents();*/

    transformMatrix = modelMatrix * viewMatrix * perspectiveMatrix;
    //transformMatrix = perspectiveMatrix * viewMatrix * modelMatrix;

    transformMatrix.PrintContents();
}

static const Vector4<float> vertexBufferData[] =
        {
                Vector4<float>(-1.0f, -1.0f, 0.0f, 1),
                Vector4<float>(1.0f, -1.0f, 0.0f, 1),
                Vector4<float>(0.0f, 1.0f, 0.0f, 1)
        };

static const float normalBufferData[] =
        {
                1.0,0.0,0.0,
                1.0,0.0,0.0,
                1.0,0.0,0.0
        };

static const float colorBufferData[] =
        {
                1.0,1.0,1.0,
                1.0,1.0,0.0,
                0.0,1.0,0.0
        };

bool Graphics::Initialize()
{
    TIMER("GRAPHICS Init");
    if (!glfwInit()) {
        std::printf("GLFW failed to initalize. %s:%i\n", __FILE__, __LINE__);
        return false;
    }

    mainWindow = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);

    if (!mainWindow) {
        std::printf("GLFW failed to create a window. %s:%i\n", __FILE__,  __LINE__);
        return false;
    }

    glfwMakeContextCurrent(mainWindow);

    glfwSetKeyCallback(mainWindow, &Input::KeyCallback);
    glfwSetInputMode(mainWindow, GLFW_STICKY_KEYS, 1);

    if (!gladLoadGL()) {
        std::printf("Glad has failed to load OGL. %s:%i\n", __FILE__,  __LINE__);
        return false;
    }

    glfwGetWindowSize( mainWindow, &window_width, &window_height );
    glViewport( 0, 0, window_width, window_height );

    UpdateTransformMatrix();

    std::printf("Compiling shaders...\n");
    shaderProgram = new ShaderProgram("shader/mvp_v.glsl", "shader/common_f.glsl");
    std::printf("Done compiling shaders.\n");

    return true;
}

void Graphics::Release()
{
    if (mainWindow)
        glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

void Graphics::DrawFrame()
{
    TIMER("Drawing");
    glfwPollEvents();

    UpdateTransformMatrix();

    /*int len = sizeof(vertexBufferData)/sizeof(vertexBufferData[0]);
    auto* vertices = new float[len*3];

    for (int i = 0; i < len; i++)
    {
        auto tv = transformMatrix * vertexBufferData[i];
        tv = vertexBufferData[i];
        vertices[0 + i*3] = tv.x;
        vertices[1 + i*3] = tv.y;
        vertices[2 + i*3] = tv.z;
        //vertices[3 + i*4] = tv.w;
    }*/

    float vertices_[] = {
            -1.0,-1.0,0.0,
            1.0,-1.0,0.0,
            0.0,1.0,0.0
    };

    int uniformId = shaderProgram->GetUniform("transform");
    std::printf("GLError, Id fetch (%#x):, %#x\n", uniformId, glGetError());

    shaderProgram->Bind();

    glUniformMatrix4dv(uniformId, 1, GL_FALSE, &transformMatrix[0][0]);
    std::printf("GLError, Uniform set: %X\n",glGetError());

    glClearColor(0.1f,0.3f,0.1f,1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    unsigned int indices[3] = {0,1,2};

    /*
    //glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    //glNormalPointer(GL_FLOAT, 0, normalBufferData);
    glColorPointer(3, GL_FLOAT, 0, colorBufferData);
    glVertexPointer(3, GL_FLOAT, 0, vertices_);
    glVertexAttribPointerARB(0, 3, GL_FLOAT, 0,0, vertices_);

    glDrawRangeElements(GL_TRIANGLES, 0, 2, 3, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    std::printf("GLError, Pass one: %X\n",glGetError());*/

    //glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    //glNormalPointer(GL_FLOAT, 0, normalBufferData);
    //glColorPointer(3, GL_FLOAT, 0, colorBufferData);
    glVertexPointer(3, GL_FLOAT, 0, vertices_);
    //glVertexAttribPointerARB(0, 3, GL_FLOAT, 0,0, vertices_);

    //unsigned int indices[3] = {0,1,2};
    glDrawRangeElements(GL_TRIANGLES, 0, 2, 3, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_COLOR_ARRAY);

    std::printf("GLError, Pass two: %X\n",glGetError());

    glfwSwapBuffers(mainWindow);

    //shaderProgram->Unbind();

    std::printf("Done drawing!\n");
}