#include <sandbox/core/Window.hpp>
#include <sandbox/utils/Logger.hpp>
#include <sstream>
#include <X11/Xatom.h>
#include <cstring> // memset

namespace sb
{
    Window::Window(std::string title, int xpos, int ypos, int width, int height)
    {
        std::stringstream ss;

        _display = XOpenDisplay(nullptr);
        if(_display == nullptr)
        {
            utils::Logger::write("Cannot connect to X server");
            exit(1);
        }

        XID root_window_xid = DefaultRootWindow(_display);

        GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
        XVisualInfo* visual_info = glXChooseVisual(_display, 0, att);

        if(visual_info == nullptr)
        {
            utils::Logger::write("No appropriate visual found");
            exit(1);
        } 
        else
        {
            ss.str("");
            ss << "Visual " << (void *)visual_info->visualid << " selected";
            utils::Logger::write(ss.str());
        }

        XSetWindowAttributes swa;
        swa.colormap = XCreateColormap(_display, root_window_xid, visual_info->visual, AllocNone);
        swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask;

        _position[0] = xpos;
        _position[1] = ypos;
        _size[0] = width;
        _size[1] = height;
        _window_xid = XCreateWindow(_display, root_window_xid, xpos, ypos, width, height, 0, visual_info->depth, InputOutput, visual_info->visual, CWColormap | CWEventMask, &swa);

        XMapWindow(_display, _window_xid);
        XStoreName(_display, _window_xid, title.c_str());

        _gl_context = glXCreateContext(_display, visual_info, nullptr, GL_TRUE);
        glXMakeCurrent(_display, _window_xid, _gl_context);

        // glew must be initialized AFTER the opengl context has been created
        GLenum status = glewInit();
        ss.str("");
        ss << "GLEW has " << (status == GLEW_OK ? "" : "NOT ") << "been initialized";
        utils::Logger::write(ss.str());
        if (status != GLEW_OK)
        {
            ss.str("");
            ss << "Error: " << glewGetErrorString(status);
            utils::Logger::write(ss.str());
        }
        else
            if (GLEW_VERSION_4_3)
                utils::Logger::write("OpenGL 4.3 is supported");

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Window::~Window()
    {
        glXMakeCurrent(_display, None, nullptr);
        glXDestroyContext(_display, _gl_context);
        XDestroyWindow(_display, _window_xid);
        XCloseDisplay(_display);
    }

    void Window::update()
    {
        real elapsed_time_us = static_cast<real>(_timer.getFrameTime()) * 1e-3;
        if (elapsed_time_us < _min_target_delay_us)
            utils::Timer::usleep(_min_target_delay_us - elapsed_time_us);

        XWindowAttributes window_attributes;
        XGetWindowAttributes(_display, _window_xid, &window_attributes);

        _position[0] = window_attributes.x;
        _position[1] = window_attributes.y;
        _size[0] = window_attributes.width;
        _size[1] = window_attributes.height;

        glViewport(0, 0, _size[0], _size[1]);
        glXSwapBuffers(_display, _window_xid);

        glClearColor(0.3, 0.6, 0.9, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void Window::setTitle(std::string title)
    {
        XStoreName(_display, _window_xid, title.c_str());
    }

    void Window::setFullscreen(bool enable)
    {
        // source
        // https://stackoverflow.com/questions/10897503/opening-a-fullscreen-opengl-window

        Atom wm_state = XInternAtom(_display, "_NET_WM_STATE", False);
        Atom fullscreen = XInternAtom(_display, "_NET_WM_STATE_FULLSCREEN", False);

        XEvent xev;
        memset(&xev, 0, sizeof(xev));
        xev.type = ClientMessage;
        xev.xclient.window = _window_xid;
        xev.xclient.message_type = wm_state;
        xev.xclient.format = 32;
        xev.xclient.data.l[0] = (int)enable;
        xev.xclient.data.l[1] = fullscreen;
        xev.xclient.data.l[2] = 0;

        XSendEvent(_display, DefaultRootWindow(_display), False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
        XFlush(_display);
    }

    void Window::setRefreshRate(real fps)
    {
        _min_target_delay_us = (1000. / fps) * 1e3;
    }

    Display* Window::display() { return _display; }
    XID Window::xid() const { return _window_xid; }

    int Window::xpos() const { return _position[0]; }
    int Window::ypos() const { return _position[1]; }

    int Window::width() const { return _size[0]; }
    int Window::height() const { return _size[1]; }

    void Window::size(int& w, int& h) const
    {
        w = _size[0];
        h = _size[1];
    }
}