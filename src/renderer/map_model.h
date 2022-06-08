#ifndef MAP_MODEL_H
#define MAP_MODEL_H

#include "mesh_pool.h"
#include "sprite_map.h"
#include "../game/map_file.h"

class map_model_t {
private:
  mesh_pool_t   &m_mesh_pool;
  sprite_map_t  *m_sprite_map;
  mesh_t        m_mesh;

public:
  map_model_t(mesh_pool_t &mesh_pool);
  
  void  load(map_file_t &map_file);
  void  draw();
};

#endif
