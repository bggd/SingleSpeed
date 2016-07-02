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

  static CoreEvents events;

  Event<MouseEventArgs> mouse_pressed;
  Event<MouseEventArgs> mouse_moved;
  Event<MouseEventArgs> mouse_released;

};
