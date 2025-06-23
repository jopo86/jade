#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

jade::Camera::Camera() 
    : pos(glm::vec3(0.0f, 0.0f, 0.0f)), front(pos), up(pos), roll(0.0f), view(glm::mat4(1.0f)), proj(view) {}

jade::Camera::Camera(float width, float height) {
    pos = glm::vec3(0.0f, 0.0f, 0.1f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    view = glm::lookAt(pos, pos + front, up);
    proj = glm::ortho(0.0f, width, 0.0f, height);
}

void jade::Camera::rotate(float deg) {
    roll += glm::radians(deg);
    up = glm::vec3(glm::cos(roll + glm::half_pi<float>()), glm::sin(roll + glm::half_pi<float>()), 0.0f);
    view = glm::lookAt(pos, pos + front, up);
}

void jade::Camera::translate(float x, float y) {
    pos += glm::vec3(x, y, 0.0f);
    view = glm::lookAt(pos, pos + front, up);
}

void jade::Camera::resize(float width, float height) {
    proj = glm::ortho(0.0f, width, 0.0f, height);
}
