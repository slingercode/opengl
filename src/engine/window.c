#include "window.h"

static bool window_created = false;

void on_escape_press(GLFWwindow* window, int key, int scancode, int action, int mods);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow* init_window(const EngineState* state) {
    if (window_created) {
        printf("Window already initialized\n");

        return NULL;
    }

    if (!glfwInit()) {
        printf("There was an error trying to initialize GLFW\n");

        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(state->width, state->height, state->title, NULL, NULL);
    if (window == NULL) {
        printf("There was an error trying to create the window\n");

        clean_window(window);

        return NULL;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, on_escape_press);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("There was an error trying to initialize GLAD\n");

        clean_window(window);

        return NULL;
    }

    const unsigned char* renderer = glGetString(GL_RENDERER);
    const unsigned char* version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported: %s\n", version);

    window_created = true;

    return window;
}

void clean_window(GLFWwindow* window) {
    if (window != NULL) {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}

void on_escape_press(GLFWwindow* window, int key, int scancode, int action, int mods) {
    /* Unused parameters */
    (void)scancode;
    (void)mods;

    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    /* Unused parameters */
    (void)window;

    glViewport(0, 0, width, height);
}
