//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>


#include "Application/utils.h"

void SimpleShapeApplication::init() {


    auto program = xe::create_program(std::string(PROJECT_DIR) + "/shaders/base_vs.glsl",
                                      std::string(PROJECT_DIR) + "/shaders/base_fs.glsl");


    if (!program) {
        std::cerr << "Cannot create program from " << std::string(PROJECT_DIR) + "/shaders/base_vs.glsl" << " and ";
        std::cerr << std::string(PROJECT_DIR) + "/shaders/base_fs.glsl" << " shader files" << std::endl;
    }

    std::vector<GLushort> indices = {
            0,2,1,6,5,4,3 // wypisujemy tyle elementów ile mamy wierzchołków
        };

    std::vector<GLfloat> vertices = {
            -0.7f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f,
            0.7f, 0.0f, 0.0f, 1.0f, 0.6f, 0.2f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.4f, 0.0f,
            -0.5f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            -0.5f, 0.0f, 0.0f, 0.4f, 0.4f, 0.0f,
            0.5f, 0.0f, 0.0f, 0.6f, 0.6f, 0.0f,
    };

    GLuint idx_buffer_handle;
    glGenBuffers(1,&idx_buffer_handle); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buffer_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), 
                        GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint v_buffer_handle;
    glGenBuffers(1, &v_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));
    glEnableVertexAttribArray(0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3*sizeof(GLfloat)));
    glBindVertexArray(0);

    glClearColor(0.0f, 0.81f, 0.8f, 1.0f);
    int w, h;
    std::tie(w, h) = frame_buffer_size();
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glUseProgram(program);
}

void SimpleShapeApplication::frame() {
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLE_STRIP, 7, GL_UNSIGNED_SHORT, nullptr);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawArrays(GL_TRIANGLE_STRIP, 3, 4);
    glBindVertexArray(0);
}
