#pragma once


struct VBO {

  GLuint id;

  VBO();
  VBO(VBO&& other) : id(std::move(other.id)) {}
  VBO(const VBO& other) = delete;
  VBO& operator=(const VBO& other) = delete;
  VBO& operator=(VBO&& other)
  {
    this->id = std::move(other.id);
    return *this;
  }
  ~VBO();

  void bind();

  void unbind();
  
  void vertex_attrib_pointer(GLuint location, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* offset);

  void buffer_data(const void* vertices, size_t size, GLenum usage);

  void draw_arrays(GLenum mode, GLint first, GLsizei count);

  // Windows's GL header hasn't GL_***_DRAW
  static const GLenum STATIC_DRAW;
  static const GLenum STREAM_DRAW;
  static const GLenum DYNAMIC_DRAW;

};
