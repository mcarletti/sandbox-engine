#include <sandbox/sandbox.hpp>
#include <sandbox/graphics/Texture.hpp>
#include <cmath>

using namespace std;
using namespace sb;

#ifdef __Debug
#define PRINT(msg) {cout << msg << endl;}
#else
#define PRINT(msg) {}
#endif

int main(int argc, char* argv[])
{
    utils::Logger::setSignalHandler(11);

    sb::Window window;
    Input input(&window);
    input.setMousePosition(1024, 1024);

    string title = "05_fps_camera";
    real target_fps = 60.;

    window.setTitle(title);
    window.setRefreshRate(target_fps);

    string vs_path = utils::join({"assets/shaders/examples/", title, "/vertex.glsl"});
    string fs_path = utils::join({"assets/shaders/examples/", title, "/fragment.glsl"});
    Shader* shader = Shader::create(vs_path, fs_path);
    assert(shader);
    shader->use();

    Texture texture1(utils::join({"assets/textures/examples/", title, "/container.jpg"}), GL_RGB);
    Texture texture2(utils::join({"assets/textures/examples/", title, "/wood.png"}), GL_RGB);
    shader->setInt("texture_data", 0);

    VAO cube({
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

    VAO plane({
        // position (xyz)     // normal (xyz)      // color (rgb)       // texture (st)
        -0.5f,  0.0f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
        -0.5f,  0.0f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 0.0f,
         0.5f,  0.0f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,
        -0.5f,  0.0f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  1.0f, 1.0f,
         0.5f,  0.0f,  0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 0.0f,
         0.5f,  0.0f, -0.5f,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.0f, 1.0f,
    }, {}, 11);

    utils::Timer timer;

    Camera camera(&window, 45., 0.1, 100.);
    real base_speed = camera.speed();

    while (true)
    {
        real delta_t = timer.getFrameTime() * 1e-9;

        window.update();
        input.update();
        camera.update();

        if (input.isKeyPressed(KEY_q) || input.isKeyDown(KEY_Escape))
            break;

        real speed = input.isMouseButtonDown(MOUSE_Button1) ? base_speed * 2. : base_speed;
        camera.setSpeed(speed);

        if (input.isKeyDown(KEY_W))
            camera.moveForward(delta_t);
        if (input.isKeyDown(KEY_S))
            camera.moveBackward(delta_t);
        if (input.isKeyDown(KEY_A))
            camera.moveLeft(delta_t);
        if (input.isKeyDown(KEY_D))
            camera.moveRight(delta_t);
        if (input.isKeyDown(KEY_Shift_L))
            camera.moveUp(delta_t);
        if (input.isKeyDown(KEY_Control_L))
            camera.moveDown(delta_t);

        int mouse_x = 0, mouse_y = 0;
        input.mousePosition(mouse_x, mouse_y);
        input.setMousePosition(1024, 1024);
        real dx = (mouse_x - 1024);
        real dy = (mouse_y - 1024);

        if (dx != 0 || dy != 0)
            camera.rotateView(delta_t, dx, dy);

        if (input.isKeyDown(KEY_U))
            camera.roll(delta_t);
        if (input.isKeyDown(KEY_O))
            camera.roll(-delta_t);
        if (input.isKeyDown(KEY_I))
            camera.pitch(-delta_t);
        if (input.isKeyDown(KEY_K))
            camera.pitch(delta_t);
        if (input.isKeyDown(KEY_J))
            camera.yaw(-delta_t);
        if (input.isKeyDown(KEY_L))
            camera.yaw(delta_t);

        mat4 projection = camera.projection();
        mat4 view = camera.view();
        mat4 projection_view_mtx = projection.matmul(view);

        {
            mat4 model;
            model = rotate(model, timer.getWallTime() * 1e-9, {.5, 1., 0.});
            model.translate({0., 2., 0.});
            shader->setMatrix("mvp", projection_view_mtx.matmul(model));

            texture1.bind(0);
            cube.draw();
        }
        {
            mat4 model;
            model.scale(20.);
            shader->setMatrix("mvp", projection_view_mtx.matmul(model));

            texture2.bind(0);
            plane.draw();
        }
    }

    delete shader;

    return 0;
}