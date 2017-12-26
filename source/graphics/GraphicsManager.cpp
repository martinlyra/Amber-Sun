#include "GraphicsManager.h"

#include "glad.h"

#include "Input.h"
#include "maths/Matrix4.h"
#include "maths/Vector4.h"

#include <iostream>

#include <GLFW/glfw3.h>

GLFWwindow* window;

GLuint vertexArrayObjectId_;
GLuint vertexBufferObjectId_;

Matrix4<double> modelMatrix_;
Matrix4<double> viewMatrix_;
Matrix4<double> perspectiveMatrix_;

Matrix4<double> transformMatrix_;

static const Vector4<double> vertexBufferData_[] =
{
	Vector4<double>(-1.0f, -1.0f, 0.0f, 1),
	Vector4<double>(1.0f, -1.0f, 0.0f, 1),
	Vector4<double>(0.0f, 1.0f, 0.0f, 1)
};

void SubmitBufferData2()
{
	int len = sizeof(vertexBufferData_)/sizeof(vertexBufferData_[0]);
	//std::printf("Buffer data size: %u\n", len);
	
	int bufferSize = len * 3;
	GLdouble *vertexBuffer = new GLdouble[len*3];
	for (int i = 0; i < len; i++)
	{
		//auto tv = vertexBufferData[i];
		auto tv = transformMatrix_ * vertexBufferData_[i];
		vertexBuffer[i*3 + 0] = tv.x;
		vertexBuffer[i*3 + 1] = tv.y;
		vertexBuffer[i*3 + 2] = tv.z;
		
		std::printf("%f:%f:%f:%f\n", tv.x, tv.y, tv.z, tv.w);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId_);
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

    glfwSetKeyCallback(window, &Input::KeyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	
	if (!gladLoadGL())
		std::printf("Glad has failed to load OGL. %s:%i\n", __FILE__,  __LINE__);

	glGenVertexArrays( 1, &vertexArrayObjectId_ );
	glBindVertexArray( vertexArrayObjectId_ );

	glGenBuffers( 1, &vertexBufferObjectId_ );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObjectId_ );
	
	int width, height;
	glfwGetWindowSize( window, &width, &height );
	glViewport( 0, 0, width, height );

	perspectiveMatrix_ = Matrix4<double>::Perspective(60.0f, width/height, 0.1f, 100.0f);

	viewMatrix_ = Matrix4<double>::LookAt(
		Vector4<double>(8,3,3,1),  // camera/eye
		Vector4<double>(0,0,0,1),  // target
		Vector4<double>(0,1,0,0)); // up
	viewMatrix_.Inverse();

	modelMatrix_ = Matrix4<double>();
	modelMatrix_.SetAsIdentity();
	
	transformMatrix_ = modelMatrix_ * viewMatrix_ * perspectiveMatrix_;
	
	SubmitBufferData2();
}

void GraphicsManager::DrawFrame()
{
    glfwPollEvents();

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
	
	int len = sizeof(vertexBufferData_)/sizeof(vertexBufferData_[0]);
	for (int i = 0; i < len; i++)
	{
		//auto v = vertexBufferData[i];
		auto v = transformMatrix_ * vertexBufferData_[i];
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
