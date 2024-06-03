/** @file Input.hpp
 *  @brief X11 input manager.
 * 
 *  Input manager is linked to a specific X11 window
 *  which focus state is used to enable/disable the
 *  keyboard and mouse event listeners.
 * 
 *  References
 *  https://tronche.com/gui/x/xlib/events/keyboard-pointer/keyboard-pointer.html
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/core/types.hpp>
#include <sandbox/core/Window.hpp>

namespace sb
{
    class Input
    {
    public:

        /*!
            @brief Constructor.

            Initialize a keyboard and mouse event handler 
            linked to a specific window.

            @param w Pointer to the linked window object.
        */
        Input(Window* w);


        //! Update keyboard and mouse state vectors.
        void update();

        /*!
            @brief Check if a keyboard button is currently pressed.

            @param code Integer representig the code of the button.
        */
        bool isKeyDown(uint code) const;

        /*!
            @brief Check if a keyboard button is currently unpressed.

            @param code Integer representig the code of the button.
        */
        bool isKeyUp(uint code) const;

        /*!
            @brief Check if a keyboard button has been pressed.

            @param code Integer representig the code of the button.
        */
        bool isKeyPressed(uint code) const;

        /*!
            @brief Check if a keyboard button has been released.

            @param code Integer representig the code of the button.
        */
        bool isKeyReleased(uint code) const;
        
        /*!
            @brief Check if a mouse button is currently pressed.

            @param code Integer representig the code of the button.
        */
        bool isMouseButtonDown(uint code) const;
        
        /*!
            @brief Check if a mouse button is currently unpressed.

            @param code Integer representig the code of the button.
        */
        bool isMouseButtonUp(uint code) const;

        /*!
            @brief Check if a mouse button has been pressed.

            @param code Integer representig the code of the button.
        */
        bool isMouseButtonPressed(uint code) const;

        /*!
            @brief Check if a mouse button has been released.

            @param code Integer representig the code of the button.
        */
        bool isMouseButtonReleased(uint code) const;

        /*!
            @brief Get the mouse position.

            @param x Horizontal mouse coordinate in pixels.
            @param y Vertical mouse coordinate in pixels.
            @param screen_space If false, mouse coords are relative to the window.
        */
        void mousePosition(int& x, int& y, bool screen_space = false);

        /*!
            @brief Set the mouse position in window reference system.

            @param x Horizontal mouse coordinate in pixels.
            @param y Vertical mouse coordinate in pixels.
        */
        void setMousePosition(int x, int y);

    private:

        //! Pointer to the linked window object.
        Window* _window{nullptr};

        //! Previous state of the keyboard.
        char _keymap_previous[32]{0};

        //! Current keyboard state.
        char _keymap_current[32]{0};

        //! Previous state of the mouse.
        uint _mouse_state_previous{0};

        //! Current mouse state.
        uint _mouse_state_current{0};

        //! Current mouse position in screen space.
        int _mouse_pos_root[2]{0};

        //! Current mouse position in window space.
        int _mouse_pos_win[2]{0};
    };
}