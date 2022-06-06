#ifndef SHADER_H
#define SHADER_H

#include "gl.h"

class shader_t {
private:
  GLuint  m_program;

public:
  shader_t(const char *src_vertex, const char *src_fragment);
  
  void    bind();
  GLuint  get_uniform_location(const char *name);
};

#endif
