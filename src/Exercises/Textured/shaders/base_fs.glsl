#version 410

in vec2 vertex_texture;
uniform sampler2D diffuse_map; 

layout(location=0) out vec4 vFragColor;

void main() {
    vFragColor = texture(diffuse_map, vertex_texture); 
}
