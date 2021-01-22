#pragma once

#include "glad/glad.h"


class Pyramid  {
public:
    Pyramid(const Pyramid& rhs) = delete;
    Pyramid &operator=(const Pyramid& rhs) = delete;
    void operator=(Pyramid&& rhs) = delete;
    Pyramid(Pyramid&& rhs) = delete;
    Pyramid();
    ~Pyramid();
    void draw();
private:
    GLuint diffuse_texture_; 
    GLuint vao_;
    GLuint buffer_[2];

    std::vector<GLushort> indices_ = {
            //0,2,3,3,1,0,
            0,1,3,3,2,0,
            2,4,0, 
            2,3,5, 
            3,1,6, 
            0,7,1 
        };
        
    std::vector<GLfloat> vertices_ = {
           /*0*/ -0.5f, 0.0f, -0.5f,    0.191f, 0.5f, 
           /*1*/  0.5f, 0.0f, -0.5f,    0.5f, 0.191f,
           /*2*/  -0.5f, 0.0f, 0.5f,    0.5f, 0.809f,
           /*3*/  0.5f, 0.0f, 0.5f,     0.809f, 0.5f,

        //  /*0*/ /*2*/
            0.0f, 1.0f, 0.0f,           0.0f, 1.0f,

        //  /*2*/ /*3*/
            0.0f, 1.0f, 0.0f,           1.0f, 1.0f,

        //  /*3*/ /*1*/
            0.0f, 1.0f, 0.0f,           1.0f, 0.0f,

        //  /*1*/ /*0*/
            0.0f, 1.0f, 0.0f,           0.0f, 0.0f
    };
};