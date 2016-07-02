#pragma once


namespace gl {

void viewport(GLint x, GLint y, GLsizei width, GLsizei height);

void clear_color(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
void clear(GLbitfield mask);

void enable_vertex_attrib_array(GLuint location);
void disable_vertex_attrib_array(GLuint location);

void enable(GLenum cap);
void disable(GLenum cap);

void cull_face(GLenum mode);

void blend_equation(GLenum mode);
void blend_equation_separate(GLenum modeRGB, GLenum modeAlpha);
void blend_func(GLenum sfactor, GLenum dfactor);
void blend_func_separate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);

} // namespace gl
