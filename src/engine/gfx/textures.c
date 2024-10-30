#include "textures.h"

#define INITIAL_TEXTURES 5

Textures textures_init(void) {
    Texture* data = (Texture*)malloc(INITIAL_TEXTURES * sizeof(Texture));
    if (data == NULL) {
        printf("There was an error allocating memory for the textures");
    }

    Textures textures = {
        .length = 0,
        .capacity = INITIAL_TEXTURES,
        .data = data
    };

    return textures;
}

void clean_textures(Textures* textures) {
    free(textures->data);
}

void append_texture(Textures* textures, const Texture texture) {
    if (textures->length >= textures->capacity) {
        textures->capacity *= 2;
        textures->data = (Texture*)realloc(textures->data, textures->capacity * sizeof(Texture));
        if (textures->data == NULL) {
            printf("There was an error reallocating the textures data");

            return;
        }
    }

    textures->data[textures->length] = texture;
    textures->length++;
}

unsigned int load_texture(Texture* texture) {
    unsigned int texture_id;

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;

    unsigned char *data = stbi_load(texture->path, &width, &height, &channels, 0);
    if (data == NULL) {
        printf("There was an error trying to load the texture\n");
        printf("Texture %s\n", texture->path);

        return 0;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, texture->format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    texture->id = texture_id;

    return texture_id;
}
