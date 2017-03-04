#include "GraphicsManager.h"

#include "glad.h"

#include "maths/Matrix4.h"
#include "maths/Vector4.h"

#include <iostream>

#include <GLFW/glfw3.h>

GLFWwindow* window;

GLuint vertexArrayObjectId;
GLuint vertexBufferObjectId;

Matrix4<double> modelMatrix; 
Matrix4<double> viewMatrix;
Matrix4<double> perspectiveMatrix;

Matrix4<double> transformMatrix;

static const Vector4<double> vertexBufferData[] =
{
	Vector4<double>(-1.0f, -1.0f, 0.0f, 1),
	Vector4<double>(1.0f, -1.0f, 0.0f, 1),
	Vector4<double>(0.0f, 1.0f, 0.0f, 1)
};

void SubmitBufferData()
{
	int len = sizeof(vertexBufferData)/sizeof(vertexBufferData[0]);
	//std::printf("Buffer data size: %u\n", len);
	
	int bufferSize = len * 3;
	GLdouble *vertexBuffer = new GLdouble[len*3];
	for (int i = 0; i < len; i++)
	{
		//auto tv = vertexBufferData[i];
		auto tv = transformMatrix * vertexBufferData[i];
		vertexBuffer[i*3 + 0] = tv.x;
		vertexBuffer[i*3 + 1] = tv.y;
		vertexBuffer[i*3 + 2] = tv.z;
		
		//std::printf("%f:%f:%f:%f\n", tv.x, tv.y, tv.z, tv.w);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, vertexBuffer, GL_STATIC_DRAW);
};

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
	if (!glfwInit())
		std::printf("GLFW failed to initalize. %s:%i\n", __FILE__,  __LINE__);
	
	window = glfwCreateWindow(1024, 768, "Test", nullptr, nullptr);
	
	if (!window)
		std::printf("GLFW failed to create a window. %s:%i\n", __FILE__,  __LINE__);
	
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGL())
		std::printf("Glad has failed to load OGL. %s:%i\n", __FILE__,  __LINE__);

	glGenVertexArrays( 1, &vertexArrayObjectId );
	glBindVertexArray( vertexArrayObjectId );

	glGenBuffers( 1, &vertexBufferObjectId );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObjectId );
	
	int width, height;
	glfwGetWindowSize( window, &width, &height );
	glViewport( 0, 0, width, height );

	perspectiveMatrix = Matrix4<double>::Perspective(60.0f, width/height, 0.1f, 100.0f);
	viewMatrix = Matrix4<double>::LookAt(
		Vector4<double>(4,0,3,1),
		Vector4<double>(0,0,0,1), 
		Vector4<double>(0,1,0,0));
	modelMatrix = Matrix4<double>();
	modelMatrix.SetAsIdentity();
	
	transformMatrix = modelMatrix * viewMatrix * perspectiveMatrix;
	
	SubmitBufferData();
}

void GraphicsManager::DrawFrame()
{
	BeginDraw();
	Draw();
	EndDraw();
}

void GraphicsManager::BeginDraw()
{
	glClearColor(0.1f,0.3f,0.1f,1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void GraphicsManager::Draw()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	
	glBegin(GL_TRIANGLES);
	
	int len = sizeof(vertexBufferData)/sizeof(vertexBufferData[0]);
	for (int i = 0; i < len; i++)
	{
		//auto v = vertexBufferData[i];
		auto v = transformMatrix * vertexBufferData[i];
		glVertex4d(v.x, v.y, v.z, v.w);
	}
	
	glEnd();
	
	/*
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
	glVertexAttribPointer(
	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	3,                  // size
	GL_FLOAT,           // type
	GL_FALSE,           // normalized?
	0,                  // stride
	(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
	*/
}

void GraphicsManager::EndDraw()
{
	glfwSwapBuffers( window );
}
