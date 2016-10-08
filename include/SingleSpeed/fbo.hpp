#pragma once


namespace ss {


struct FBO {

  GLuint id;
  GLuint id_depth;

  FBO();
  FBO(FBO&& other) : id(std::move(other.id)), id_depth(std::move(other.id_depth)) {}
  FBO(const FBO& other) = delete;
  FBO& operator=(const FBO& other) = delete;
  FBO& operator=(FBO&& other)
  {
    this->id = std::move(other.id);
    this->id_depth = std::move(other.id_depth);
    return *this;
  }
  ~FBO();

  void bind();
  void unbind();

  void attach(const Texture2D& texture);
  void attach_depth(int width, int height);
};


} // namespace ss
