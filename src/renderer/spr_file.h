#ifndef SPR_FILE_H
#define SPR_FILE_H

#include "../common/file.h"
#include <fstream>

class spr_file_t {
private:
  std::ifstream &m_in;
  sz32_t        m_src;
  int           m_img_width;
  int           m_img_height;
  int           m_spr_width;
  int           m_spr_height;
  int           m_tile_count;
  int           m_columns;

public:
  spr_file_t(std::ifstream &in);
  
  const char *get_src() const { return m_src; }
  int get_img_width() const { return m_img_width; }
  int get_img_height() const { return m_img_height; }
  int get_spr_width() const { return m_spr_width; }
  int get_spr_height() const { return m_spr_height; }
  int get_tile_count() const { return m_tile_count; }
  int get_columns() const { return m_columns; }
};

#endif
