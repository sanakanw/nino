#include "map_model.h"

#include "spr_file.h"
#include "sprite_map.h"
#include "../common/log.h"
#include <vector>

void build_tile_mesh(
  const sprite_map_t    &sprite_map,
  std::vector<vertex_t> &vertices,
  tile_t                tile,
  const vec3_t          &pos)
{
  static vertex_t face_vertices[] = {
    vertex_t(vec3_t(-0.5f, 0.0f, -0.0f), vec2_t(0.0, 1.0)),
    vertex_t(vec3_t(-0.5f, 0.0f, +1.0f), vec2_t(0.0, 0.0)),
    vertex_t(vec3_t(+0.5f, 0.0f, -0.0f), vec2_t(1.0, 1.0)),
    
    vertex_t(vec3_t(+0.5f, 0.0f, -0.0f), vec2_t(1.0, 1.0)),
    vertex_t(vec3_t(-0.5f, 0.0f, +1.0f), vec2_t(0.0, 0.0)),
    vertex_t(vec3_t(+0.5f, 0.0f, +1.0f), vec2_t(1.0, 0.0)),
  };
  
  static int num_face_vertices = sizeof(face_vertices) / sizeof(vertex_t);
  
  for (int i = 0; i < num_face_vertices; i++) {
    vertex_t vertex(
      face_vertices[i].pos + pos,
      face_vertices[i].uv * sprite_map.get_sprite_size() + sprite_map.get_uv_pos(tile));
    
    vertices.push_back(vertex);
  }
}

map_model_t::map_model_t(mesh_pool_t &mesh_pool)
  : m_mesh_pool(mesh_pool)
{
  m_sprite_map = NULL;
}

void map_model_t::load(map_file_t &map_file)
{
  if (m_sprite_map)
    delete m_sprite_map;
  
  std::string spr_path = "assets/sprites/" + std::string(map_file.get_spr()) + ".spr";
  std::ifstream file_spr(spr_path, std::ifstream::binary);
  if (!file_spr)
    LOG_ERROR() << "unable to open sprite map: " << spr_path;
  spr_file_t spr_file(file_spr);
  m_sprite_map = new sprite_map_t(spr_file);
  
  std::vector<vertex_t> vertices;
  std::vector<tile_t> data = map_file.load_data();
  
  for (int y = 0; y < map_file.get_height(); y++) {
    for (int x = 0; x < map_file.get_width(); x++) {
      vec3_t pos(x, 0, y);
      tile_t tile = data[x + y * map_file.get_width()] - 1;
      build_tile_mesh(*m_sprite_map, vertices, tile, pos);
    }
  }
  
  m_mesh = m_mesh_pool.load_mesh(vertices.data(), vertices.size());
}

void map_model_t::draw()
{
  if (m_sprite_map)
    m_sprite_map->bind();
  
  m_mesh_pool.draw_mesh(m_mesh);
}
