#include "renderer.h"

#include "../common/log.h"
#include "gl.h"

static const char *src_flat_vertex = "\
#version 300 es\n\
layout(location = 0) in vec3 v_pos;\
layout(location = 1) in vec2 v_uv;\
\
out vec2 vs_uv;\
\
uniform mat4 u_mvp;\
\
void main() {\
  vs_uv = v_uv;\
  gl_Position = u_mvp * vec4(v_pos, 1.0);\
}\
";

static const char *src_flat_fragment = "\
#version 300 es\n\
precision mediump float;\
\
in vec2 vs_uv;\
\
out vec4 frag_color;\
\
uniform sampler2D u_sampler;\
\
void main() {\
  frag_color = texture(u_sampler, vs_uv);\
}\
";

renderer_t::renderer_t(const game_t &game)
  : m_game(game),
    m_mesh_pool(4096),
    m_shader(src_flat_vertex, src_flat_fragment),
    m_sprite_renderer(game.get_edict(), game.get_sprite(), game.get_transform(), m_mesh_pool, vec2_t(1.0f / 4.0f, 1.0f / 8.0f))
{
  glClearColor(0.01f, 0.4f, 1.0f, 1.0f);
  
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  
  glCullFace(GL_FRONT);
  glDepthFunc(GL_LESS);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  m_sprite_map = texture_load("assets/sprite_map.png");
  m_uloc_mvp = m_shader.get_uniform_location("u_mvp");
  m_projection_matrix.init_perspective(1280.0 / 720.0, 1.0, -1.0, -100.0);
}

void renderer_t::render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  m_sprite_renderer.update(m_game.get_transform()[m_game.get_player_entity()].rotation);
  
  m_shader.bind();
  glBindTexture(GL_TEXTURE_2D, m_sprite_map);
  
  setup_view_projection_matrix();
  glUniformMatrix4fv(m_uloc_mvp, 1, GL_FALSE, m_view_projection_matrix.m);
  
  m_sprite_renderer.draw();
}

void renderer_t::setup_view_projection_matrix()
{
  vec3_t view_origin = m_game.get_transform()[m_game.get_player_entity()].position;
  quat_t view_angle = m_game.get_transform()[m_game.get_player_entity()].rotation;
  
  vec3_t inverted_view_origin = view_origin * -1;
  quat_t inverted_view_angle = view_angle.conjugate();
  
  mat4_t translation_matrix = mat4_t().init_translation(inverted_view_origin);
  mat4_t rotation_matrix = mat4_t().init_rotation(inverted_view_angle);
  
  mat4_t view_matrix = translation_matrix * rotation_matrix;
  
  m_view_projection_matrix = view_matrix * m_projection_matrix;
}
