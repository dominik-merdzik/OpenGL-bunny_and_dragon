#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


class OBJObject {
private:
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4 toWorld;

	void parseVertex(std::istringstream& iss);
	void parseNormal(std::istringstream& iss);


public:
	float rotationAngleY = 0.0;
	float rotationAngleX = 0.0;

	OBJObject(const char* filepath);

	void move(float x, float y, float z);
	void updateTransform();

	glm::vec3 cumulativeTranslation;
	glm::vec3 cumulativeScale;
	glm::mat4 cumulativeRotation;

	void draw();
	void setToWorldMatrix(const glm::mat4& mat) {
		toWorld = mat;
	}

};

#endif
