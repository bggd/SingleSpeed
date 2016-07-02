namespace gl {

void viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
  glViewport(x, y, width, height);
}

void clear_color(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
  glClearColor(red, green, blue, alpha);
}

void clear(GLbitfield mask)
{
  glClear(mask);
}

void enable_vertex_attrib_array(GLuint location)
{
  glEnableVertexAttribArray(location);
}

void disable_vertex_attrib_array(GLuint location)
{
  glDisableVertexAttribArray(location);
}

void enable(GLenum cap)
{
  glEnable(cap);
}

void disable(GLenum cap)
{
  glDisable(cap);
}

void cull_face(GLenum mode)
{
  glCullFace(mode);
}

void blend_equation(GLenum mode)
{
  glBlendEquation(mode);
}

void blend_equation_separate(GLenum modeRGB, GLenum modeAlpha)
{
  glBlendEquationSeparate(modeRGB, modeAlpha);
}

void blend_func(GLenum sfactor, GLenum dfactor)
{
  glBlendFunc(sfactor, dfactor);
}

void blend_func_separate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
  glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

} // namespace gl
