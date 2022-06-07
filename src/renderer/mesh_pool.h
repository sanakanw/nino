#ifndef MESH_POOL_H
#define MESH_POOL_H

#include "gl.h"
#include "../common/math.h"

struct vertex_t {
  vec3_t  pos;
  vec2_t  uv;
  
  vertex_t() {}
  
  vertex_t(vec3_t _pos, vec2_t _uv)
  {
    pos = _pos;
    uv = _uv;
  }
};

struct mesh_t {
  GLuint  offset;
  GLuint  size;
};

class mesh_pool_t {
private:
  GLuint  m_vbo;
  int     m_max_vertices;
  int     m_vertex_ptr;
  
public:
  mesh_pool_t(int max_vertices);
  
  mesh_t  new_mesh(int num_vertices);
  void    sub_mesh(const mesh_t &mesh, int offset, const vertex_t *vertices, int num_vertices);
  mesh_t  load_mesh(const vertex_t *vertices, int num_vertices);
  
  void    draw_mesh(const mesh_t &mesh);
  void    draw_sub_mesh(const mesh_t &mesh, int offset, int size);
  
  int     get_vertex_pointer() { return m_vertex_ptr; }
};

#endif
