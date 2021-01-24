#pragma once

#include "glad/glad.h"


class Quad  {
public:
    Quad(const Quad& rhs) = delete;
    Quad &operator=(const Quad& rhs) = delete;
    void operator=(Quad&& rhs) = delete;
    Quad(Quad&& rhs) = delete;
    Quad();
    ~Quad();
    void draw();
private:
    GLuint diffuse_texture_; 
    GLuint vao_;
    GLuint buffer_[2];

    std::vector<GLushort> indices_ = {
            //0,2,3,3,1,0,
            0,3,1,2,3,0 // Swapped order so it is visible from "above"
        };
        
    std::vector<GLfloat> vertices_ = {
           /*0*/ -1.0f, 0.0f, -1.0f,    0.0f, 0.0f,     1.0f, 0.0f,
           /*1*/  1.0f, 0.0f, -1.0f,    1.0f, 0.0f,     1.0f, 0.0f,
           /*2*/  -1.0f, 0.0f, 1.0f,    0.0f, 1.0f,     1.0f, 0.0f,
           /*3*/  1.0f, 0.0f, 1.0f,     1.0f, 1.0f,     1.0f, 0.0f
    };
};