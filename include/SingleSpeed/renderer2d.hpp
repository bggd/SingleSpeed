#pragma once


namespace ss {


struct Renderer2D {

  Shader shader;

  static const GLuint POSITION = 0;
  static const GLuint UV = 1;
  static const GLuint COLOR = 2;

  GLint projection_location;

  Renderer2D();

  void clear();

  void ortho(float left, float right, float bottom, float top, float near_z, float far_z);

  void bind();
  void unbind();
};


} // namespace ss
