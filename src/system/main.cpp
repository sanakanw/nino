#include "input.h"
#include "window.h"
#include "../game/game.h"
#include "../common/log.h"
#include "../renderer/gl.h"
#include "../renderer/renderer.h"
#include <iostream>

void system_event_loop(event_queue_t &event_queue, input_t &input)
{
  event_t event;
  while (event_queue.get_event(event)) {
    switch (event.type) {
    case EVENT_KEY_PRESS:
      input.key_press(event.key_press.code, event.key_press.action);
      break;
    case EVENT_MOUSE_MOVE:
      input.mouse_move(event.mouse_move.dx, event.mouse_move.dy);
    }
  }
}

int main(int argc, char *argv[])
{
  window_t      window;
  
  window.set_mouse_lock(true);
  
  gl_init();
  
  input_t       input;
  event_queue_t event_queue;
  game_t        game;
  renderer_t    renderer(game);
  
  while (!window.should_quit()) {
    window.poll(event_queue);
    system_event_loop(event_queue, input);
    game.update(input.base_move());
    renderer.render();
    window.swap();
  }
  
  window.quit();
  
  return 0;
}
