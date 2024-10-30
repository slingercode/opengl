#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"

#include <math.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct EngineState {
    int width;
    int height;
    const char* title;
} EngineState;

typedef struct Texture {
    unsigned int id;
    const char* path;
    unsigned int format;
} Texture;

typedef struct Textures {
    /// An array of textures
    Texture* data;
    unsigned int length;
    unsigned int capacity;
} Textures;

typedef struct EngineGFX {
    unsigned int shader_program;
    Textures textures;
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
} EngineGFX;

typedef struct Engine {
    EngineState* state;
    GLFWwindow* window;
    EngineGFX* gfx;
} Engine;
