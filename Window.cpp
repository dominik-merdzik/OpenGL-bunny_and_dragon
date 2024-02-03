#include "Window.h"
#include "OBJObject.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


const char* window_title = "Dragon & Bunny";

int Window::width;
int Window::height;

OBJObject* bunnyObject;
OBJObject* dragonObject;

float pointSize = 1.0f; // Default point size
float dragonScaleFactor = 8.5f; // Scale of Dragon
float bunnyScaleFactor = 7.5f;  // Scale of Bunny


void Window::initialize_objects() {
	bunnyObject = new OBJObject("E:/Dev/CG_Assignement_01/assets/BunnyF14.obj");
	dragonObject = new OBJObject("E:/Dev/CG_Assignement_01/assets/dragonF14.obj"); // Replace with your actual file path


	// Initial transformation for the dragon
	dragonObject->cumulativeTranslation = glm::vec3(-9.0f, -5.0f, 0.0f);
	dragonObject->cumulativeScale = glm::vec3(dragonScaleFactor, dragonScaleFactor, dragonScaleFactor);

	// Initial transformation for the bunny
	bunnyObject->cumulativeTranslation = glm::vec3(11.0f, 2.0f, 0.0f);
	bunnyObject->cumulativeScale = glm::vec3(bunnyScaleFactor, bunnyScaleFactor, bunnyScaleFactor);
	bunnyObject->updateTransform();

}

void Window::clean_up() {
	delete bunnyObject;
	delete dragonObject;
}

void Window::idle_callback() {

	float rotationSpeed = 0.23f;
	dragonObject->rotationAngleY += rotationSpeed;
	bunnyObject->rotationAngleX += rotationSpeed;

	bunnyObject->updateTransform();
	dragonObject->updateTransform();

}


void Window::display_callback(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Set the matrix mode to GL_MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	// Load the identity matrix
	glLoadIdentity();

	glPointSize(pointSize);

	// Drawing objects
	bunnyObject->draw();
	dragonObject->draw();

	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}


GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing - 16x because 1070
	glfwWindowHint(GLFW_SAMPLES, 16);

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size
	glViewport(0, 0, width, height);
	// Set the matrix mode to GL_PROJECTION to determine the proper camera properties
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the perspective of the projection viewing frustum
	gluPerspective(45.0, double(width) / (double)height, 0.1, 1000.0);
	// Move camera back 20 units so that it looks at the origin (or else it's in the origin)
	glTranslatef(0, 0, -50); // Adjust the Z value as needed to fit the object

}


void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	float movementStep = 0.5f;
	float scaleStep = 0.2f;
	float zMovementStep = 0.5f;
	bool shiftPressed = (mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT;

	// Check for a key press
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_P:
			// Scale up the size of each point
			if (!shiftPressed) {
				pointSize = glm::max(1.0f, pointSize + 2.0f);
				glPointSize(pointSize);
			}
			break;
		case GLFW_KEY_A:
			// Move left
			if (!shiftPressed) {
				bunnyObject->move(-movementStep, 0.0f, 0.0f);
				dragonObject->move(-movementStep, 0.0f, 0.0f);
			}
			break;
		case GLFW_KEY_D:
			// Move right
			if (!shiftPressed) {
				bunnyObject->move(movementStep, 0.0f, 0.0f);
				dragonObject->move(movementStep, 0.0f, 0.0f);
			}
			break;
		case GLFW_KEY_W:
			// Move up
			if (!shiftPressed) {
				bunnyObject->move(0.0f, movementStep, 0.0f);
				dragonObject->move(0.0f, movementStep, 0.0f);
			}
			break;
		case GLFW_KEY_S:
			// Move down
			if (!shiftPressed) {
				bunnyObject->move(0.0f, -movementStep, 0.0f);
				dragonObject->move(0.0f, -movementStep, 0.0f);
			}
			break;
		case GLFW_KEY_Z:
			if (!shiftPressed) {
				// Moving along Z-axis
				bunnyObject->move(0.0f, 0.0f, -zMovementStep);
				dragonObject->move(0.0f, 0.0f, -zMovementStep);
			}
			break;
		case GLFW_KEY_C:
			if (!shiftPressed) {
				// Scaling objects
				bunnyObject->cumulativeScale -= glm::vec3(scaleStep, scaleStep, scaleStep);
				dragonObject->cumulativeScale -= glm::vec3(scaleStep, scaleStep, scaleStep);
			}
			break;
		case GLFW_KEY_R:

			if (!shiftPressed) {
				bunnyObject->cumulativeTranslation = glm::vec3(11.0f, 2.0f, 0.0f); // Original starting position
				dragonObject->cumulativeTranslation = glm::vec3(-9.0f, -5.0f, 0.0f); // Original starting position

				bunnyObject->updateTransform();
				dragonObject->updateTransform();
				break;
			}
			else {
				// Reset objects to thier initial scale and orientation
				dragonObject->cumulativeScale = glm::vec3(dragonScaleFactor, dragonScaleFactor, dragonScaleFactor);
				dragonObject->cumulativeRotation = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				dragonObject->updateTransform();

				bunnyObject->cumulativeScale = glm::vec3(bunnyScaleFactor, bunnyScaleFactor, bunnyScaleFactor);
				bunnyObject->cumulativeRotation = glm::mat4(1.0f);
				bunnyObject->updateTransform();
			}
			break;

		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		}
	}
}
