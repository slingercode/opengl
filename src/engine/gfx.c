#include "gfx.h"

#define MSG_BUFFER 500
#define VERTEX_SHADER_PATH "../src/shaders/base.vert"
#define FRAGMENT_SHADER_PATH "../src/shaders/base.frag"

unsigned int compile_shader(const char* shader_filepath, GLenum shader_type);

unsigned int shader_init(const char* vertex_shader_filepath, const char* fragment_shader_filepath);

EngineGFX* init_gfx() {
    EngineGFX* gfx = (EngineGFX*) malloc(sizeof(EngineGFX));
    if (gfx == NULL) {
        printf("There was an error trying to initialize the graphics card\n");

        return NULL;
    }

    // Temporal value, the shaders files should be provided to this step
    gfx->shader_program = shader_init(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

    // Temporal value, this should be provided to this step
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    glGenVertexArrays(1, &gfx->vao);
    glGenBuffers(1, &gfx->vbo);
    glBindVertexArray(gfx->vao);

    glBindBuffer(GL_ARRAY_BUFFER, gfx->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);   

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    return gfx;
}

void render_pipeline(EngineGFX* gfx) {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(gfx->shader_program);
    glBindVertexArray(gfx->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void clean_gfx(EngineGFX* gfx) {
    if (gfx == NULL) return;

    glDeleteVertexArrays(1, &gfx->vao);
    glDeleteBuffers(1, &gfx->vbo);
    glDeleteProgram(gfx->shader_program);

    free(gfx);
}

unsigned int compile_shader(const char* shader_filepath, GLenum shader_type) {
    int success_compiling_shader;
    char infoLog[MSG_BUFFER];

    char* shader_source_buffer = read_shader_file(shader_filepath);
    if (shader_source_buffer == NULL) {
        printf("There was an error reading the shader code\n");

        return 0;
    }

    const char* shader_source = shader_source_buffer;

    unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);

    free(shader_source_buffer);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success_compiling_shader);
    if (!success_compiling_shader) {
        glGetShaderInfoLog(shader, MSG_BUFFER, NULL, infoLog);

        printf("\nSHADER COMPILE %s\n", infoLog);
        printf("Error code: %d\n", shader_type);
        printf("Path: %s\n\n", shader_filepath);

        return 0;
    }

    return shader;
}

unsigned int shader_init(const char* vertex_shader_filepath, const char* fragment_shader_filepath) {
    unsigned int vertex_shader = compile_shader(vertex_shader_filepath, GL_VERTEX_SHADER);
    if (vertex_shader == 0) {
        return vertex_shader;
    }

    unsigned int fragment_shader = compile_shader(fragment_shader_filepath, GL_FRAGMENT_SHADER);
    if (fragment_shader == 0) {
        return fragment_shader;
    }

    int success;
    char infoLog[MSG_BUFFER];

    unsigned int shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, MSG_BUFFER, NULL, infoLog);

        printf("\nLink Program %s\n", infoLog);
        printf("Vertex %d ... Fragment %d\n", vertex_shader, fragment_shader);

        return 0;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader); 

    return shader_program;
}
