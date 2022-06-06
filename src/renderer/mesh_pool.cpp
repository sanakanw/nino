#include "mesh_pool.h"

mesh_pool_t::mesh_pool_t(int max_vertices)
{
  m_max_vertices = max_vertices;
  m_vertex_ptr = 0;
  
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_max_vertices * sizeof(vertex_t), 0, GL_STATIC_DRAW);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (float*) 0);
  
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (float*) 3);
}

mesh_t mesh_pool_t::new_mesh(int num_vertices)
{
  if (m_vertex_ptr + num_vertices >= m_max_vertices) {
    LOG_ERROR()
      << "mesh pool ran out of memory "
      << m_vertex_ptr + num_vertices
      << "/"
      << m_max_vertices;
  }
  
  mesh_t mesh;
  mesh.offset = m_vertex_ptr;
  mesh.size = num_vertices;
  m_vertex_ptr += num_vertices;
  
  return mesh;
}

void mesh_pool_t::sub_mesh(const mesh_t &mesh, int offset, const vertex_t *vertices, int num_vertices)
{
  if (offset + num_vertices > mesh.size) {
    LOG_ERROR()
      << "mesh substitution out of bounds"
      << offset + num_vertices
      << "/"
      << mesh.size;
  }
  
  glBufferSubData(
    GL_ARRAY_BUFFER,
    (mesh.offset + offset) * sizeof(vertex_t),
    num_vertices * sizeof(vertex_t),
    vertices);
}

mesh_t mesh_pool_t::load_mesh(const vertex_t *vertices, int num_vertices)
{
  mesh_t mesh = new_mesh(num_vertices);
  sub_mesh(mesh, 0, vertices, num_vertices);
  return mesh;
}

void mesh_pool_t::draw_mesh(const mesh_t &mesh)
{
  glDrawArrays(GL_TRIANGLES, mesh.offset, mesh.size);
}
