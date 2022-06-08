#include "spr_file.h"

#include "../common/log.h"

spr_file_t::spr_file_t(std::ifstream &in)
  : m_in(in)
{
  m_in.read(m_src, sizeof(m_src));
  m_in.read((char*) &m_img_width, sizeof(m_img_width));
  m_in.read((char*) &m_img_height, sizeof(m_img_height));
  m_in.read((char*) &m_spr_width, sizeof(m_spr_width));
  m_in.read((char*) &m_spr_height, sizeof(m_spr_height));
  m_in.read((char*) &m_tile_count, sizeof(m_tile_count));
  m_in.read((char*) &m_columns, sizeof(m_columns));
}
