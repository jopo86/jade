#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace jade {
    class Shader {
    public:
        GLuint prog;

        Shader();
        Shader(const std::string& vert_src, const std::string& frag_src);

        void use();

        void set_vec3(const std::string& name, const glm::vec3& val);
        void set_vec4(const std::string& name, const glm::vec4& val);
        void set_mat4(const std::string& name, const glm::mat4& val);

        

    };
}
