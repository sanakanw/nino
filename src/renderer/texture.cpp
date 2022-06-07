#include "texture.h"

#include <SDL2/SDL_image.h>

GLuint texture_load(const char *path)
{
  SDL_Surface *bitmap = IMG_Load(path);
  
  if (!bitmap)
    LOG_ERROR() << "could not load " << path;
  
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap->w, bitmap->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
  
  return texture;
}
