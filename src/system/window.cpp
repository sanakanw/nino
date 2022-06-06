#include "window.h"

window_t::window_t()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  
  m_sdl_window = SDL_CreateWindow(
    "",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    1280, 720,
    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  
  m_sdl_gl_context = SDL_GL_CreateContext(m_sdl_window);
  
  m_quit = false;
}

void window_t::poll(event_queue_t &event_queue)
{
  static SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_KEYDOWN:
      event_queue.post_event(event_t().init_key_press(event.key.keysym.sym, 1));
      break;
    case SDL_KEYUP:
      event_queue.post_event(event_t().init_key_press(event.key.keysym.sym, 0));
      break;
    case SDL_MOUSEMOTION:
      event_queue.post_event(event_t().init_mouse_move(event.motion.xrel, event.motion.yrel));
      break;
    case SDL_QUIT:
      m_quit = true;
      break;
    }
  }
}

void window_t::quit()
{
  SDL_GL_DeleteContext(m_sdl_gl_context);
  SDL_DestroyWindow(m_sdl_window);
  SDL_Quit();
}

void window_t::swap()
{
  SDL_GL_SwapWindow(m_sdl_window);
}

bool window_t::should_quit()
{
  return m_quit;
}

void window_t::set_mouse_lock(bool lock)
{
  SDL_SetRelativeMouseMode(static_cast<SDL_bool>(lock));
}
