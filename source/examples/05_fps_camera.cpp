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

    std::string title = "05_fps_camera";
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
         0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,

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

         0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,

         0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
    }, {}, 11);

    sb::utils::Timer timer;

    sb::Camera camera(&window, 45., 0.1, 100.);

    while (true)
    {
        sb::real delta_t = timer.getFrameTime() * 1e-9;

        window.update();
        input.update();
        camera.update();

        if (input.isKeyPressed(sb::KEY_q) || input.isKeyDown(sb::KEY_Escape))
            break;
        if (input.isKeyDown(sb::KEY_W))
            camera.moveForward(delta_t);
        if (input.isKeyDown(sb::KEY_S))
            camera.moveBackward(delta_t);
        if (input.isKeyDown(sb::KEY_A))
            camera.moveLeft(delta_t);
        if (input.isKeyDown(sb::KEY_D))
            camera.moveRight(delta_t);
        if (input.isKeyDown(sb::KEY_Shift_L))
            camera.moveUp(delta_t);
        if (input.isKeyDown(sb::KEY_Control_L))
            camera.moveDown(delta_t);

        sb::Matrix4 projection = camera.projection();
        sb::Matrix4 view = camera.view();

        sb::Matrix4 model;
        model = sb::rotate(model, timer.getWallTime() * 1e-9, {.5, 1., 0.});

        sb::Matrix4 mvp = projection.matmul(view.matmul(model));
        shader->setMatrix("mvp", mvp);

        vao.draw();
    }

    delete shader;

    return 0;
}