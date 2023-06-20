#include <sandbox/sandbox.hpp>
#include <sandbox/graphics/Texture.hpp>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

sb::Matrix4 glm2sb(const glm::mat4& mat)
{
    std::vector<sb::real> vdata(glm::value_ptr(mat), glm::value_ptr(mat)+16);
    return sb::Matrix4(vdata).t();
}

glm::mat4 sb2glm(const sb::Matrix4& mat)
{
    return glm::make_mat4(mat.t().data());
}

#ifdef __Debug
#define PRINT(msg) {std::cout << msg << std::endl;}
#else
#define PRINT(msg) {}
#endif

int main(int argc, char* argv[])
{
    sb::utils::Logger::setSignalHandler(11);

    sb::Window window;
    sb::Input input(&window);

    std::string title = "04_model_view_projection";
    sb::real target_fps = 60.;

    window.setTitle(title);
    window.setRefreshRate(target_fps);

    std::string vs_path = sb::utils::join({"assets/shaders/examples/", title, "/vertex.glsl"});
    std::string fs_path = sb::utils::join({"assets/shaders/examples/", title, "/fragment.glsl"});
    sb::Shader* shader = sb::Shader::create(vs_path, fs_path);
    assert(shader);
    shader->use();

    sb::Texture texture(sb::utils::join({"assets/textures/examples/", title, "/container.jpg"}), GL_RGB);
    shader->setInt("texture_data", 0);
    texture.bind(0);

    sb::VAO vao({
        // position (xyz)     // normal (xyz)      // color (rgb)       // texture (st)
        -0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f
    }, {}, 11);

    sb::utils::Timer timer;

    while (true)
    {
        window.update();
        input.update();

        if (input.isKeyPressed(sb::KEY_q) || input.isKeyDown(sb::KEY_Escape))
            break;

        sb::real W = (sb::real)window.width();
        sb::real H = (sb::real)window.height();
        sb::real aspect_ratio = W / H;

        sb::Matrix4 projection = sb::perspective(45.f * sb::DEG2RAD, aspect_ratio, 0.1f, 100.f);
        shader->setMatrix("projection", projection);

        sb::Matrix4 view;
        view.translate({0.f, 0.f, -3.f});
        shader->setMatrix("view", view);

        sb::Matrix4 model;
        model = sb::rotate(model, timer.getWallTime() * 1e-9, {1.f, 1.f, 0.f});
        shader->setMatrix("model", model);

        vao.draw();
    }

    delete shader;

    return 0;
}