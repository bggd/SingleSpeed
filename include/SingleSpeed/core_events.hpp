#pragma once


struct EventArgs {
};


struct MouseEventArgs : EventArgs {

  enum Type {
    Pressed,
    Moved,
    Released,
    Dragged,
    Scrolled,
    Entered,
    Exited
  };

  Type type;
  int x, y;
  int scroll_x, scroll_y;

};


struct CoreEvents {

  static Event<MouseEventArgs> mouse_pressed;
  static Event<MouseEventArgs> mouse_moved;
  static Event<MouseEventArgs> mouse_released;
  static Event<MouseEventArgs> mouse_scrolled;

};
