#include <sandbox/core/Input.hpp>
#include <cstring>
#include <cassert>

using namespace sb;

Input::Input(Window* w) :
    _window(w)
{
    assert(_window != nullptr);
}

void Input::update()
{
    // do nothing if the associated
    // window is not focused
    XID focused_window;
    int focus_state;
    XGetInputFocus(_window->display(), &focused_window, &focus_state);
    if (_window->xid() != focused_window)
        return;

    // query the keyboard status
    memcpy(_keymap_previous, _keymap_current, 32 * sizeof(char));
    XQueryKeymap(_window->display(), _keymap_current);

    // query the mouse status
    XID root_window_xid, child_window_xid;
    _mouse_state_previous = _mouse_state_current;
    XQueryPointer(_window->display(), _window->xid(),
                    &root_window_xid, &child_window_xid,
                    &_mouse_pos_root[0], &_mouse_pos_root[1],
                    &_mouse_pos_win[0], &_mouse_pos_win[1],
                    &_mouse_state_current);
}

bool Input::isKeyDown(uint code) const
{
    KeyCode keycode = XKeysymToKeycode(_window->display(), code);
    return !!( _keymap_current[ keycode >> 3 ] & ( 1 << (keycode & 7) ) );
}

bool Input::isKeyUp(uint code) const
{
    return !isKeyDown(code);
}

bool Input::isKeyPressed(uint code) const
{
    KeyCode keycode = XKeysymToKeycode(_window->display(), code);
    bool key_was_up = !(!!( _keymap_previous[ keycode >> 3 ] & ( 1 << (keycode & 7) ) ));
    return key_was_up && isKeyDown(code);
}

bool Input::isKeyReleased(uint code) const
{
    KeyCode keycode = XKeysymToKeycode(_window->display(), code);
    bool key_was_down = !!( _keymap_previous[ keycode >> 3 ] & ( 1 << (keycode & 7) ) );
    return key_was_down && isKeyUp(code);
}

bool Input::isMouseButtonDown(uint code) const
{
    assert(code < 13);
    uint button_mask = 1 << code;
    return !!(_mouse_state_current & button_mask);
}

bool Input::isMouseButtonUp(uint code) const
{
    assert(code < 13);
    return !isMouseButtonDown(code);
}

bool Input::isMouseButtonPressed(uint code) const
{
    assert(code < 13);
    uint button_mask = 1 << code;
    bool button_was_up = !(!!(_mouse_state_previous & button_mask));
    return button_was_up && isMouseButtonDown(code);
}

bool Input::isMouseButtonReleased(uint code) const
{
    assert(code < 13);
    uint button_mask = 1 << code;
    bool button_was_down = !!(_mouse_state_previous & button_mask);
    return button_was_down && isMouseButtonUp(code);
}

void Input::mousePosition(int& x, int& y, bool screen_space)
{
    if (screen_space)
    {
        x = _mouse_pos_root[0];
        y = _mouse_pos_root[1];
    }
    else
    {
        x = _mouse_pos_win[0];
        y = _mouse_pos_win[1];
    }
}