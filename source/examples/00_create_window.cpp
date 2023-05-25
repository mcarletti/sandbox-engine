#include <sandbox/sandbox.hpp>

int main(int argc, char* argv[])
{
    sb::Window window;
    sb::Input input(&window);
    sb::utils::Timer timer;

    window.setTitle("Hello, Sandbox!");

    sb::real target_fps = 30.;
    window.setRefreshRate(target_fps);

    bool fullscreen = false;
    sb::real angle = 0.;

    while (true)
    {
        sb::real delta_t = timer.getFrameTime() * 1e-9;
        angle += 50 * delta_t;

        window.update();
        input.update();

        if (input.isKeyPressed(sb::KEY_q) || input.isKeyDown(sb::KEY_Escape))
            break;

        if (input.isKeyPressed(sb::KEY_f))
        {
            fullscreen = !fullscreen;
            window.setFullscreen(fullscreen);
        }

        if (input.isKeyPressed(sb::KEY_plus) || input.isKeyPressed(sb::KEY_KP_Add))
        {
            target_fps += 1.;
            std::cout << "target_fps: " << target_fps << std::endl;
            window.setRefreshRate(target_fps);
        }

        if (input.isKeyPressed(sb::KEY_minus) || input.isKeyPressed(sb::KEY_KP_Subtract))
        {
            target_fps = std::max(target_fps - 1., 1.);
            std::cout << "target_fps: " << target_fps << std::endl;
            window.setRefreshRate(target_fps);
        }

        glLoadIdentity();

        sb::real W = (sb::real)window.width();
        sb::real H = (sb::real)window.height();
        sb::real max_size = std::max(W, H);
        glOrtho(-W / max_size, +W / max_size, -H / max_size, +H / max_size, -1, +1);

        glRotated(angle, 0., 0., 1.);
        glBegin(GL_TRIANGLES);
            glColor3d(1., 0., 0.);
            glVertex2d( 0.,    0.5);
            glColor3d(0., 1., 0.);
            glVertex2d(-0.25, -0.15);
            glColor3d(0., 0., 1.);
            glVertex2d( 0.25, -0.15);
        glEnd();
    }

    return 0;
}