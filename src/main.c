#define STB_IMAGE_IMPLEMENTATION

#include "engine.h"

int main(void) {
    Engine* engine = init();
    run(engine);

    return 0;
}
