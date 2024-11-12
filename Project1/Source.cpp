#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>
#include <windows.h>


int widthWindow = 1280;
int heightWindow = 720;
bool FullScreen = false;

void GameInicializate() {

}

void GameUptade() {


}
void GameDraw() {

}
void GameFinalize() {

}
void logError(const wchar_t* message) {
		MessageBox(NULL, message, L"Error", MB_OK | MB_ICONERROR);
}

void setWindowIcon(GLFWwindow* window, const char* iconPath) {

	int width, height, channels;
	stbi_uc* image = stbi_load(iconPath, // Path
							   &width,   // Image Width
							   &height,  // Image Height
							   &channels,// Image Channels
							   4);       // RGBA

	if (!image) {
		logError(L"Failed to load icon image");
		return;
	}
	GLFWimage Gameicon{};
	Gameicon.width = width;
	Gameicon.height = height;
	Gameicon.pixels = image;

	glfwSetWindowIcon(window, 1, &Gameicon); // Set Game Icon

	stbi_image_free(image);
}

void CreateNewWindow(GLFWwindow** window) {
	
	if (!glfwInit()) {
		logError(L"Failed to initialize GLFW");
		glfwTerminate();
		exit(0);
	}
	
	//Create a modern window using the last version of OpenGL (4.5)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	//Remove deprecated functions
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	//Set the OpenGL profile to core, which means that only modern OpenGL functions are available
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	
	GLFWmonitor* monitor = glfwGetPrimaryMonitor(); //Full Screen mode

	if (FullScreen)
		*window = glfwCreateWindow(widthWindow,      // Width
								   heightWindow,     // Height
								   "Ehre-s-Requiem", // Window Name
									monitor,         // Full screen
									NULL); 
	else
		*window = glfwCreateWindow(widthWindow,      // Width
			heightWindow,							 // Height
			"Ehre-s-Requiem",						 // Window Name
			NULL,								     // Full screen
			NULL);

	if (!window)
	{
		MessageBox(NULL, L"Failed to create window", L"Error", MB_OK | MB_ICONERROR);
		glfwTerminate();
		exit(0);
	}
	setWindowIcon(*window, "..\\Icon\\image.png");
}

int main()
{
	GLFWwindow* window{ nullptr };

	CreateNewWindow(&window);
	
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		logError(L"Failed to initialize GLAD");
		return -1;
	}

	GameInicializate();
	do {

		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		GameUptade();
		GameDraw();

	} while (!glfwWindowShouldClose(window));

	GameFinalize();

	

	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}