#include "input.h"

#define SENSITIVITY 0.005f

input_t::input_t()
{
  m_forward = 0.0f;
  m_back    = 0.0f;
  m_left    = 0.0f;
  m_right   = 0.0f;
  
  m_yaw     = 0.0f;
  m_pitch   = 0.0f;
}

void input_t::key_press(int key, int action)
{
  switch (key) {
  case 'w':
    m_forward = action;
    break;
  case 'a':
    m_left = action;
    break;
  case 's':
    m_back = action;
    break;
  case 'd':
    m_right = action;
    break;
  }
}

void input_t::mouse_move(int dx, int dy)
{
  m_yaw += dx * SENSITIVITY;
  m_pitch += dy * SENSITIVITY;
}

usercmd_t input_t::base_move()
{
  return (usercmd_t) {
    .forward  = m_forward - m_back,
    .side     = m_right - m_left,
    .yaw      = m_yaw,
    .pitch    = m_pitch
  };
}
