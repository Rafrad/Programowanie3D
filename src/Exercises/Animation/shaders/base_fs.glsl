#version 410

in vec4 vertex_color;

layout(location=0) out vec4 vFragColor;

void main() {
    vFragColor.a = vertex_color.a;
    vFragColor.rgb = vertex_color.rgb;
}
