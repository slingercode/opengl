#include "engine.h"

// Change this to enum?
static bool instance_created = false;

void clean(Engine* engine);

Engine* init() {
    if (instance_created) {
        printf("Engine already initialized\n");

        return NULL;
    }

    Engine* engine = (Engine*) malloc(sizeof(Engine));
    if (engine == NULL) {
        printf("There was an error trying to initialize the engine\n");

        return NULL;
    }

    EngineState* state = (EngineState*) malloc(sizeof(EngineState));
    if (state == NULL) {
        printf("There was an error trying to initialize the engine state\n");

        return NULL;
    }

    engine->state = state;

    state->width = 800;
    state->height = 600;
    state->title = "OpenGL";

    engine->window = init_window(engine->state);

    // Maybe this is not the right place to initialize this?
    engine->gfx = init_gfx();

    instance_created = true;

    return engine;
}

void run(Engine* engine) {
    while (!glfwWindowShouldClose(engine->window)) {
        // Input

        // Rendering
        render_pipeline(engine->gfx);

        // Call events and swap the buffers
        glfwSwapBuffers(engine->window);
        glfwPollEvents();
    }

    clean(engine);

    instance_created = false;
}

void clean(Engine* engine) {
    if (engine == NULL) return;

    if (engine->window != NULL) {
        clean_window(engine->window);
    }

    if (engine->gfx != NULL) {
        clean_gfx(engine->gfx);
    }

    if (engine->state != NULL) {
        free(engine->state);
    }

    free(engine);
}

