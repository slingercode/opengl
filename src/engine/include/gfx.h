#pragma once

#include "engine-definitions.h"

#include "utils.h"

EngineGFX* init_gfx();

void render_pipeline(EngineGFX* gfx);

void clean_gfx(EngineGFX* gfx);
