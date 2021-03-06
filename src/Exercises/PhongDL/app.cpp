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

    auto u_matrix_index = glGetUniformBlockIndex(program, "Matrix");
    if (u_matrix_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Matrix uniform block in program" << "\n";
    } else {
        glUniformBlockBinding(program, u_matrix_index, 0);
    }

    auto u_light_index = glGetUniformBlockIndex(program, "Light");
    if (u_light_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Light uniform block in program" << "\n";
    } else {
        glUniformBlockBinding(program, u_light_index, 1);
    }

    set_pyramid(new Pyramid);
    set_quad(new Quad);

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

    set_light(
        glm::vec4(),
        glm::vec4(1.0f, 1.0f, 1.0f, 0.0f),
        glm::vec4(1.0f, 0.0f, 1.0f, 0.0f),
        glm::vec4(0.2f, 0.2f, 0.2f, 0.0f)
    );

    glGenBuffers(1, &u_pvm_buffer_);
    glBindBufferBase(GL_UNIFORM_BUFFER,0,u_pvm_buffer_);
    glBindBuffer(GL_UNIFORM_BUFFER,u_pvm_buffer_);
    glBufferData(GL_UNIFORM_BUFFER, 2*sizeof(glm::mat4) + sizeof(glm::mat3), nullptr, GL_STATIC_DRAW);

    glGenBuffers(1, &u_light_buffer);
    glBindBufferBase(GL_UNIFORM_BUFFER,1,u_light_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER,u_light_buffer);
    glBufferData(GL_UNIFORM_BUFFER, 4*4*sizeof(GLfloat), nullptr, GL_STATIC_DRAW);

    glViewport(0, 0, w, h);
    glEnable(GL_DEPTH_TEST);
    
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    
    glUseProgram(program);

    auto  u_diffuse_map_location = glGetUniformLocation(program,"diffuse_map");
    if(u_diffuse_map_location==-1) {
        std::cerr<<"Cannot find uniform diffuse_map\n";
    } else {
        glUniform1ui(u_diffuse_map_location,0); 
    }
}

void SimpleShapeApplication::frame() {
    //pyramid_->draw();
    quad_->draw();
    auto P = camera_->projection();
    auto VM = camera_->view();
    auto N = glm::transpose(glm::inverse(glm::mat3(VM)));
    light_.position = VM * glm::vec4 (0.0f, 1.0f, 0.0f, 1.0f);
    
    glBindBuffer(GL_UNIFORM_BUFFER,u_pvm_buffer_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0,                                         sizeof(glm::mat4),   &P[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4),                         sizeof(glm::mat4),   &VM[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(glm::mat4),                       3 * sizeof(GLfloat), &N[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(glm::mat4) + 4 * sizeof(GLfloat), 3 * sizeof(GLfloat), &N[1]);
    glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(glm::mat4) + 8 * sizeof(GLfloat), 3 * sizeof(GLfloat), &N[2]);
    glBindBuffer(GL_UNIFORM_BUFFER,0);

    glBindBuffer(GL_UNIFORM_BUFFER, u_light_buffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0,                    4 * sizeof(GLfloat), &light_.position[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 4 * sizeof(GLfloat),  4 * sizeof(GLfloat), &light_.color[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 8 * sizeof(GLfloat),  4 * sizeof(GLfloat), &light_.a[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 12 * sizeof(GLfloat), 4 * sizeof(GLfloat), &light_.ambient[0]);
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

void SimpleShapeApplication::cleanup() {
        delete pyramid_;
        delete quad_;
}