extern std::string renderer2d_gles2_vert;
extern std::string renderer2d_gles2_frag;
extern std::string renderer2d_gl3_vert;
extern std::string renderer2d_gl3_frag;

Renderer2D::Renderer2D()
{
  std::string version = "#version ";
  std::string vert;
  std::string frag;

  if (GLInfo::is_gles2) {
    version += "100";
    vert = version + renderer2d_gles2_vert;
    frag = version + renderer2d_gles2_frag;
  }
  else {
    if (GLInfo::major == 3 && GLInfo::minor == 3) version += "330";
    vert = version + renderer2d_gl3_vert;
    frag = version + renderer2d_gl3_frag;
  }

  std::cout << vert << std::endl;

  this->shader.compile(GL_VERTEX_SHADER, vert.c_str());
  this->shader.compile(GL_FRAGMENT_SHADER, frag.c_str());
  this->shader.bind_attr(Renderer2D::POSITION, "position");
  this->shader.bind_attr(Renderer2D::UV, "uv");
  this->shader.bind_attr(Renderer2D::COLOR, "color");
  this->shader.bind_frag_data_location(0, "fragColor");
  this->shader.link();

  this->shader.bind();
  this->projection_location = this->shader.get_uniform_location("projection");
  this->shader.unbind();
}

void Renderer2D::clear()
{
  gl::clear(GL_COLOR_BUFFER_BIT);
}

void Renderer2D::ortho(float left, float right, float bottom, float top, float nearVal, float farVal)
{
  mat4x4 ortho;
  mat4x4_identity(ortho);

  mat4x4_ortho(ortho, left, right, bottom, top, nearVal, farVal);

  this->shader.uniform_mat4(this->projection_location, 1, (const GLfloat*)ortho);
}


void Renderer2D::bind()
{
  // set alpha blending
  gl::enable(GL_BLEND);
  //gl::blend_equation_separate(GL_FUNC_ADD, GL_FUNC_ADD);
  //gl::blend_func_separate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  gl::blend_equation(GL_FUNC_ADD);
  gl::blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  gl::enable(GL_SCISSOR_TEST);

  //gl::enable(GL_CULL_FACE);
  //gl::cull_face(GL_BACK);

  this->shader.bind();
  gl::enable_vertex_attrib_array(Renderer2D::POSITION);
  gl::enable_vertex_attrib_array(Renderer2D::UV);
  gl::enable_vertex_attrib_array(Renderer2D::COLOR);
}

void Renderer2D::unbind()
{
  gl::disable_vertex_attrib_array(Renderer2D::POSITION);
  gl::disable_vertex_attrib_array(Renderer2D::UV);
  gl::disable_vertex_attrib_array(Renderer2D::COLOR);
  this->shader.unbind();

  gl::disable(GL_BLEND);
  gl::disable(GL_SCISSOR_TEST);
}
