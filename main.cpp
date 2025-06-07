//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------
#define GLM_ENABLE_EXPERIMENTAL
#include<windows.h>
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"



const unsigned int width = 800;
const unsigned int height = 800;


struct Vec3 {
	GLfloat x, y, z;
};

std::vector<Vec3> Triangle =
{
	{-0.5f, 0.0f,  0.5f},
	{-0.5f, 0.0f, -0.5f},
	{ 0.5f, 0.0f, -0.5f},
	{ 0.5f, 0.0f,  0.5f},
	{ 0.0f, 0.8f,  0.0f},
};


std::vector<Vec3> GrassFloor =
{
	{25, -10, -25},
	{-25, -10, -25},
	{25, -10, 25},
	{-25, -10, 25}
};
// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	Triangle[0].x,Triangle[0].y,Triangle[0].z,    0.83f, 0.70f, 0.44f,	0.0f, 0.0f, //Triangle
	Triangle[1].x,Triangle[1].y,Triangle[1].z,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f, //Triangle
	Triangle[2].x,Triangle[2].y,Triangle[2].z,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f, //Triangle
	Triangle[3].x,Triangle[3].y,Triangle[3].z,    0.83f, 0.70f, 0.44f,	5.0f, 0.0f, //Triangle
	Triangle[4].x,Triangle[4].y,Triangle[4].z,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f,  //Triangle



	//Grass Floor
GrassFloor[0].x, GrassFloor[0].y, GrassFloor[0].z, 0.13f, 0.55f, 0.13f, 0.0f, 0.0f,
GrassFloor[1].x, GrassFloor[1].y, GrassFloor[1].z, 0.13f, 0.55f, 0.13f, 0.0f, 0.0f,
GrassFloor[2].x, GrassFloor[2].y, GrassFloor[2].z, 0.13f, 0.55f, 0.13f, 0.0f, 0.0f,
GrassFloor[3].x, GrassFloor[3].y, GrassFloor[3].z, 0.13f, 0.55f, 0.13f, 0.0f, 0.0f,

};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4,
	6, 7, 8,
};








float LastTime = 0;

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("C:\\Users\\baldl\\source\\repos\\Physics Engine\\Physics Engine\\Organized\\Shaders\\defualt.vert", "C:\\Users\\baldl\\source\\repos\\Physics Engine\\Physics Engine\\Organized\\Shaders\\defualt.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();



	Texture brickTex("C:\\Users\\baldl\\source\\repos\\Physics Engine\\Physics Engine\\Textures\\rebirth.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	//brickTex.texUnit(shaderProgram, "tex0", 0);

	// Original code from the tutorial
	/*Texture brickTex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);*/


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));




	float lastTime = (float)glfwGetTime();



	//Gravity Calculation
	//Gravity Calculation
	//Gravity Calculation
	float Gravity = 9.80665;
	//Gravity Calculation
	//Gravity Calculation
	//Gravity Calculation




	float CurrentLocation = 0;
	float NewLocation = 0;
	float PastLocation = 0;;


	bool physics = false;;
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		if (GetKeyState('p') & 0x8000 || GetKeyState('P') & 0x8000)
		{
			if (physics)
			{
				physics = false;
				std::cout << "Physics off" << std::endl;
				Sleep(200);
			}
			else
			{
				physics = true;
				std::cout << "Physics on" << std::endl;
				Sleep(200);
			}
		}

		if (physics)
		{
			
			for (int i = 0; i < Triangle.size(); i++)
			{
				CurrentLocation = Triangle[i].y;
				NewLocation = CurrentLocation - 0.25;
				Triangle[i].y = NewLocation;
				PastLocation = CurrentLocation;
			}
		}



		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Binds texture so that is appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}