#pragma once


namespace ss {


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

  void buffer_data(size_t size, const void* vertices, GLenum usage);

  void draw_elements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);

};


} // namespace ss
