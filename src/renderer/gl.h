#ifndef GL_H
#define GL_H

#include "../common/log.h"
#include <GL/glew.h>

static inline bool gl_init()
{
  glewExperimental = true;
  
  GLuint status = glewInit();
  if (status != GLEW_OK) {
    LOG_ERROR()
      << "failed to initialize glew: "
      << glewGetErrorString(status)
      << std::endl;
    
    return false;
  }
  
  return true;
}

#endif
