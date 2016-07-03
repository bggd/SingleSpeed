IBO::IBO()
{
  glGenBuffers(1, &this->id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IBO::~IBO()
{
  if (glIsBuffer(this->id) == GL_TRUE) glDeleteBuffers(1, &this->id);
}

void IBO::bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
}

void IBO::unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IBO::buffer_data(size_t size, const void* vertices, GLenum usage)
{
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, usage);
}

void IBO::draw_elements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
  glDrawElements(mode, count, type, indices);
}
