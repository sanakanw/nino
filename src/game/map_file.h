#ifndef MAP_FILE_H
#define MAP_FILE_H

#include <fstream>
#include <vector>
#include "../common/file.h"

using tile_t = int;

class map_file_t {
private:
  std::ifstream &m_in;
  sz32_t        m_spr;
  int           m_width;
  int           m_height;

public:
  map_file_t(std::ifstream &in);
  
  std::vector<tile_t> load_data();
  
  const char *get_spr() const { return m_spr; }
  int get_width() const { return m_width; }
  int get_height() const { return m_height; }
};

#endif
