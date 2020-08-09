#include "chapter2.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <glad/glad.h>
#include <glfw3.h>
#include "shader_manager.h"
#include "stb_image.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "tools.h"
#include <sstream>
#include <fstream>
#include "stb_image_write.h";
#include <vector>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



// settings



void	chapter2::run() {
	unsigned int SCR_WIDTH = 800;
	unsigned int SCR_HEIGHT = 600;
	unsigned int Tscale = 10;
	std::string name;
	
	// camera
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	std::cout << "Give the width of Camera Resolution:" << "\n";
	//int iu;
	std::cin >> SCR_WIDTH;

	std::cout << "Give the height of Camera Resolution:" << "\n";
	//int iu;
	std::cin >> SCR_HEIGHT;

	std::cout << "Give the scale of Texture Resolution: (choose 0 to 10)" << "\n";
	//int iu;
	std::cin >> Tscale;

	std::cout << "Give the name for saving image" << "\n";
	//int iu;
	std::cin >> name;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif


	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL_Assignment", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		//return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("Shader.vert", "cShader.frag"); // you can name your shader files however you like

	float vertices[] = {
		 1.f,  1.f, 1.0f, 0.0f, 0.0f, //top right
		 1.f, -1.0f,0.0f, 1.0f, 0.0f, //bottom right
		 -1.0f,  -1.f,0.0f, 1.0f, 0.0f, //bottom left
		 -1.0f,  1.f,1.0f, 0.0f, 0.0f //top left




	};


	unsigned int ind[] = { 0,1,3,1,2,3 };
	unsigned int EBO;


	glCullFace(GL_FALSE);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);


	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height, channel;

	unsigned char* data = stbi_load("container.jpg", &width, &height, &channel, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	}
	else {
		std::cout << "couldn't load texture" << "\n";
	}

	stbi_image_free(data);
	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture"), 0);
	ourShader.setFloat("res", Tscale / 10.f);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	float fov = 45.0f;

	glm::mat4 proj = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 100.f);
	Tool tol = Tool();
	proj = tol.getMat("Data/projMatrix.txt");
	//tol.saveMat("Data/projMatrix.txt", proj, false);
	//proj = tol.getMat("Data/mat.txt");
	//tol.init("Data/cameraMatrix.txt");
	int frame = 0;

	std::vector<glm::mat4> mats;
	mats = tol.getMatrix("Data/cameraMatrix.txt");
	
	int itime=0;

	float ins = 0.0;
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----

		// --------------------

		processInput(window);


		glLineWidth(22.0f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		//cameraPos.z = 2;




		ourShader.setMat4("projection", proj);

		// camera/view transformation
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos - cameraFront, cameraUp);
		view = glm::rotate(view, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0f));
		
			view = mats.at((int)floor(ins)%8);
		
		
		ourShader.setMat4("view", view);
		
		std::string inn = std::to_string((int)floor(ins) % 8);
		
		//ourShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		int indd = (int)floor(ins) % 8;
		if (itime == indd) {
			if (ins < 9.0) {
				saveScreenshotToFile("Data/" + name + inn + ".bmp", SCR_WIDTH, SCR_HEIGHT);
			}
			itime++;
		}

		ins += 0.05;
		frame += 1;
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

}
void chapter2::saveScreenshotToFile(std::string filename,  int windowWidth, int windowHeight) {
	const int numberOfPixels = windowWidth  * windowHeight * 3;
	unsigned char *pixels = new unsigned char[numberOfPixels];

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels);

 	stbi_write_bmp(filename.c_str(), windowWidth, windowHeight, 3, pixels);
	 
	
}












