Texture2D::Texture2D()
{
  glGenTextures(1, &this->id);
  glBindTexture(GL_TEXTURE_2D, this->id);
  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D()
{
  if (glIsTexture(this->id)) glDeleteTextures(1, &this->id);
}

void Texture2D::bind()
{
  glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture2D::unbind()
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::tex_parameteri(GLenum pname, GLint param)
{
  glTexParameteri(GL_TEXTURE_2D, pname, param);
}

void Texture2D::upload_rgb8(int width, int height, const unsigned char* image)
{
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
}

void Texture2D::upload_rgba8(int width, int height, const unsigned char* image)
{
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
}
