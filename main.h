#ifndef _MAIN_H_
#define _MAIN_H_
#define _CRTDBG_MAP_ALLOC

#ifdef __APPLE__
// If modern OpenGL replace gl.h with gl3.h
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // This header is required for glm::translate
#include <stdlib.h>
#include <crtdbg.h>


#endif