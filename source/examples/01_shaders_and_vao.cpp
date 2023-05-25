#include <sandbox/sandbox.hpp>

int main(int argc, char* argv[])
{
    sb::Window window;
    sb::Input input(&window);

    std::string title = "01_shaders_and_vao";
    window.setTitle(title);

    sb::real target_fps = 30.;
    window.setRefreshRate(target_fps);

    bool fullscreen = false;
    bool use_flat_color = false;

    std::string vs_path = sb::utils::join({"assets/shaders/examples/", title, "/vertex.glsl"});
    std::string fs_path = sb::utils::join({"assets/shaders/examples/", title, "/fragment.glsl"});
    std::cout << vs_path << " " << fs_path << std::endl;
    sb::Shader* shader = sb::Shader::create(vs_path, fs_path);
    assert(shader);

    sb::VAO vao({
        // position (xyz)    // normal (xyz)      // color (rgb)
        -0.95, -0.95,  0.00,  0.00,  0.00,  0.00,  1.00,  0.00,  0.00,
         0.90, -0.95,  0.00,  0.00,  0.00,  0.00,  0.00,  1.00,  0.00,
        -0.95,  0.90,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.00,
        -0.90,  0.95,  0.00,  0.00,  0.00,  0.00,  1.00,  0.00,  0.00,
         0.95, -0.90,  0.00,  0.00,  0.00,  0.00,  0.00,  1.00,  0.00,
         0.95,  0.95,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.00,
    }, {}, 9);

    shader->use();

    while (true)
    {
        window.update();
        input.update();

        if (input.isKeyPressed(sb::KEY_q) || input.isKeyDown(sb::KEY_Escape))
            break;

        if (input.isKeyPressed(sb::KEY_f))
        {
            fullscreen = !fullscreen;
            window.setFullscreen(fullscreen);
        }

        if (input.isKeyPressed(sb::KEY_c))
        {
            use_flat_color = !use_flat_color;
            shader->setBool("use_flat_color", use_flat_color);
        }

        sb::real W = (sb::real)window.width();
        sb::real H = (sb::real)window.height();
        sb::real max_size = std::max(W, H);
        glOrtho(-W / max_size, +W / max_size, -H / max_size, +H / max_size, -1, +1);

        vao.draw();
    }

    delete shader;

    return 0;
}