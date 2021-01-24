#include <vector>
#include <string>
#include <iostream>
#include "3rdParty/src/stb/stb_image.h"
#include "quad.h"
#include "glad/glad.h"


Quad::Quad() {
    int width, height, n_channels;
    uint8_t  *data = stbi_load((std::string(PROJECT_DIR) + "/Textures/silver.png").c_str(), &width, &height, &n_channels, 0);
    if(data == NULL) std::cout << "Failed to load texture" << std::endl;
    
    glGenTextures(1, &diffuse_texture_);
    glBindTexture(GL_TEXTURE_2D, diffuse_texture_);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, width, height,0, GL_RGBA, GL_UNSIGNED_BYTE,data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint idx_buffer_handle;
    glGenBuffers(1,&idx_buffer_handle); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buffer_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLushort), indices_.data(), 
                        GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint v_buffer_handle;
    glGenBuffers(1, &v_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(GLfloat), vertices_.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(5*sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}  

Quad::~Quad() {
    glDeleteBuffers(1, &vao_);
    glDeleteBuffers(2, buffer_);
} 
 
void Quad::draw() {
    glActiveTexture(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,diffuse_texture_); 
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_SHORT, reinterpret_cast<GLvoid*>(0));

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}  