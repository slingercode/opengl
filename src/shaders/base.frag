#version 330

layout(location = 0) out vec4 frag_color;

uniform vec4 custom_color;

void main() {
    frag_color = custom_color;
}
