#pragma once

#include "engine-definitions.h"

Textures textures_init(void);

void clean_textures(Textures* textures);

void append_texture(Textures* textures, const Texture texture);

unsigned int load_texture(Texture* texture);
