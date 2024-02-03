#include "OBJObject.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor for OBJObject
OBJObject::OBJObject(const char* filepath) {

	// Initialize object's transformation matrix to scale it uniformly.
	toWorld = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f));

	std::ifstream file(filepath); // Open the file containing the object's data.

	// Check if the file opened successfully.
	if (!file.is_open()) {
		std::cerr << "Error::OBJObject could not open file: " << filepath << std::endl;
		return;
	}

	std::string line;
	// Read the file line by line.
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		// Parse vertex positions.
		if (prefix == "v") {
			parseVertex(iss);
		}
		// Parse vertex normals.
		else if (prefix == "vn") {
			parseNormal(iss);
		}
	}

	file.close(); // Close the file after reading.
}

// Method to move the object by updating its cumulative translation vector.
void OBJObject::move(float x, float y, float z) {
	cumulativeTranslation += glm::vec3(x, y, z);
	updateTransform(); // Update the object's transformation matrix.
}

// Updates the transformation matrix with current translation and scale.
void OBJObject::updateTransform() {
	toWorld = glm::mat4(1.0f); // Start with the identity matrix.
	toWorld = glm::translate(toWorld, cumulativeTranslation); // Apply translation.
	toWorld = glm::scale(toWorld, cumulativeScale); // Apply scaling.
}

void OBJObject::parseVertex(std::istringstream& iss) {
	glm::vec3 vertex;
	if (!(iss >> vertex.x >> vertex.y >> vertex.z)) {
		std::cerr << "Error parsing vertex data" << std::endl;
		return; // Add return to avoid pushing corrupted data
	}
	vertices.push_back(vertex);

}

void OBJObject::parseNormal(std::istringstream& iss) {
	glm::vec3 normal;
	if (!(iss >> normal.x >> normal.y >> normal.z)) {
		std::cerr << "Error parsing normal data" << std::endl;
		return; // To avoid pushing corrupted data
	}
	normals.push_back(normal);
}

void OBJObject::draw()
{
	glMatrixMode(GL_MODELVIEW);

	// Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(&(toWorld[0][0]));

	glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f); // Rotating around the Y-axis
	glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f); // Rotating around the Y-axis

	glBegin(GL_POINTS);
	// Loop through all the vertices of this OBJ Object and render them
	for (unsigned int i = 0; i < vertices.size(); ++i) {
		if (i < normals.size()) {
			// Map the normal vectors to color
			glColor3f((normals[i].x + 1.0f) * 0.5f, (normals[i].y + 1.0f) * 0.5f, (normals[i].z + 1.0f) * 0.5f);
		}
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();

	glPopMatrix();


	// Check for OpenGL errors
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error in OBJObject::draw: " << err << std::endl;
	}
}