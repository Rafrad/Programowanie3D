//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "Application/utils.h"

void SimpleShapeApplication::init() {


    auto program = xe::create_program(std::string(PROJECT_DIR) + "/shaders/base_vs.glsl",
                                      std::string(PROJECT_DIR) + "/shaders/base_fs.glsl");


    if (!program) {
        std::cerr << "Cannot create program from " << std::string(PROJECT_DIR) + "/shaders/base_vs.glsl" << " and ";
        std::cerr << std::string(PROJECT_DIR) + "/shaders/base_fs.glsl" << " shader files" << std::endl;
    }

    std::vector<GLushort> indices = {
            //0,2,3,3,1,0,
            0,1,3,3,2,0,
            4,5,6, 
            7,8,9, 
            10,11,12, 
            15,14,13 
        }; // wypisujemy tyle elementów ile mamy wierzchołków

    std::vector<GLfloat> vertices = {
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

    auto u_modifiers_index = glGetUniformBlockIndex(program, "Modifiers"); 
    if (u_modifiers_index == GL_INVALID_INDEX) { 
        std::cout << "Cannot find Modifiers uniform block in program" << std::endl;
    } else {
        glUniformBlockBinding(program, u_modifiers_index, 1);
    }

    auto u_matrix_index = glGetUniformBlockIndex(program, "Matrix");
    if (u_matrix_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Matrix uniform block in program" << "\n";
    } else {
        glUniformBlockBinding(program, u_matrix_index, 0);
    }

    GLfloat light_intensity = 0.9f;
    GLfloat light_color[3] = { 1.0f, 1.0f, 1.0f };


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
    
    GLuint ubo_handle(0u);
    glGenBuffers(1, &ubo_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_handle);
    glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(GLfloat), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(GLfloat), &light_intensity);
    glBufferSubData(GL_UNIFORM_BUFFER, 4 * sizeof(GLfloat), 3 * sizeof(GLfloat), light_color);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, ubo_handle);


    glClearColor(0.0f, 0.81f, 0.8f, 1.0f);
    int w, h;
    std::tie(w, h) = frame_buffer_size();

    set_camera(new Camera);

    camera_->perspective(
        glm::half_pi<float>(),
        (float)w/h,
        0.1f,
        100.0f
    );
    //camera_->projection();
    camera_->look_at(
            glm::vec3(1.0f, 2.f, 0.2f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
    );
    
    set_controler(new CameraControler(camera()));

    glGenBuffers(1, &u_pvm_buffer_);
    glBindBufferBase(GL_UNIFORM_BUFFER,0,u_pvm_buffer_);

    // Buffor "wyrzucony do metody init"
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);

    glViewport(0, 0, w, h);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glUseProgram(program);
}

void SimpleShapeApplication::frame() {
    glBindVertexArray(vao_);


    auto PVM = camera_->projection()*camera_->view();
    glBindBuffer(GL_UNIFORM_BUFFER,u_pvm_buffer_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &PVM[0]);

    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, reinterpret_cast<GLvoid*>(0));
    glBindVertexArray(0);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    glViewport(0,0,w,h);
    camera_->set_aspect((float)w/h);
}

void SimpleShapeApplication::mouse_button_callback(int button, int action, int mods) {
    Application::mouse_button_callback(button, action, mods);
    if (controler_) {
        double x, y;
        glfwGetCursorPos(window_, &x, &y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            controler_->LMB_pressed((float)x, (float)y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
            controler_->LMB_released((float)x, (float)y);
    }

}

void SimpleShapeApplication::cursor_position_callback(double x, double y) {
    Application::cursor_position_callback(x, y);
    if (controler_) {
        controler_->mouse_moved(x, y);
    }
}