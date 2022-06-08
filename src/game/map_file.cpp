#include "map_file.h"

#include "../common/log.h"

map_file_t::map_file_t(std::ifstream &in)
  : m_in(in)
{
  m_in.read(m_spr, sizeof(m_spr));
  m_in.read((char*) &m_width, sizeof(m_width));
  m_in.read((char*) &m_height, sizeof(m_height));
}

std::vector<tile_t> map_file_t::load_data()
{
  m_in.seekg(sizeof(m_spr) + 2 * sizeof(int), m_in.beg);
  
  int buf_size = m_width * m_height * sizeof(int);
  tile_t *buf_data = (tile_t*) malloc(buf_size);
  m_in.read((char*) buf_data, buf_size);
  std::vector<tile_t> data = std::vector<tile_t>(buf_data, buf_data + buf_size / sizeof(tile_t));
  free(buf_data);
  
  return data;
}
