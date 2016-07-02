#pragma once


struct IBO {

  GLuint id;

  IBO();
  IBO(IBO&& other) : id(std::move(other.id)) {}
  IBO(const IBO& other) = delete;
  IBO& operator=(const IBO& other) = delete;
  IBO& operator=(IBO&& other)
  {
    this->id = std::move(other.id);
    return *this;
  }
  ~IBO();

  void bind();
  void unbind();

  void buffer_data(const void* vertices, size_t size, GLenum usage);

  void draw_elements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);

};
