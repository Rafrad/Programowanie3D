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
    GLuint vao_;
    GLuint buffer_[2];

    std::vector<GLushort> indices_ = {
            //0,2,3,3,1,0,
            0,1,3,3,2,0,
            4,5,6, 
            7,8,9, 
            10,11,12, 
            15,14,13 
        }; // wypisujemy tyle elementów ile mamy wierzchołków

    std::vector<GLfloat> vertices_ = {
           /*0*/ -0.5f, 0.0f, -0.5f,    0.2f, 1.0f, 0.2f, 
           /*1*/  0.5f, 0.0f, -0.5f,    0.2f, 1.0f, 0.2f, 
           /*2*/  -0.5f, 0.0f, 0.5f,    0.2f, 1.0f, 0.2f,
           /*3*/  0.5f, 0.0f, 0.5f,     0.2f, 1.0f, 0.2f, 

           /*1*/  0.5f, 0.0f, -0.5f,    0.f, 0.2f, 0.8f,
           /*0*/ -0.5f, 0.0f, -0.5f,    0.f, 0.2f, 0.8f,
            0.0f, 1.0f, 0.0f,           0.f, 0.2f, 0.8f,

           /*3*/  0.5f, 0.0f, 0.5f,     1.0f, 0.f, 0.2f,
           /*1*/  0.5f, 0.0f, -0.5f,    1.0f, 0.f, 0.2f,
            0.0f, 1.0f, 0.0f,           1.0f, 0.f, 0.2f,

           /*2*/  -0.5f, 0.0f, 0.5f,    1.0f, 1.f, 0.2f,
           /*3*/  0.5f, 0.0f, 0.5f,     1.0f, 1.f, 0.2f,
            0.0f, 1.0f, 0.0f,           1.0f, 1.f, 0.2f,

            0.0f, 1.0f, 0.0f,           0.5f, 0.5f, 0.5f,
           /*2*/  -0.5f, 0.0f, 0.5f,    0.5f, 0.5f, 0.5f,
           /*0*/ -0.5f, 0.0f, -0.5f,    0.5f, 0.5f, 0.5f,
    };
};