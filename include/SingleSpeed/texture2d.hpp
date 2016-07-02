#pragma once


struct Texture2D {

  GLuint id;

  Texture2D();
  Texture2D(Texture2D&& other) : id(std::move(other.id)) {}
  Texture2D(const Texture2D& other) = delete;
  Texture2D& operator=(const Texture2D& other) = delete;
  Texture2D& operator=(Texture2D&& other)
  {
    this->id = std::move(other.id);
    return *this;
  }
  ~Texture2D();

  void bind();
  void unbind();

  void tex_parameteri(GLenum pname, GLint param);

  void upload_rgb8(int width, int height, const unsigned char* image);
  void upload_rgba8(int width, int height, const unsigned char* image);

};
