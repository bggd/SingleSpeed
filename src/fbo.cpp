FBO::FBO() : id_depth(0)
{
  glGenFramebuffers(1, &this->id);
  glBindFramebuffer(GL_FRAMEBUFFER, this->id);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FBO::~FBO()
{
  if (this->id_depth != 0 && glIsRenderbuffer(this->id_depth)) glDeleteRenderbuffers(1, &this->id_depth);
  if (glIsFramebuffer(this->id) == GL_TRUE) glDeleteFramebuffers(1, &this->id);
}

void FBO::bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, this->id);
}

void FBO::unbind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::attach(const Texture2D& texture)
{
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);
}

void FBO::attach_depth(int width, int height)
{
  glGenRenderbuffers(1, &this->id_depth);
  glBindRenderbuffer(GL_RENDERBUFFER, this->id_depth);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->id_depth);
}
