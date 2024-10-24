#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct EngineState {
    int width;
    int height;
    const char* title;
} EngineState;

typedef struct EngineGFX {
    unsigned int shader_program;
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
} EngineGFX;

typedef struct Engine {
    EngineState* state;
    GLFWwindow* window;
    EngineGFX* gfx;
} Engine;
