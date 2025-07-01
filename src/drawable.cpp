#include "drawable.h"

#include <glm/gtc/matrix_transform.hpp>

namespace jade::draw {
    
    Drawable::Drawable() {
        x = y = z = 0.0f;
        m_scale_x = m_scale_y = 1.0f;
        rotation = 0.0f;
        model = glm::mat4(1.0f);
    }

    void Drawable::translate(float x, float y, float z) {
        this->x += x;
        this->y += y;
        this->z += z;
        update_model();
    }

    void Drawable::rotate(float deg) {
        rotation += deg;
        update_model();
    }

    void Drawable::scale(float xy) {
        m_scale_x *= xy;
        m_scale_y *= xy;
        update_model();
    }

    void Drawable::scale(float x, float y) {
        m_scale_x *= x;
        m_scale_y *= y;
        update_model();
    }

    void Drawable::scale_x(float factor) {
        m_scale_x *= factor;
        update_model();
    }

    void Drawable::scale_y(float factor) {
        m_scale_y *= factor;
        update_model();
    }

    void Drawable::set_position(float x, float y) {
        this->x = x;
        this->y = y;
        update_model();
    }

    void Drawable::set_position(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        update_model();
    }

    void Drawable::set_x(float x) {
        this->x = x;
        update_model();
    }

    void Drawable::set_y(float y) {
        this->y = y;
        update_model();
    }

    void Drawable::set_z(float z) {
        this->z = z;
        update_model();
    }

    void Drawable::set_scale(float scale) {
        m_scale_x = m_scale_y = scale;
        update_model();
    }

    void Drawable::set_scale_x(float m_scale_x) {
        this->m_scale_x = m_scale_x;
        update_model();
    }

    void Drawable::set_scale_y(float m_scale_y) {
        this->m_scale_y = m_scale_y;
        update_model();
    }

    void Drawable::set_rotation(float deg) {
        rotation = deg;
        update_model();
    }

    float Drawable::get_x() const {
        return x;
    }

    float Drawable::get_y() const {
        return y;
    }

    float Drawable::get_z() const {
        return z;
    }

    float Drawable::get_scale_x() const {
        return m_scale_x;
    }

    float Drawable::get_scale_y() const {
        return m_scale_y;
    }

    float Drawable::get_rotation() const {
        return rotation;
    }

    void Drawable::update_model() {
        model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(m_scale_x, m_scale_y, 1.0f));
    }
}
