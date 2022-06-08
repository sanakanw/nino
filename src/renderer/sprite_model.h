#ifndef SPRITE_POOL_H
#define SPRITE_POOL_H

#include "../game/edict.h"
#include "../game/gamedef.h"
#include "mesh_pool.h"

#define MAX_SPRITES 32

class sprite_model_t {
private:
  mesh_t      m_mesh;
  int         m_num_sprites;
  
  mesh_pool_t &m_mesh_pool;
  vec2_t      m_sprite_size;
  
  const edict_t               &m_edict;
  const cdict_t<sprite_t>     &m_sprite;
  const cdict_t<transform_t>  &m_transform;
  
public:
  sprite_model_t(
    const edict_t               &edict,
    const cdict_t<sprite_t>     &sprite,
    const cdict_t<transform_t>  &transform,
    mesh_pool_t                 &mesh_pool,
    const vec2_t                &sprite_size);
  
  void  update(const quat_t &cam_rot);
  void  draw();
};

#endif
