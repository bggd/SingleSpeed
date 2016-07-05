#pragma once


struct Shader {

  GLuint program;
  GLuint vert;
  GLuint frag;

  Shader();
  ~Shader();

  bool compile(GLenum type, const char* src);
  void bind_attr(GLuint location, const char* name);
  bool link();

  GLint get_uniform_location(const char* name);
  void uniform_mat4(GLint location, GLsizei count, const GLfloat* v);

  void bind_frag_data_location(GLuint color_number, const char* name);

  void bind();
  void unbind();

};
