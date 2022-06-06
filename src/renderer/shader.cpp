#include "shader.h"

static GLuint compile_shader(GLuint type, const char *src)
{
  int success;
  static GLchar info[1024];
  
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, NULL);
  
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 1024, NULL, info);
    LOG_ERROR() << "failed to compile shader" << std::endl << info;
  }
  
  return shader;
}

static GLuint link_shader(GLuint vertex_shader, GLuint fragment_shader)
{
  int success;
  static GLchar info[1024];
  
  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(program, 1024, NULL, info);
    LOG_ERROR() << "failed to link shader" << std::endl << info;
  }
  
  glDetachShader(program, vertex_shader);
  glDetachShader(program, fragment_shader);
  
  return program;
}

shader_t::shader_t(const char *src_vertex, const char *src_fragment)
{
  GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, src_vertex);
  GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, src_fragment);
  
  m_program = link_shader(vertex_shader, fragment_shader);
  
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

GLuint shader_t::get_uniform_location(const char *name)
{
  return glGetUniformLocation(m_program, name);
}

void shader_t::bind()
{
  glUseProgram(m_program);
}
