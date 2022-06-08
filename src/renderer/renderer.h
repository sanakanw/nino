#ifndef RENDERER_H
#define RENDERER_H

#include "mesh_pool.h"
#include "shader.h"
#include "texture.h"
#include "map_model.h"
#include "sprite_model.h"
#include "../game/game.h"
#include "../game/map_file.h"
#include "../common/math.h"

class renderer_t {
private:
  const game_t  &m_game;
  
  mesh_pool_t       m_mesh_pool;
  shader_t          m_shader;
  GLuint            m_uloc_mvp;
  
  mat4_t            m_projection_matrix;
  mat4_t            m_view_projection_matrix;
  
  map_model_t       m_map_model;
  sprite_model_t    m_sprite_model;

public:
  void  setup_view_projection_matrix();

public:
  renderer_t(const game_t &game);
  
  void  new_map(map_file_t &map_file);
  void  render();
};

#endif
