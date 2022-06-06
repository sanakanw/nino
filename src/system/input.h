#ifndef INPUT_H
#define INPUT_H

#include "../game/game.h"

class input_t {
private:
  float m_forward;
  float m_back;
  float m_left;
  float m_right;
  
  float m_yaw;
  float m_pitch;

public:
  input_t();
  
  void key_press(int key, int action);
  void mouse_move(int dx, int dy);
  
  usercmd_t base_move();
};

#endif
