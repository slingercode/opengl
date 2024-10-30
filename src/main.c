#define STB_IMAGE_IMPLEMENTATION

#include "engine.h"

int main(void) {
    Engine* engine = init();
    if (engine == NULL) {
        return 0;
    }

    run(engine);

    return 0;
}
