#ifndef GAMEDEF_H
#define GAMEDEF_H

#include "../common/math.h"

struct usercmd_t {
  float forward;
  float side;
  float yaw;
  float pitch;
};

struct transform_t {
  vec3_t    position;
  quat_t    rotation;
};

struct client_t {
  usercmd_t usercmd;
};

struct sprite_t {
  vec2_t    uv_ofs;
};

enum class component_t {
  TRANSFORM = (1 << 0),
  CLIENT    = (1 << 1),
  SPRITE    = (1 << 2)
};

constexpr int operator|(component_t lhs, component_t rhs)
{
  return static_cast<int>(lhs) | static_cast<int>(rhs);
}

#endif
