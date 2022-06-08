#ifndef SPRITE_MAP_H
#define SPRITE_MAP_H

#include "gl.h"
#include "spr_file.h"
#include "../common/math.h"

class sprite_map_t {
private:
  GLuint  m_texture;
  vec2_t  m_sprite_size;
  int     m_tile_count;
  int     m_columns;
  
public:
  sprite_map_t(spr_file_t &spr_file);
  
  void    bind();
  vec2_t  get_uv_pos(int id) const;
  
  const vec2_t &get_sprite_size() const { return m_sprite_size; }
};

#endif
