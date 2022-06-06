#ifndef GAMEDEF_H
#define GAMEDEF_H

#include "../common/math.h"

enum class model_id_t {
  MODEL_CUBE,
  MODEL_PLANE
};

struct usercmd_t {
  float forward;
  float side;
  float yaw;
  float pitch;
};

struct transform_t {
  vec3_t  position;
  quat_t  rotation;
};

struct client_t {
  usercmd_t usercmd;
};

enum class component_t {
  TRANSFORM = (1 << 0),
  CLIENT    = (1 << 1)
};

constexpr int operator|(component_t lhs, component_t rhs)
{
  return static_cast<int>(lhs) | static_cast<int>(rhs);
}

#endif
