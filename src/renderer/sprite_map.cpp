#include "sprite_map.h"

#include "texture.h"
#include "../common/log.h"

sprite_map_t::sprite_map_t(spr_file_t &spr_file)
{
  std::string src_path = "assets/sprites/" + std::string(spr_file.get_src()) + ".png";
  m_texture = texture_load(src_path.c_str());
  m_columns = spr_file.get_columns();
  m_tile_count = spr_file.get_tile_count();
  m_sprite_size = vec2_t(
    (float) spr_file.get_spr_width() / (float) spr_file.get_img_width(),
    (float) spr_file.get_spr_height() / (float) spr_file.get_img_height());
}

vec2_t sprite_map_t::get_uv_pos(int id) const
{
  return vec2_t(id % m_columns, id / m_columns) * m_sprite_size;
}

void sprite_map_t::bind()
{
  glBindTexture(GL_TEXTURE_2D, m_texture);
}
