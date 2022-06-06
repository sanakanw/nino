#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include "event.h"

class window_t {
private:
  SDL_Window      *m_sdl_window;
  SDL_GLContext   m_sdl_gl_context;
  bool            m_quit;
  
public:
  window_t();
  
  void  poll(event_queue_t &event_queue);
  void  quit();
  void  swap();
  
  void  set_mouse_lock(bool lock);
  
  bool  should_quit();
};

#endif
