#version 410

in vec2 vertex_texture;
in vec3 vertex_normal_in_vs;
in vec3 vertex_position_in_vs; 

uniform sampler2D diffuse_map; 

layout(location=0) out vec4 vFragColor;
layout(std140) uniform Light {
    vec3 position_in_vs;
    vec3 color;
    vec3 a; 
} light;

void main() {
    vFragColor = texture(diffuse_map, vertex_texture); 
}
