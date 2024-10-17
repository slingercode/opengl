#include "utils.h"

char* read_shader_file(const char* file_path) {
    FILE* shader_file = fopen(file_path, "r");
    if (shader_file == NULL) {
        return NULL;
    }

    fseek(shader_file, 0, SEEK_END);
    long length = ftell(shader_file);
    fseek(shader_file, 0, SEEK_SET);

    char* buffer = malloc(length + 1);
    if (buffer == NULL) {
        fclose(shader_file);

        return NULL;
    }

    fread(buffer, 1, length, shader_file);

    fclose(shader_file);

    return buffer;
}
