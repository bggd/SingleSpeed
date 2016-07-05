Shader::Shader() : program(0), vert(0), frag(0)
{
  this->program = glCreateProgram();
}

Shader::~Shader()
{
  if (glIsProgram(this->program) == GL_TRUE) {
    glDetachShader(this->program, this->vert);
    glDetachShader(this->program, this->frag);
    glDeleteShader(this->vert);
    glDeleteShader(this->frag);
    glDeleteProgram(this->program);
    this->program = this->vert = this->frag = 0;
  }
}

bool Shader::compile(GLenum type, const char* src)
{
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

  if (status == GL_TRUE) {
    // TODO log verbose
  }
  else {
    GLsizei len;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

    GLchar* info_log = new GLchar[len];
    glGetShaderInfoLog(shader, len, NULL, info_log);
    // TODO log error
    std::cerr << info_log << std::endl;
    delete info_log;

    return false;
  }

  if (type == GL_VERTEX_SHADER) this->vert = shader;
  if (type == GL_FRAGMENT_SHADER) this->frag = shader;

  return true;
}

void Shader::bind_attr(GLuint location, const char* name)
{
  glBindAttribLocation(this->program, location, name);
}

bool Shader::link()
{
  glAttachShader(this->program, this->vert);
  glAttachShader(this->program, this->frag);
  glLinkProgram(this->program);

  GLint status;
  glGetProgramiv(this->program, GL_LINK_STATUS, &status);

  if (status == GL_TRUE) {
    // TODO log verbose
    return true;
  }
  else {
    GLsizei len;
    glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &len);
    GLchar* info_log = new GLchar[len];
    // TODO log error
    std::cerr << info_log << std::endl;
    delete info_log;
    return false;
  }
}

GLint Shader::get_uniform_location(const char* name)
{
  return glGetUniformLocation(this->program, name);
}

void Shader::uniform_mat4(GLint location, GLsizei count, const GLfloat* v)
{
  glUniformMatrix4fv(location, count, GL_FALSE, v);
}

void Shader::bind_frag_data_location(GLuint color_number, const char* name)
{
  if (!GLInfo::is_gles2) {
    glBindFragDataLocation(this->program, color_number, name);
  }
}

void Shader::bind()
{
  glUseProgram(this->program);
}

void Shader::unbind()
{
  glUseProgram(0);
}
