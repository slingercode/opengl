#version 330 core

layout(location = 0) in vec3 possition;

void main() {
    gl_Position = vec4(possition.x, possition.y, possition.z, 1.0);
}
