Renderer2D::Renderer2D()
{
  std::string vert = R"(
#version 100

uniform mat4 projection;

attribute vec2 position;
attribute vec2 uv;
attribute vec4 color;

varying vec4 vColor;
varying vec2 vUV;

void main()
{
  vColor = color;
  vUV = uv;
  gl_Position = projection * vec4(position, 0.0, 1.0);
}
)";

  std::string frag = R"(
#version 100

uniform sampler2D tex;

varying vec4 vColor;
varying vec2 vUV;

void main()
{
  gl_FragColor = texture2D(tex, vUV) * vColor;
}
)";

  this->shader.compile(GL_VERTEX_SHADER, vert.c_str());
  this->shader.compile(GL_FRAGMENT_SHADER, frag.c_str());
  this->shader.bind_attr(Renderer2D::POSITION, "position");
  this->shader.bind_attr(Renderer2D::UV, "uv");
  this->shader.bind_attr(Renderer2D::COLOR, "color");
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
  gl::blend_equation_separate(GL_FUNC_ADD, GL_FUNC_ADD);
  gl::blend_func_separate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  gl::enable(GL_SCISSOR_TEST);

  gl::enable(GL_CULL_FACE);
  gl::cull_face(GL_BACK);

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
