#pragma once

#include "engine-definitions.h"

#include "textures.h"
#include "utils.h"

EngineGFX* init_gfx(void);

void clean_gfx(EngineGFX* gfx);

void render_pipeline(EngineGFX* gfx);
