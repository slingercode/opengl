#include "gfx.h"

#define MSG_BUFFER 500
#define VERTEX_SHADER_PATH "../src/shaders/base.vert"
#define FRAGMENT_SHADER_PATH "../src/shaders/base.frag"
#define TEXTURE_1_PATH "../assets/textures/texture 1.jpg"
// #define TEXTURE_2_PATH "../assets/textures/texture 2.png"
#define TEXTURE_2_PATH "../assets/textures/smile.png"

unsigned int compile_shader(const char* shader_filepath, const GLenum shader_type);

unsigned int shader_init(const char* vertex_shader_filepath, const char* fragment_shader_filepath);

unsigned int load_texture(const char* texture_filepath, const int temp);

EngineGFX* init_gfx() {
    EngineGFX* gfx = (EngineGFX*) malloc(sizeof(EngineGFX));
    if (gfx == NULL) {
        printf("There was an error trying to initialize the graphics card\n");

        return NULL;
    }

    // Temporal value, the shaders files should be provided into this step
    gfx->shader_program = shader_init(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

    // Temporal value, the texture should be provided into this step
    // temp (the second param) is important because the color channel needs to be RGB bc with alpha does not work? idunno
    // The first image is JPG so it does not have an alpha channel? idunno x2
    gfx->texture_1 = load_texture(TEXTURE_1_PATH, GL_RGB);
    gfx->texture_2 = load_texture(TEXTURE_2_PATH, GL_RGBA);

    // Temporal value...
    const float vertices[] = {
        // positions        // colors           // texture coords
        0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    // Temporal value...
    const unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glGenVertexArrays(1, &gfx->vao);
    glGenBuffers(1, &gfx->vbo);
    glGenBuffers(1, &gfx->ebo);
    glBindVertexArray(gfx->vao);

    glBindBuffer(GL_ARRAY_BUFFER, gfx->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gfx->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    const float stride = 8 * sizeof(float);

    // Vertex position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Vertex texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Load the fragment shader uniforms (make a function)
    glUseProgram(gfx->shader_program);
    glUniform1i(glGetUniformLocation(gfx->shader_program, "texture_file_1"), 0);
    glUniform1i(glGetUniformLocation(gfx->shader_program, "texture_file_2"), 1);

    return gfx;
}

void render_pipeline(EngineGFX* gfx) {
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gfx->texture_1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gfx->texture_2);

    glUseProgram(gfx->shader_program);
    glBindVertexArray(gfx->vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void clean_gfx(EngineGFX* gfx) {
    if (gfx == NULL) return;

    glDeleteVertexArrays(1, &gfx->vao);
    glDeleteBuffers(1, &gfx->vbo);
    glDeleteBuffers(1, &gfx->ebo);
    glDeleteTextures(1, &gfx->texture_1);
    glDeleteTextures(1, &gfx->texture_2);
    glDeleteProgram(gfx->shader_program);

    free(gfx);
}

unsigned int compile_shader(const char* shader_filepath, const GLenum shader_type) {
    int success_compiling_shader;
    char infoLog[MSG_BUFFER];

    char* shader_source_buffer = read_shader_file(shader_filepath);
    if (shader_source_buffer == NULL) {
        printf("There was an error reading the shader code\n");
        printf("errno read_shader_file: %d\n", errno);

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

unsigned int load_texture(const char* texture_filepath, const int temp) {
    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;

    unsigned char *data = stbi_load(texture_filepath, &width, &height, &channels, 0);
    if (data == NULL) {
        printf("There was an error trying to load the texture\n");
        printf("Texture %s\n", texture_filepath);

        return 0;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, temp, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return texture;
}
