//
// Created by pbialas on 05.08.2020.
//


#pragma once

#include <vector>
#include <memory>

#include "Application/application.h"
#include "Application/utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include "glad/glad.h"
#include "camera_controler.h"
#include "pyramid.h"
#include "quad.h"

struct Light {
    glm::vec4 position;
    glm::vec4 color; 
    glm::vec4 a;  
};

class SimpleShapeApplication : public xe::Application {
public:
    SimpleShapeApplication(int width, int height, std::string title, int major = 4, int minor = 1) :
            Application(width, height, title, major, minor) {}

    void init() override;

    void cleanup() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;

    void mouse_button_callback(int button, int action, int mods) override;

    void cursor_position_callback(double x, double y) override;

    void set_camera(Camera *camera) { camera_ = camera; }

    void scroll_callback(double xoffset, double yoffset) override {
        Application::scroll_callback(xoffset, yoffset);   
        camera()->zoom(yoffset / 30.0f);
     }

    Camera *camera() { return camera_; }
    
    ~SimpleShapeApplication() {
        if (camera_) {
            delete camera_;
        }
    }
    
    void set_controler(CameraControler *controler) { controler_ = controler; }
    CameraControler *camera_controler() { return controler_; }

    void set_pyramid(Pyramid* pyramid) { pyramid_ = pyramid; }
    Pyramid* pyramid() { return pyramid_; }

    void set_quad(Quad* quad) { quad_ = quad; }
    Quad* quad() { return quad_; }

    void set_light(glm::vec4 position, glm::vec4 color, glm::vec4 a) { light_.position = position; light_.color = color; light_.a = a; }
private:
    GLuint vao_;
    GLuint u_pvm_buffer_;
    GLuint u_light_buffer;

    Light light_;

    Pyramid* pyramid_;
    Quad* quad_;
    Camera *camera_;
    CameraControler *controler_;
};