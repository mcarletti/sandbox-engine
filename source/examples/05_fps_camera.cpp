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

    struct CameraFPS
    {
        void moveForward(sb::real dt) { position += front * dt * speed; }
        void moveBackward(sb::real dt) { position -= front * dt * speed; }
        void moveLeft(sb::real dt) { position -= right * dt * speed; }
        void moveRight(sb::real dt) { position += right * dt * speed; }

        // TODO
        void roll(sb::real angle) { return; }
        void pitch(sb::real angle) { return; }
        void yaw(sb::real angle) { return; }

        sb::Vector3 position = {0., 0., 3.};
        sb::Vector3 front = {0., 0., -1.};
        sb::Vector3 up = {0., 1., 0.};
        sb::Vector3 right = {1., 0., 0.};
        sb::real speed = 5.;
    };

    CameraFPS camera;

    while (true)
    {
        sb::real delta_t = timer.getFrameTime() * 1e-9;

        window.update();
        input.update();

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

        sb::real W = (sb::real)window.width();
        sb::real H = (sb::real)window.height();
        sb::real aspect_ratio = W / H;

        sb::Matrix4 projection = sb::perspective(45. * sb::DEG2RAD, aspect_ratio, 0.1, 100.);
        shader->setMatrix("projection", projection);

        sb::Matrix4 view;
        view = sb::lookAt(camera.position, camera.position + camera.front, camera.up);
        shader->setMatrix("view", view);

        sb::Matrix4 model;
        model = sb::rotate(model, timer.getWallTime() * 1e-9, {.5, 1., 0.});
        shader->setMatrix("model", model);

        vao.draw();
    }

    delete shader;

    return 0;
}