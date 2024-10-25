#include "utils.h"

char* read_shader_file(const char* file_path) {
    int file_descriptor = open(file_path, O_RDONLY);
    if (file_descriptor == -1) {
        return NULL;
    }

    int buffer_size = lseek(file_descriptor, 0, SEEK_END);
    if (buffer_size == -1) {
        close(file_descriptor);

        return NULL;
    }

    // Reset the file pointer to the beginning of the file
    lseek(file_descriptor, 0, SEEK_SET);

    // Buffer size plus for null-termination
    char* buffer = malloc(buffer_size + 1);
    if (buffer == NULL) {
        close(file_descriptor);

        return NULL;
    }

    int bytes_read = read(file_descriptor, buffer, buffer_size);
    if (bytes_read == -1) {
        close(file_descriptor);

        return NULL;
    }

    // null-terminate the string
    buffer[buffer_size] = '\0';

    close(file_descriptor);

    return buffer;
}
