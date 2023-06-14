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
    sb::Window window;
    sb::Input input(&window);

    std::string title = "03_transforms";
    window.setTitle(title);

    sb::real target_fps = 60.;
    window.setRefreshRate(target_fps);

    bool fullscreen = false;
    sb::real mix_factor = 0.5;
    sb::Matrix transform = sb::Matrix::identity(4, 4);

    std::string vs_path = sb::utils::join({"assets/shaders/examples/", title, "/vertex.glsl"});
    std::string fs_path = sb::utils::join({"assets/shaders/examples/", title, "/fragment.glsl"});
    sb::Shader* shader = sb::Shader::create(vs_path, fs_path);
    assert(shader);

    sb::VAO vao({
        // position (xyz)    // normal (xyz)      // color (rgb)       // texture (st)
        -0.95, -0.95,  0.00,  0.00,  0.00,  0.00,  1.00,  0.00,  0.00,  0.00,  0.00,
         0.90, -0.95,  0.00,  0.00,  0.00,  0.00,  0.00,  1.00,  0.00,  1.00,  0.00,
        -0.95,  0.90,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.00,  0.00,  1.00,
        -0.90,  0.95,  0.00,  0.00,  0.00,  0.00,  1.00,  0.00,  0.00,  0.00,  1.00,
         0.95, -0.90,  0.00,  0.00,  0.00,  0.00,  0.00,  1.00,  0.00,  1.00,  0.00,
         0.95,  0.95,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.00,  1.00,  1.00
    }, {}, 11);

    sb::Texture texture(sb::utils::join({"assets/textures/examples/", title, "/container.jpg"}), GL_RGB);
    sb::Texture texture2(sb::utils::join({"assets/textures/examples/", title, "/awesomeface.png"}), GL_RGBA, true);

    shader->use();
    shader->setMatrix("transform", transform);
    shader->setReal("mix_factor", mix_factor);
    shader->setInt("texture_data_1", 0);
    shader->setInt("texture_data_2", 1);

    sb::utils::Timer timer;

    while (true)
    {
        sb::real delta_t_sec = timer.getFrameTime() * 1e-9;

        window.update();
        input.update();

        if (input.isKeyPressed(sb::KEY_q) || input.isKeyDown(sb::KEY_Escape))
            break;

        if (input.isKeyPressed(sb::KEY_F11))
        {
            fullscreen = !fullscreen;
            window.setFullscreen(fullscreen);
        }

        sb::real W = (sb::real)window.width();
        sb::real H = (sb::real)window.height();
        sb::real max_size = std::max(W, H);
        glOrtho(-W / max_size, +W / max_size, -H / max_size, +H / max_size, -1, +1);

        if (input.isKeyDown(sb::KEY_t))
        {
            texture.bind(0);
            texture2.bind(1);
        }
        else
        {
            texture.bind(1);
            texture2.bind(0);
        }

        if (input.isKeyDown(sb::KEY_KP_Add))
        {
            mix_factor = std::min(1.0, mix_factor + 0.5 * delta_t_sec);
            shader->setReal("mix_factor", mix_factor);
        }

        if (input.isKeyDown(sb::KEY_KP_Subtract))
        {
            mix_factor = std::max(0.0, mix_factor - 0.5 * delta_t_sec);
            shader->setReal("mix_factor", mix_factor);
        }

        sb::real value = timer.getWallTime() * 1e-9;
        transform(0, 0) = std::cos(value) * 0.5;
        transform(1, 1) = std::sin(value * 1.3) * 0.5;
        transform(0, 3) = 0.5;
        transform(1, 3) = 0.5;
        shader->setMatrix("transform", transform.t());

        vao.draw();
    }

    delete shader;

    return 0;
}