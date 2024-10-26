#version 330

// Update out names? in params with out prefix does not make sense
in vec3 out_color;
in vec2 out_texture_coordinate;

out vec4 fragment_color;

uniform sampler2D texture_file_1;
uniform sampler2D texture_file_2;

void main() {
    fragment_color = mix(texture(texture_file_1, out_texture_coordinate), texture(texture_file_2, out_texture_coordinate), 0.2);
    // fragment_color = mix(texture(texture_file_1, out_texture_coordinate), texture(texture_file_2, out_texture_coordinate), 0.2) * vec4(out_color, 1.0);
}
