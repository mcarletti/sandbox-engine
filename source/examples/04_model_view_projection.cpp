#include <sandbox/sandbox.hpp>
#include <sandbox/graphics/Texture.hpp>
#include <cmath>

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
        -1.00, -1.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,
         1.00, -1.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.00,  0.00,
        -1.00,  1.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.00,
        -1.00,  1.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.00,
         1.00, -1.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.00,  0.00,
         1.00,  1.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.00,  1.00
    }, {}, 11);

    sb::utils::Timer timer;

    while (true)
    {
        sb::real delta_t_sec = timer.getFrameTime() * 1e-9;

        window.update();
        input.update();

        if (input.isKeyPressed(sb::KEY_q) || input.isKeyDown(sb::KEY_Escape))
            break;

        sb::real W = (sb::real)window.width();
        sb::real H = (sb::real)window.height();
        sb::real aspect_ratio = W / H;

        sb::Matrix4 projection = sb::perspective(45.f * sb::DEG2RAD, aspect_ratio, 0.1f, 100.f);
        shader->setMatrix("projection", projection.t());

        sb::Matrix4 view;
        view.translate({0.f, 0.f, -3.f});
        shader->setMatrix("view", view.t());

        sb::Matrix4 transform;
        transform = sb::rotate(transform, -55.f * sb::DEG2RAD, {1.f, 0.f, 0.f});
        shader->setMatrix("model", transform.t());

        vao.draw();

        std::cout << "projection\n" << projection.toString() << std::endl;
        std::cout << "view\n" << view.toString() << std::endl;
        std::cout << "model\n" << transform.toString() << std::endl;
        std::cout << "MVP\n" << (projection * view * transform).toString() << std::endl;
    }

    delete shader;

    return 0;
}