/** @file Window.hpp
 *  @brief X11 window manager. It creates a windows with OpenGL context.
 * 
 *  References
 *  https://www.khronos.org/opengl/wiki/Programming_OpenGL_in_Linux:_GLX_and_Xlib
 *  https://venam.nixers.net/blog/unix/2016/10/25/x11-blah-blah.html
 *  http://mech.math.msu.su/~nap/2/GWindow/xintro.html
 * 
 *  @author Marco Carletti
 * 
 *  @bug Creating a scoped visual info object causes a memory leak;
 *       a possible solution is to define it as global.
 *  @bug Class name 'Window' is ambiguous due to X11 name clash;
 *       currently you must specify the namespace when using this
 *       class (eg. 'sb::Window' works while 'Window' fails.).
*/
#pragma once

#include <iostream>
#include <cstdlib>
#include <X11/Xlib.h>
#include <sandbox/core/types.hpp>
#include <sandbox/core/opengl.hpp>
#include <sandbox/utils/Timer.hpp>
#include <cassert>

namespace sb
{
    class Window
    {
    public:

        /*!
            @brief Constructor.

            Create a X11 window with OpenGL enabled. 
            Advanced graphics functions are enabled through GLEW.

            @param title Title of the window.
            @param xpos X-coord (in pixels) of the top-left corner of the window.
            @param ypos Y-coord (in pixels) of the top-left corner of the window.
            @param width Width (in pixels) of the window.
            @param height Height (in pixels) of the window.
        */
        Window(std::string title = "Sandbox Engine", int xpos = 0, int ypos = 0, int width = 800, int height = 600);

        //! Destructor.
        ~Window();

        //! Update window attributes and clear OpenGL buffers.
        void update();

        //! Set window title.
        void setTitle(std::string title);

        //! Enable/disable fullscreen mode.
        void setFullscreen(bool enable);

        //! Set desired framerate [FPS].
        void setRefreshRate(real fps);

        //! Get X11 display pointer.
        Display* display();
        //! Get X11 window unique index.
        XID xid() const;

        //! Get top-left corner x-coord.
        int xpos() const;
        //! Get top-left corner y-coord.
        int ypos() const;

        //! Get window width.
        int width() const;
        //! Get window height.
        int height() const;

        //! Get window dimensions.
        void size(int& w, int& h) const;

        //! Get default screen dimensions.
        void screenSize(int&w, int& h) const;

        //! Get wether the window is focused or not.
        bool focused() const;

    private:
        //! Pointer to X11 display object.
        Display* _display{nullptr};

        //! Unique index of the X11 window.
        XID _window_xid{0};

        //! OpenGL context pointer.
        GLXContext _gl_context{nullptr};

        //! X11 event reference object.
        XEvent _mouse_event{XEvent()};

        //! Position of the window in screen space (in pixels).
        int _position[2]{0};

        //! Window resolution (in pixels).
        int _size[2]{0};
    };
}