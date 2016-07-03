VBO::VBO()
{
  glGenBuffers(1, &this->id);
  glBindBuffer(GL_ARRAY_BUFFER, this->id);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::~VBO()
{
  if (glIsBuffer(this->id) == GL_TRUE) glDeleteBuffers(1, &this->id);
}

void VBO::bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VBO::unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::vertex_attrib_pointer(GLuint location, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* offset)
{
  glVertexAttribPointer(location, size, type, normalized, stride, offset);
}

void VBO::buffer_data(size_t size, const void* vertices, GLenum usage)
{
  glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
}

void VBO::draw_arrays(GLenum mode, GLint first, GLsizei count)
{
  glDrawArrays(mode, first, count);
}

const GLenum VBO::STATIC_DRAW = GL_STATIC_DRAW;
const GLenum VBO::STREAM_DRAW = GL_STREAM_DRAW;
const GLenum VBO::DYNAMIC_DRAW = GL_DYNAMIC_DRAW;
