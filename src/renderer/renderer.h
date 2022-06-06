#ifndef RENDERER_H
#define RENDERER_H

#include "mesh_pool.h"
#include "shader.h"
#include "../game/game.h"
#include "../common/math.h"

class renderer_t {
private:
  const game_t  &m_game;
  
  mesh_pool_t   m_mesh_pool;
  shader_t      m_shader;
  GLuint        m_uloc_mvp;
  
  mat4_t        m_projection_matrix;
  mat4_t        m_view_projection_matrix;
  
  mesh_t        m_meshes;

public:
  void          setup_view_projection_matrix();

public:
  renderer_t(const game_t &game);
  
  void          render();
};

#endif
