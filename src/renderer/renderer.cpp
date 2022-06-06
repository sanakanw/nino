#include "renderer.h"

#include "../common/log.h"
#include "gl.h"

static const char *src_flat_vertex = "\
#version 300 es\n\
layout(location = 0) in vec3 v_pos;\
layout(location = 1) in vec2 v_uv;\
\
uniform mat4 u_mvp;\
\
void main() {\
  gl_Position = u_mvp * vec4(v_pos, 1.0);\
}\
";

static const char *src_flat_fragment = "\
#version 300 es\n\
precision mediump float;\
\
out vec4 frag_color;\
\
void main() {\
  frag_color = vec4(1.0, 1.0, 1.0, 1.0);\
}\
";

renderer_t::renderer_t(const game_t &game)
  : m_game(game),
    m_mesh_pool(256),
    m_shader(src_flat_vertex, src_flat_fragment)
{
  m_uloc_mvp = m_shader.get_uniform_location("u_mvp");
  
  m_projection_matrix.init_perspective(1280.0 / 720.0, 1.0, -1.0, -100.0);
  
  vertex_t vertices[] = {
    vertex_t(vec3_t(0.0, 0.0, 4.0), vec2_t(0.0, 0.0)),
    vertex_t(vec3_t(1.0, 0.0, 4.0), vec2_t(1.0, 0.0)),
    vertex_t(vec3_t(0.0, 1.0, 4.0), vec2_t(0.0, 1.0)),
  };
  
  m_mesh_triangle = m_mesh_pool.load_mesh(vertices, sizeof(vertices) / sizeof(vertex_t));
}

void renderer_t::render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  
  m_shader.bind();
  setup_view_projection_matrix();
  glUniformMatrix4fv(m_uloc_mvp, 1, GL_FALSE, m_view_projection_matrix.m);
  m_mesh_pool.draw_mesh(m_mesh_triangle);
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
