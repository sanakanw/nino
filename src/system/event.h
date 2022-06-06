#ifndef EVENT_H
#define EVENT_H

#include <vector>

#include "../common/log.h"

enum event_type_t {
  EVENT_KEY_PRESS,
  EVENT_MOUSE_MOVE
};

struct event_t {
  event_type_t type;
  union {
    struct {
      int   code;
      bool  action;
    } key_press;
    struct {
      int   dx;
      int   dy;
    } mouse_move;
  };
  
  event_t()
  {
    
  }
  
  event_t &init_mouse_move(int dx, int dy)
  {
    type = EVENT_MOUSE_MOVE;
    mouse_move.dx = dx;
    mouse_move.dy = dy;
    return *this;
  }
  
  event_t &init_key_press(int code, bool action)
  {
    type = EVENT_KEY_PRESS;
    key_press.code = code;
    key_press.action = action;
    return *this;
  }
};

class event_queue_t {
private:
  std::vector<event_t> m_event_queue;

public:
  bool  get_event(event_t &event);
  void  post_event(event_t event);
};

#endif
