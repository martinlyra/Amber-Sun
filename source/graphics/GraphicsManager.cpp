#include "GraphicsManager.h"

#include "glad.h"

#include <GLFW\glfw3.h>

GLFWwindow* window;

GLuint vertexArrayObjectId;
GLuint vertexBufferObjectId;

GraphicsManager::GraphicsManager()
{
}


GraphicsManager::~GraphicsManager()
{
	if (window != nullptr)
		glfwDestroyWindow( window );
	glfwTerminate();
}

void GraphicsManager::Initialize()
{
	if (!gladLoadGL() || !glfwInit())
	{
		// something bad happened
	}

	glGenVertexArrays( 1, &vertexArrayObjectId );
	glBindVertexArray( vertexArrayObjectId );

	glGenBuffers( 1, &vertexBufferObjectId );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObjectId );
}

void GraphicsManager::DrawFrame()
{
	BeginDraw();
	Draw();
	EndDraw();
}

void GraphicsManager::BeginDraw()
{
	int width, height;
	glfwGetWindowSize( window, &width, &height );
	glViewport( 0, 0, width, height );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void GraphicsManager::Draw()
{
}

void GraphicsManager::EndDraw()
{
	glfwSwapBuffers( window );
}
